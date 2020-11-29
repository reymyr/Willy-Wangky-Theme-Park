#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "adt.h"

void randomPengunjung(PrioQueuePengunjung * PQ, ArrWahana AW);
/* I.S. PQ sembarang */
/* F.S. PQ terisi pengunjung secara acak */
void processKesabaran(PrioQueuePengunjung * Antrian);
/* Proses kesabaran pengunjung */
void initActionDatabase(ArrAction * AA);
/* Menginisialisasi array action yang diisi semua action */
void initPrepActionArray(ArrAction * AA);
/* Menginisialisasi array action yang dapat dilakukan saat preparation phase */
void initMainActionArray(ArrAction * AA);
/* Menginisialisasi array action yang dapat dilakukan saat main phase */

/* Savenya gabisa ngeload pointer (Graph, list linear, tree) */
struct SaveData {
    boolean prepPhase;
    Player player;
    ArrWahana builtWahana;
    JAM currentTime;
    PrioQueuePengunjung antrian;
    PrioQueuePengunjung inWahana;
    Stack actionStack;
};

void save(boolean prep, Player P, ArrWahana builtW, JAM currentTime, PrioQueuePengunjung antrian, PrioQueuePengunjung inWahana, Stack actStack);
/* Prosedur menyimpan data game ke file eksternal */

void load(boolean *prep, Player *P, ArrWahana *builtW, JAM *currentTime, Graph *G, PrioQueuePengunjung *antrian, PrioQueuePengunjung *inWahana, Stack *actStack);
/* Prosedur membaca data game dari file eksternal */

int main()
{
    srand(time(0));
    int moveStatus; /* Penanda keberhasilan gerak */
    int counter; /* Penanda waktu (seberapa lama setelah opening time) */
    boolean prepPhase; /* Penanda phase saat ini */
    ArrAction ActionDatabase; /* Seluruh aksi yang bisa dilakukan dalam game */
    ArrAction PrepActionArray; /* Aksi yang dapat dilakukan saat preparation phase */
    ArrAction MainActionArray; /* Aksi yang dapat dilakukan saat main phase */
    ArrWahana WahanaDatabase; /* Semua wahana dalam game */
    ArrWahana BuiltWahana; /* List Wahana yang sudah dibangun */
    ArrWahana BaseWahana; /* List wahana dasar yang dapat dibangun di awal */
    ArrListWahanaUpg ArrWahanaUpg; /* Array yg mencatat List berkait yg merepresentasikan history upgrade dari wahana yg elah dibangun*/
    ArrTree UpgradeTrees;
    TabMaterial MaterialDatabase; /* Seluruh material yang ada di dalam game */
    JAM CurrentTime; /* Waktu sekarang */
    JAM OpeningTime = MakeJAM(0, 9, 0); /* Waktu buka */
    JAM ClosingTime = MakeJAM(0, 21, 0); /* Waktu tutup */
    Graph Map; /* Map */
    Player P; /* Player */
    Pengunjung Pgj; /* Pengunjung yang sedang diproses */
    PrioQueuePengunjung Antrian; /* Antrian pengunjung */
    PrioQueuePengunjung DalamWahana;
    Stack ActionStack; /* Stack pada preparation phase */
    Stack ExecuteStack; /* Stack yang sudah di inverse sebelum di execute */
    S_infotype StackElmt; /* Elemen stack */
    Wahana WBuilt; /* Wahan yangakan dibangun/upgrade */
    List WListUpg; /* List Upgrade */
    Kata KATANEW = MK_MakeKata("new", 3);
    Kata KATALOAD = MK_MakeKata("load", 4);
    Kata KATAEXIT = MK_MakeKata("exit", 4);

    /* Inisialisasi data-data game */
    initActionDatabase(&ActionDatabase);
    initPrepActionArray(&PrepActionArray);
    initMainActionArray(&MainActionArray);
    AM_BacaFile(&MaterialDatabase, "../files/material.txt", false); /* membaca file material.txt */
    MK_EndKata = false;
    AW_readWahanaDanTree(&UpgradeTrees, &WahanaDatabase, "../files/wahana.txt"); /* membaca file wahana.txt */
    AW_MakeEmpty(&BaseWahana);
    for (size_t i = 0; i < AT_Neff(UpgradeTrees); i++)
    {
        AW_AddAsLastEl(&BaseWahana, AW_GetWahanaId(WahanaDatabase, Akar(AT_Elmt(UpgradeTrees, i))));
    }

    /* Tampilan main menu */
    printf("Welcome to Willy Wangky's\n");
    printf("Commands:\n");
    printf("new - New game\n");
    printf("load - Load game (blm ada)\n");
    printf("exit - Exit game\n\n");

    MK_STARTKATAINPUT();
    while (!MK_EndKata)
    {   
        /* Validasi input */
        while (!MK_isKataSama(MK_CKata, KATANEW) && !MK_isKataSama(MK_CKata, KATALOAD) && !MK_isKataSama(MK_CKata, KATAEXIT))
        {
            printf("Input tidak valid\n");
            MK_ADVKATAINPUT();
        }
        
        if (!MK_isKataSama(MK_CKata, KATAEXIT))
        {
            /* New Game */
            if (MK_isKataSama(MK_CKata, KATANEW))
            {
                printf("Memulai permainan baru...\n");
                printf("Masukkan nama: ");
                MK_ADVKATAINPUT();
                /* Insialisasi player dgn nama MK_CKata */
                Nama(P) = MK_CKata;
                Money(P) = 10000;
                AM_MakeEmpty(&Materials(P));
                printf("Selamat bermain, ");
                MK_printKata(Nama(P)); printf("\n");

                /* Inisialisasi map default */
                CreateEmptyGraph(&Map);
                Gaddress P1 = AlokasiNodeGraph("../files/map1.txt");
                Gaddress P2 = AlokasiNodeGraph("../files/map2.txt");
                Gaddress P3 = AlokasiNodeGraph("../files/map3.txt");
                Gaddress P4 = AlokasiNodeGraph("../files/map4.txt");
                InsertLastGraph(&Map, P1);
                InsertLastGraph(&Map, P2);
                InsertLastGraph(&Map, P3);
                InsertLastGraph(&Map, P4);

                /* Menempatkan player di posisi awal */
                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, 2, 2);

                /* Material awal buat debug */
                AM_AddCount(&Materials(P), MK_MakeKata("Wood", 4), 20, AM_GetPrice(MaterialDatabase, MK_MakeKata("Wood", 4)));
                AM_AddCount(&Materials(P), MK_MakeKata("Stone", 5), 20, AM_GetPrice(MaterialDatabase, MK_MakeKata("Stone", 5)));
                AM_AddCount(&Materials(P), MK_MakeKata("Steel", 5), 20, AM_GetPrice(MaterialDatabase, MK_MakeKata("Steel", 5)));

                /* Inisialisasi data game lain */
                AW_MakeEmpty(&BuiltWahana);
                WU_CreateEmpty(&ArrWahanaUpg);
                CreateEmptyStack(&ActionStack);
                PQ_MakeEmpty(&Antrian);
                PQ_MakeEmpty(&DalamWahana);
                prepPhase = true;
                CurrentTime = MakeJAM(1, 21, 0);
            }
            /* Load Game */
            else /* (MK_isKataSama(MK_CKata, KATALOAD)) */
            {
                printf("Load game\n");
                /* Baca state dari file */
                /* NANTI GANTI JADI DARI FILE EKSTERNAL */
                CreateEmptyGraph(&Map);
                AW_MakeEmpty(&BuiltWahana);
                WU_CreateEmpty(&ArrWahanaUpg);
                CreateEmptyStack(&ActionStack);
                load(&prepPhase, &P, &BuiltWahana, &CurrentTime, &Map, &Antrian, &DalamWahana, &ActionStack);
                /* Load Wahana History */
                // loadwahanahistory("../../WahanaHistory.txt",&ArrWahanaUpg);
            }

            do
            {
                if (prepPhase)   /* Preparation Phase */
                {
                    printf("Preparation Phase Day %d\n", Day(CurrentTime)); 
                    printCurrentMap(Map, P);
                    printf("Name: "); MK_printKata(Nama(P)); printf("\n");
                    printf("Money: %d\n", Money(P));
                    printf("Current Time: "); TulisJAM(CurrentTime); printf("\n");
                    printf("Opening Time: "); TulisJAM(OpeningTime); printf("\n");
                    printf("Time Remaining: "); TulisJamMenit(DurasiJam(CurrentTime, OpeningTime)); printf("\n");
                    printf("Total aksi yang akan dilakukan: %d\n", NbElmtStack(ActionStack));
                    printf("Total waktu yang dibutuhkan: "); (JAMToMenit(TotalTime(ActionStack)) == 0 ? printf("0") : TulisJamMenit(TotalTime(ActionStack))); printf("\n");
                    printf("Total uang yang dibutuhkan: %d\n\n", TotalMoney(ActionStack));

                    printf("Masukkan perintah: \n");

                    MK_STARTKATAINPUT();

                    /* Validasi input */
                    while (!AA_SearchB(PrepActionArray, MK_CKata))
                    {
                        printf("Input tidak valid\n");
                        MK_ADVKATAINPUT();
                    }
                    int ActionID = AA_SearchID(PrepActionArray, MK_CKata);
                    switch (ActionID)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        /* MOVE (W, A, S, D) */
                        move(&Map, &P, ActionID, &moveStatus);
                        printf("\n");
                        break;
                    case 4:
                        /* BUILD */
                        printf("Ingin membangun apa?\n");
                        printf("List:\n");

                        /* Menulis wahana yang dapat dibangun di awal beserta bahan dan uang yang dibutuhkan */
                        for (size_t i = 0; i < AW_NbElmt(BaseWahana); i++)
                        {
                            AW_printWahanaCost(AW_Elmt(BaseWahana, i));
                            printf("\n\n");
                        }

                        /* Menulis bahan yang dimiliki pemain */
                        printf("Bahan yang anda miliki:\n");
                        AM_TulisIsiTabCount(Materials(P)); printf("\n");

                        /* Meminta input nama wahana */
                        MK_ADVKATAINPUT();
                        if (AW_SearchB(BuiltWahana, MK_CKata)) /* Tidak bisa membangun dua wahana yang sama */
                        {
                            printf("Anda sudah membangun wahana tersebut\n");
                        }
                        else if (!AW_SearchB(BaseWahana, MK_CKata)) /* Nama wahana bukan wahana yang dapat dibangun */
                        {
                            printf("Input tidak valid\n");
                        }
                        else if (nearChar(P, '^') || nearChar(P, '>') || nearChar(P, 'V') || nearChar(P, '<'))  /* Pemain berada di sebelah gerbang */
                        {
                            printf("Tidak bisa membangun wahana di sebelah gerbang\n");
                        }
                        else
                        {
                            /* Memeriksa apakah ada petak kosong di sebelah player */
                            int pushCode = 0;
                            while (T_Type(Surround(P)[pushCode]) != '-' && pushCode <= 3)
                            {
                                pushCode++;
                            }

                            /* Tidak ada petak kosong */
                            if (pushCode == 4)
                            {
                                printf("Tidak bisa menempatkan wahana di sini\n");
                            }
                            /* Waktu pembangunan tidak cukup */
                            else if ((JLT(DurasiJam(CurrentTime, OpeningTime), MenitToJAM(JAMToMenit(TotalTime(ActionStack))+JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 4)))))))
                            {
                                printf("Waktu yang dibutuhkan tidak cukup\n");
                            }
                            else
                            {
                                WBuilt = AW_GetWahana(WahanaDatabase, MK_CKata);
                                int cost = W_MoneyCost(WBuilt);
                                if (TotalMoney(ActionStack)+cost > Money(P))    /* Uang pemain tidak cukup */
                                {
                                    printf("Uang anda tidak cukup\n");
                                }
                                else
                                {
                                    if (AM_MoreThan(Materials(P), W_MaterialCost(WBuilt)))  /* Memeriksa apakah pemain memiliki bahan yang cukup */
                                    {
                                        setTile(&Map, G_CurrentArea(Map), Pos(P), 'W', -1);

                                        StackElmt = CreateStackInfo(MK_MakeKata("build", 5), A_Duration(AA_Elmt(ActionDatabase, 4)), cost, Pos(P));
                                        S_IdWahanaFrom(StackElmt) = -1;
                                        S_IdWahanaTo(StackElmt) = AW_GetId(WahanaDatabase, MK_CKata);
                                        Push(&ActionStack, StackElmt);

                                        W_Area(WBuilt) = G_CurrentArea(Map);
                                        W_Location(WBuilt) = Pos(P);

                                        WU_Build(&ArrWahanaUpg,WBuilt);
                                        AW_AddAsLastEl(&BuiltWahana, WBuilt);
                                        

                                        move(&Map, &P, pushCode, &moveStatus);   
                                    }
                                    else    /* Bahan tidak cukup */
                                    {
                                        printf("Material anda tidak cukup\n");
                                    }                                    
                                }                              
                            }
                        }
                        break;
                    case 5: ; 
                        /* UPGRADE */
                        
                        /* Mencari apakah ada wahana di sekitar pemain */
                        boolean foundwahana = false;
                        int WId = -1;

                        for (size_t i = 0; i < 4; i++)
                        {
                            if (T_Type(Surround(P)[i]) == 'W')
                            {
                                foundwahana = true;
                                if (T_ID(Surround(P)[i]) != -1)
                                {
                                    WId = T_ID(Surround(P)[i]);
                                    break;
                                }
                            }
                        }
                        if (!foundwahana)   /* Tidak ada wahana di sekitar pemain */
                        {
                            printf("Tidak ada wahana di sekitar.\n");
                        }
                        else if (WId == -1) /* Wahana di sekitar pemain belum dibangun atau belum diupgrade (belum dilakukan execute) */
                        {
                            printf("Wahana belum dibangun atau sedang diupgrade, input 'execute' untuk membangun/upgrade wahana\n");
                        }
                        /* Waktu upgrade tidak cukup */
                        else if ((JLT(DurasiJam(CurrentTime, OpeningTime), MenitToJAM(JAMToMenit(TotalTime(ActionStack))+JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 5)))))))
                        {
                            printf("Waktu yang dibutuhkan tidak cukup\n");
                        }
                        else
                        {
                            /* Mencari wahana upgrade */
                            int LId, RId;
                            int BaseId = W_BaseId(AW_GetWahanaId(BuiltWahana, WId));
                            BinTree UpTree = AT_SearchBase(UpgradeTrees, BaseId);
                            getChildId(UpTree, WId, &LId, &RId);
                            if (LId == -1 && RId == -1) /* Wahana tidak dapat diupgrade lagi */
                            {
                                printf("Wahana sudah tidak dapat diupgrade lagi\n");
                            }
                            else
                            {
                                printf("Ingin melakukan upgrade apa?\nList:\n");

                                /* Menulis nama, bahan, dan uang yang dibutuhkan */
                                if (LId != -1)
                                {
                                    AW_printWahanaCost(AW_GetWahanaId(WahanaDatabase, LId));
                                    printf("\n\n");
                                 }
                                if (RId != -1)
                                {
                                    AW_printWahanaCost(AW_GetWahanaId(WahanaDatabase, RId));
                                    printf("\n\n");
                                }

                                /* Menuliskan bahan yang dimiliki pemain */
                                printf("Bahan yang anda miliki:\n");
                                AM_TulisIsiTabCount(Materials(P)); printf("\n");

                                /* Meminta input nama wahana */
                                MK_ADVKATAINPUT();
                                int IdInput = AW_GetId(WahanaDatabase, MK_CKata);
                                if (IdInput == -1)  /* Nama wahana yang di-input tidak ada dalam game */
                                {
                                    printf("Tidak ada wahana dengan nama tersebut\n");
                                }
                                else if (!isChild(UpTree, IdInput, WId))    /* Wahana bukan hasil upgrade (bukan child) */
                                {
                                    printf("Wahana ini tidak dapat di upgrade ke wahana yang di input\n");
                                }
                                else if (AW_SearchB(BuiltWahana, MK_CKata)) /* Tidak bisa membangun dua wahana yang sama */
                                {
                                    printf("Anda sudah membangun wahana tersebut\n");
                                }
                                else
                                {
                                    WBuilt = AW_GetWahana(WahanaDatabase, MK_CKata);
                                    int cost = W_MoneyCost(WBuilt);
                                    if (TotalMoney(ActionStack) + cost > Money(P))    /* Uang tidak mencukupi */
                                    {
                                        printf("Uang anda tidak cukup\n");
                                    }
                                    else if (!AM_MoreThan(Materials(P), W_MaterialCost(WBuilt))) /* Material tidak mencukupi */
                                    {
                                        printf("Material anda tidak cukup\n");
                                    }
                                    else
                                    {
                                        /* Penanda wahana sedang diupgrade */
                                        setTile(&Map, G_CurrentArea(Map), W_Location(AW_GetWahanaId(BuiltWahana, WId)), 'W', -1);
                                        setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                        /* Membuat elemen stack */
                                        StackElmt = CreateStackInfo(MK_MakeKata("upgrade", 7), A_Duration(AA_Elmt(ActionDatabase, 5)), cost, W_Location(AW_GetWahanaId(BuiltWahana, WId)));
                                        S_IdWahanaFrom(StackElmt) = WId;
                                        S_IdWahanaTo(StackElmt) = AW_GetId(WahanaDatabase, MK_CKata);
                                        /* Push ke dalam stack */
                                        Push(&ActionStack, StackElmt);
                                    }
                                }
                            }
                        }                        
                        break;
                    case 6: ;
                        /* BUY */
                        int matCount, price;
                        Kata matName;
                        /* Menampilkan list bahan yang dapat dibeli beserta harganya */
                        printf("Ingin membeli apa?\n");
                        printf("List:\n");
                        AM_TulisIsiTab(MaterialDatabase);

                        /* Menerima input dengan format 'jumlah nama_material' */
                        MK_ADV();
                        MK_ADVKATA();
                        matCount = MK_KataToInt(MK_CKata);
                        MK_ADVKATA();
                        matName = MK_CKata;
                        price = matCount * AM_GetPrice(MaterialDatabase, matName);

                        /* Nama material tidak ada dalam game */
                        if (!AM_SearchB(MaterialDatabase, matName))
                        {
                            printf("Input tidak valid\n");
                        }
                        /* Uang tidak mencukupi */
                        else if (TotalMoney(ActionStack)+price > Money(P))
                        {
                            printf("Uang anda tidak cukup\n");
                        }
                        /* Waktu tidak cukup */
                        else if (JLT(DurasiJam(CurrentTime, OpeningTime), MenitToJAM(JAMToMenit(TotalTime(ActionStack))+JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 6))))))
                        {
                            printf("Waktu yang dibutuhkan tidak cukup\n");
                        }
                        else
                        {
                            /* Pembuatan elemen stack dan push */
                            StackElmt = CreateStackInfo(MK_MakeKata("buy", 3), A_Duration(AA_Elmt(ActionDatabase, 6)), price, MakePOINT(-1,-1));
                            S_MatName(StackElmt) = matName;
                            S_MatCount(StackElmt) = matCount;
                            Push(&ActionStack, StackElmt);
                        }
                        printf("\n");
                        break;
                    case 7:
                        /* UNDO */
                        if (!IsEmptyStack(ActionStack)) /* Pengecekan stack kosong */
                        {
                            Pop(&ActionStack, &StackElmt);
                            if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("build", 5)))  /* Undo perintah build */
                            {
                                setTile(&Map, W_Area(AW_GetWahanaId(BuiltWahana, S_IdWahanaTo(StackElmt))), S_PosWahana(StackElmt), '-', -1);
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                AW_DelLastEl(&BuiltWahana, &WBuilt);
                                LL_DelVLast(&ArrWahanaUpg.Tab[W_BaseId(WBuilt)], &WBuilt);
                            }
                            else if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("upgrade", 7))) /* Undo perintah upgrade */
                            {
                                setTile(&Map, W_Area(AW_GetWahanaId(BuiltWahana, S_IdWahanaFrom(StackElmt))), S_PosWahana(StackElmt), 'W', S_IdWahanaFrom(StackElmt));
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                            }
                            
                        }
                        break;
                    case 8:
                        /* EXECUTE */
                        InverseStack(&ActionStack, &ExecuteStack);
                        /* JALANIN SATU PERSATU DARI TOP */
                        while (!IsEmptyStack(ExecuteStack))
                        {
                            Pop(&ExecuteStack, &StackElmt);
                            Money(P) -= S_MoneyNeeded(StackElmt);
                            if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("buy", 3)))    /* Buy */
                            {
                                /* Menambah material pemain */
                                AM_AddCount(&Materials(P), S_MatName(StackElmt), S_MatCount(StackElmt), AM_GetPrice(MaterialDatabase, matName));
                            }
                            else if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("upgrade", 7)))   /* Upgrade */
                            {
                                setTile(&Map, W_Area(AW_GetWahanaId(BuiltWahana, S_IdWahanaFrom(StackElmt))), S_PosWahana(StackElmt), 'W', S_IdWahanaTo(StackElmt));
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                TabMaterial matCost = W_MaterialCost(AW_GetWahanaId(WahanaDatabase, S_IdWahanaTo(StackElmt)));
                                for (size_t i = 0; i < AM_NEff(matCost); i++)
                                {
                                    AM_DelCount(&Materials(P), M_Name(AM_Elmt(matCost, i)), M_Count(AM_Elmt(matCost, i)));
                                }
                                UpgradeWahana(&BuiltWahana, AW_GetWahanaId(BuiltWahana, S_IdWahanaFrom(StackElmt)), AW_GetWahanaId(WahanaDatabase, S_IdWahanaTo(StackElmt)), ArrWahanaUpg);
                            }
                            else /* build */
                            {
                                setTile(&Map, W_Area(AW_GetWahanaId(BuiltWahana, S_IdWahanaTo(StackElmt))), S_PosWahana(StackElmt), 'W', S_IdWahanaTo(StackElmt));
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                TabMaterial matCost = W_MaterialCost(AW_GetWahanaId(WahanaDatabase, S_IdWahanaTo(StackElmt)));
                                for (size_t i = 0; i < AM_NEff(matCost); i++)
                                {
                                    AM_DelCount(&Materials(P), M_Name(AM_Elmt(matCost, i)), M_Count(AM_Elmt(matCost, i)));
                                }
                            }
                        }
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;  /* Penanda main phase */
                        randomPengunjung(&Antrian, BuiltWahana);    /* Merandom pengunjung yang datang pada main phase */
                        counter = 0;    
                        break;
                    case 9:
                        /* MAIN */
                        while (!IsEmptyStack(ActionStack))
                        {
                            Pop(&ActionStack, &StackElmt);
                            if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("build", 5)))
                            {
                                setTile(&Map, G_CurrentArea(Map), S_PosWahana(StackElmt), '-', -1);
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                AW_DelLastEl(&BuiltWahana, &WBuilt);
                                LL_DelVLast(&ArrWahanaUpg.Tab[W_BaseId(WBuilt)], &WBuilt);
                            }
                            else if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("upgrade", 7))) /* Undo perintah upgrade */
                            {
                                setTile(&Map, W_Area(AW_GetWahanaId(BuiltWahana, S_IdWahanaFrom(StackElmt))), S_PosWahana(StackElmt), 'W', S_IdWahanaFrom(StackElmt));
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                            }
                        }
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;  /* Penanda main phase */
                        randomPengunjung(&Antrian, BuiltWahana);    /* Merandom pengunjung yang datang pada main phase */
                        counter = 0;
                        break;
                    case 15:
                        save(prepPhase, P, BuiltWahana, CurrentTime, Antrian, DalamWahana, ActionStack);
                        break;
                    default:
                        break;
                    }
                }
                else /* Main Phase */
                {
                    printf("Main Phase Day %d\n", Day(CurrentTime)); 
                    printCurrentMap(Map, P);
                    printf("Name: "); MK_printKata(Nama(P)); printf("\n");
                    printf("Money: %d\n", Money(P));
                    printf("Current Time: "); TulisJAM(CurrentTime); printf("\n");
                    printf("Closing Time: "); TulisJAM(ClosingTime); printf("\n");
                    printf("Time Remaining: "); TulisJamMenit(DurasiJam(CurrentTime, ClosingTime)); printf("\n");
                    PQ_PrintQueuePengunjung(Antrian); printf("\n");
                    AW_printBroken(BuiltWahana); printf("\n");

                    printf("Masukkan perintah");
                    if (T_Type(Elmt(GetMap(Map, G_CurrentArea(Map)), Baris(Pos(P)), Kolom(Pos(P)))) == 'O')
                    {
                        printf(" (Masukkan 'office' untuk mengakses office)");
                    }
                    printf(":\n");

                    /* Meminta input aksi */
                    MK_STARTKATAINPUT();
                    while (!AA_SearchB(MainActionArray, MK_CKata))
                    {
                        printf("Input tidak valid\n");
                        MK_ADVKATAINPUT();
                    }
                    int ActionID = AA_SearchID(MainActionArray, MK_CKata);
                    switch (ActionID)
                    {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        /* MOVE (W, A, S, D) */
                        move(&Map, &P, ActionID, &moveStatus);
                        if (moveStatus == 1)
                        {
                            CurrentTime = NextNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID))));
                        }
                        printf("\n");
                        break;
                    case 10:
                        /* SERVE */
                        if (!nearChar(P, 'A'))
                        {
                            printf("Anda tidak berada di sebelah antrian\n");
                        }
                        else if (PQ_IsEmpty(Antrian))
                        {
                            printf("Antrian sudah kosong\n");
                        }
                        else
                        {
                            printf("Ingin serve wahana apa?\n");
                            MK_ADVKATAINPUT();
                            PQ_Dequeue(&Antrian, &Pgj);
                            if (!AK_SearchB(P_Wahana(Pgj), MK_CKata))
                            {
                                printf("Pengunjung tidak ingin menaiki wahana tersebut\n");
                                PQ_Enqueue(&Antrian, Pgj);
                            }
                            else
                            {
                                if (IsWahanaRusak(AW_GetWahana(BuiltWahana, MK_CKata)))
                                {
                                    printf("Wahana tersebut rusak\n");
                                    PQ_Enqueue(&Antrian, Pgj);
                                }
                                else if (W_Capacity(AW_GetWahana(BuiltWahana, MK_CKata)) <= PQ_getWahanaCount(DalamWahana, MK_CKata))
                                {
                                    printf("Wahana tersebut sudah penuh\n");
                                    PQ_Enqueue(&Antrian, Pgj);
                                }                                
                                else
                                {
                                    CurrentTime = NextNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID))));
                                    
                                    int r = rand() % 100;
                                    if (r < 40)
                                    {
                                        AW_setRusak(&BuiltWahana, MK_CKata);
                                        PQ_Enqueue(&Antrian, Pgj);
                                        PQ_WahanaRusak(&Antrian, &DalamWahana, MK_CKata);
                                    }
                                    else
                                    {
                                        P_CurrentWahana(Pgj) = MK_CKata;
                                        P_StartTime(Pgj) =  PrevNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID))));
                                        P_TimeLeft(Pgj) = W_Duration(AW_GetWahana(BuiltWahana, MK_CKata)) + JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID)));
                                        Money(P) += AW_GetPrice(BuiltWahana, MK_CKata);
                                        AK_DelKata(&P_Wahana(Pgj), MK_CKata); 
                                        PQ_EnqueueTimeLeft(&DalamWahana, Pgj);
                                        AW_pengungjungNaik(&BuiltWahana, MK_CKata);   
                                    }
                                    
                                }                                
                            }
                        }   
                        break;
                    case 11:
                        /* REPAIR */
                        for (size_t i = 0; i < 4; i++)
                        {
                            if (T_Type(Surround(P)[i]) == 'W')
                            {
                                if (W_IsBroken(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i]))))
                                {
                                    if (Money(P) < AW_GetCost(BuiltWahana, W_Name(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i])))) / 2)
                                    {
                                        printf("Uang anda tidak cukup\n");
                                    }
                                    else
                                    {
                                        Money(P) -= (AW_GetCost(BuiltWahana, W_Name(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i])))) / 2);
                                        CurrentTime = NextNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 11))));
                                        AW_RepairWahanaRusak(&BuiltWahana, W_Name(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i]))));
                                    }
                                    break;
                                }
                            }
                        }
                        break;
                    case 12:
                        /* DETAIL */
                        for (size_t i = 0; i < 4; i++)
                        {
                            if (T_Type(Surround(P)[i]) == 'W')
                            {
                                AW_detailWahana(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i])), ArrWahanaUpg);
                                printf("\n");
                            }
                        }
                        break;
                    case 13:
                        /* OFFICE */
                        if (!(T_Type(Elmt(GetMap(Map, G_CurrentArea(Map)), Baris(Pos(P)), Kolom(Pos(P)))) == 'O'))
                        {
                            printf("Anda tidak berada pada office\n");
                        }
                        else
                        {
                            printf("Masukkan perintah (Details / Report / Exit):\n");
                            MK_ADVKATAINPUT();
                            while (!MK_isKataSama(MK_CKata, MK_MakeKata("Details", 7)) &&
                                   !MK_isKataSama(MK_CKata, MK_MakeKata("Report", 6)) &&
                                   !MK_isKataSama(MK_CKata, MK_MakeKata("Exit", 4)))
                            {
                                printf("Input tidak valid\n");
                                MK_ADVKATAINPUT();
                            }

                            while (!MK_isKataSama(MK_CKata, MK_MakeKata("Exit", 4)))
                            {
                                while (!MK_isKataSama(MK_CKata, MK_MakeKata("Details", 7)) &&
                                       !MK_isKataSama(MK_CKata, MK_MakeKata("Report", 6)) &&
                                       !MK_isKataSama(MK_CKata, MK_MakeKata("Exit", 4)))
                                {
                                    printf("Input tidak valid\n");
                                    MK_ADVKATAINPUT();
                                }

                                if (MK_isKataSama(MK_CKata, MK_MakeKata("Details", 7)))
                                {
                                    /* Details */
                                    printf("List wahana yang sudah dibangun: \n");
                                    AW_ListNamaWahana(BuiltWahana);
                                    MK_ADVKATAINPUT();
                                    if (!AW_SearchB(BuiltWahana, MK_CKata))
                                    {
                                        printf("Wahana tersebut belum dibangun atau tidak ada wahana dengan nama tersebut\n");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        AW_detailWahana(AW_GetWahana(BuiltWahana, MK_CKata),ArrWahanaUpg);
                                    }
                                    printf("Masukkan perintah (Details / Report / Exit):\n");
                                    MK_ADVKATAINPUT();                              
                                }
                                else if (MK_isKataSama(MK_CKata, MK_MakeKata("Report", 6)))
                                {
                                    /* Report */
                                    printf("List wahana yang sudah dibangun: \n");
                                    AW_ListNamaWahana(BuiltWahana);
                                    MK_ADVKATAINPUT();
                                    if (!AW_SearchB(BuiltWahana, MK_CKata))
                                    {
                                        printf("Wahana tersebut belum dibangun atau tidak ada wahana dengan nama tersebut\n");
                                    }
                                    else
                                    {
                                        printf("\n");
                                        AW_reportWahana(AW_GetWahana(BuiltWahana, MK_CKata));
                                    }
                                    printf("Masukkan perintah (Details / Report / Exit):\n");
                                    MK_ADVKATAINPUT();
                                }
                            }
                        }
                        break;
                    case 14:
                        /* PREPARE */
                        PQ_MakeEmpty(&Antrian);
                        PQ_MakeEmpty(&DalamWahana);
                        CurrentTime = MakeJAM(Day(CurrentTime)+1, 21, 0);
                        AW_newDay(&BuiltWahana);
                        prepPhase = true;
                        break;
                    case 15:
                        save(prepPhase, P, BuiltWahana, CurrentTime, Antrian, DalamWahana, ActionStack);
                        break;
                    default:
                        break;
                    }
                    /* Memeriksa apakah waktu sudah melebihi closing time, jika sudah langsung ke preparation phase */
                    if (!prepPhase)
                    {
                        if (JAMToMenitMinDay(ClosingTime) - JAMToMenitMinDay(CurrentTime) <= 0)
                        {
                            PQ_MakeEmpty(&Antrian);
                            PQ_MakeEmpty(&DalamWahana);
                            CurrentTime = MakeJAM(Day(CurrentTime)+1, 21, 0);
                            AW_newDay(&BuiltWahana);
                            prepPhase = true;
                        }
                        else
                        {
                            /* Pengecekan waktu sekarang untuk mengurangi kesabaran pengunjung */
                            while ((JAMToMenit(DurasiJam(OpeningTime, CurrentTime)) / 30) > counter)
                            {
                                counter++;
                                processKesabaran(&Antrian);     
                            }
                            
                            if (!PQ_IsEmpty(DalamWahana))
                            {
            
                                PQ_decTimeLeft(&DalamWahana, CurrentTime);
                                
                                /* Mengeluarkan pengunjung dari wahana jika sudah melebihi batas waktu */
                                while (P_TimeLeft(PQ_Elmt(DalamWahana, PQ_Head(DalamWahana))) <= 0 && !PQ_IsEmpty(DalamWahana))
                                {
                                    PQ_Dequeue(&DalamWahana, &Pgj);
                                    
                                    if (AK_NbElmt(P_Wahana(Pgj)) > 0)
                                    {
                                        P_Prio(Pgj)--;
                                        PQ_Enqueue(&Antrian, Pgj);
                                    }
                                }
                            }
                            
                            
                        }
                    }                                   
                }
            } while (!MK_EndKata);
        }        
        else
        {
            printf("Thank you for playing!!!\n");
            break;
        }
    }
    return 0;
}

void randomPengunjung(PrioQueuePengunjung * PQ, ArrWahana AW)
/* I.S. PQ sembarang */
/* F.S. PQ terisi pengunjung secara acak */
{
    PQ_MakeEmpty(PQ);
    int maxNbWahana = AW_NbElmt(AW);
    int numPengunjung = rand() % PQ_MaxEl + 1; /* Merandom jumlah pengunjung */
    for (size_t i = 0; i < numPengunjung; i++)
    {
        Pengunjung Pgj;
        P_Kesabaran(Pgj) = 5;
        P_CurrentWahana(Pgj) = MK_MakeKata("", 0);
        P_Prio(Pgj) = rand() % 100 + 20;    /* Merandom prioritas pengunjung */
        AK_MakeEmpty(&P_Wahana(Pgj));
        /* Merandom wahana pengunjung */
        for (size_t j = 0; j < AW_NbElmt(AW); j++)
        {
            int r = rand() % 100;
            if (r < 45)
            {
                AK_AddAsLastEl(&P_Wahana(Pgj), W_Name(AW_Elmt(AW, j)));
            }
        }

        if (AK_NbElmt(P_Wahana(Pgj)) > 0)
        {
            PQ_Enqueue(PQ, Pgj);
        }
    }
}

void processKesabaran(PrioQueuePengunjung * Antrian)
/* Proses kesabaran pengunjung */
{
    if (!PQ_IsEmpty(*Antrian))
    {
        int r = rand() % PQ_NBElmt(*Antrian);
        int idx = (PQ_Head(*Antrian) + r) % PQ_MaxEl;
        P_Kesabaran(PQ_Elmt(*Antrian, idx))--;
        if (P_Kesabaran(PQ_Elmt(*Antrian, idx)) <= 0)
        {
            PrioQueuePengunjung Temp;
            Pengunjung PTemp;
            PQ_MakeEmpty(&Temp);
            for (size_t i = 0; i < r; i++)
            {
                PQ_Dequeue(Antrian, &PTemp);
                PQ_Enqueue(&Temp, PTemp);
            }
            PQ_Dequeue(Antrian, &PTemp);
            while (!PQ_IsEmpty(Temp))
            {
                PQ_Dequeue(&Temp, &PTemp);
                PQ_Enqueue(Antrian, PTemp);
            }
        }    
    }
}

void initActionDatabase(ArrAction * AA)
/* Menginisialisasi array action yang berisi semua action dalam game */
{
    AA_MakeEmpty(AA);
    AA_AddAsLastEl(AA, createAction(0, MK_MakeKata("w", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(1, MK_MakeKata("d", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(2, MK_MakeKata("s", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(3, MK_MakeKata("a", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(4, MK_MakeKata("build", 5), MakeJAM(0,2,0)));
    AA_AddAsLastEl(AA, createAction(5, MK_MakeKata("upgrade", 7), MakeJAM(0,1,30)));
    AA_AddAsLastEl(AA, createAction(6, MK_MakeKata("buy", 3), MakeJAM(0,0,30)));
    AA_AddAsLastEl(AA, createAction(7, MK_MakeKata("undo", 4), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(8, MK_MakeKata("execute", 7), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(9, MK_MakeKata("main", 4), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(10, MK_MakeKata("serve", 5), MakeJAM(0,0,10)));
    AA_AddAsLastEl(AA, createAction(11, MK_MakeKata("repair", 6), MakeJAM(0,0,30)));
    AA_AddAsLastEl(AA, createAction(12, MK_MakeKata("detail", 6), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(13, MK_MakeKata("office", 6), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(14, MK_MakeKata("prepare", 7), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(15, MK_MakeKata("save", 4), MakeJAM(0,0,0)));
}

void initPrepActionArray(ArrAction * AA)
/* Menginisialisasi array action yang dapat dilakukan saat preparation phase */
{
    AA_MakeEmpty(AA);
    AA_AddAsLastEl(AA, createAction(0, MK_MakeKata("w", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(1, MK_MakeKata("d", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(2, MK_MakeKata("s", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(3, MK_MakeKata("a", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(4, MK_MakeKata("build", 5), MakeJAM(0,2,0)));
    AA_AddAsLastEl(AA, createAction(5, MK_MakeKata("upgrade", 7), MakeJAM(0,1,30)));
    AA_AddAsLastEl(AA, createAction(6, MK_MakeKata("buy", 3), MakeJAM(0,0,30)));
    AA_AddAsLastEl(AA, createAction(7, MK_MakeKata("undo", 4), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(8, MK_MakeKata("execute", 7), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(9, MK_MakeKata("main", 4), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(15, MK_MakeKata("save", 4), MakeJAM(0,0,0)));
}

void initMainActionArray(ArrAction * AA)
/* Menginisialisasi array action yang dapat dilakukan saat main phase */
{
    AA_MakeEmpty(AA);
    AA_AddAsLastEl(AA, createAction(0, MK_MakeKata("w", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(1, MK_MakeKata("d", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(2, MK_MakeKata("s", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(3, MK_MakeKata("a", 1), MakeJAM(0,0,1)));
    AA_AddAsLastEl(AA, createAction(10, MK_MakeKata("serve", 5), MakeJAM(0,0,10)));
    AA_AddAsLastEl(AA, createAction(11, MK_MakeKata("repair", 6), MakeJAM(0,0,30)));
    AA_AddAsLastEl(AA, createAction(12, MK_MakeKata("detail", 6), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(13, MK_MakeKata("office", 6), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(14, MK_MakeKata("prepare", 7), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(15, MK_MakeKata("save", 4), MakeJAM(0,0,0)));
}

void save(boolean prep, Player P, ArrWahana builtW, JAM currentTime, PrioQueuePengunjung antrian, PrioQueuePengunjung inWahana, Stack actStack)
/* Prosedure menyimpan data game ke file eksternal */
{
    char* path = "../files/savedata";

    FILE *savefile;
    savefile = fopen(path, "wb");
    struct SaveData s;
    s.prepPhase = prep;
    s.player = P;
    s.builtWahana = builtW;
    s.currentTime = currentTime;
    s.antrian = antrian;
    s.inWahana = inWahana;
    s.actionStack = actStack;

    fwrite(&s, sizeof(struct SaveData), 1, savefile);
    fclose(savefile);
    printf("Game saved\n");
}

void load(boolean *prep, Player *P, ArrWahana *builtW, JAM *currentTime, Graph *G, PrioQueuePengunjung *antrian, PrioQueuePengunjung *inWahana, Stack *actStack)
/* Prosedur membaca data game dari file eksternal */
{
    char* path = "../files/savedata";

    FILE *savefile;
    savefile = fopen(path, "rb");
    struct SaveData s;
    fread(&s, sizeof(struct SaveData), 1, savefile);

    *prep = s.prepPhase;
    *P = s.player;
    *builtW = s.builtWahana;
    *currentTime = s.currentTime;
    *antrian = s.antrian;
    *inWahana = s.inWahana;
    *actStack = s.actionStack;

    fclose(savefile);

    CreateEmptyGraph(G);
    Gaddress P1 = AlokasiNodeGraph("../files/map1.txt");
    Gaddress P2 = AlokasiNodeGraph("../files/map2.txt");
    Gaddress P3 = AlokasiNodeGraph("../files/map3.txt");
    Gaddress P4 = AlokasiNodeGraph("../files/map4.txt");
    InsertLastGraph(G, P1);
    InsertLastGraph(G, P2);
    InsertLastGraph(G, P3);
    InsertLastGraph(G, P4);

    for (size_t i = 0; i < AW_NbElmt(*builtW); i++)
    {
        setTile(G, W_Area(AW_Elmt(*builtW, i)), W_Location(AW_Elmt(*builtW, i)), 'W', W_WahanaId(AW_Elmt(*builtW, i)));
    }

    printf("Game loaded\n");
}