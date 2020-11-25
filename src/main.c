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

int main()
{
    srand(time(0));
    int moveStatus; /* Penanda keberhasilan gerak */
    int counter;
    boolean prepPhase; /* Penanda phase saat ini */
    ArrAction ActionDatabase; /* Seluruh aksi yang bisa dilakukan dalam game */
    ArrAction PrepActionArray; /* Aksi yang dapat dilakukan saat preparation phase */
    ArrAction MainActionArray; /* Aksi yang dapat dilakukan saat main phase */
    ArrWahana WahanaDatabase; /* Semua wahana dalam game */
    ArrWahana BuiltWahana; /* List Wahana yang sudah dibangun */
    ArrWahana BaseWahana; /* List wahana dasar yang dapat dibangun di awal */
    ArrListWahanaUpg ArrWahanaUpg; /* Array yg mencatat List berkait yg merepresentasikan history upgrade dari wahana yg elah dibangun*/
    TabMaterial MaterialDatabase; /* Seluruh material yang ada di dalam game */
    JAM CurrentTime; /* Waktu sekarang */
    JAM OpeningTime = MakeJAM(0, 9, 0); /* Waktu buka */
    JAM ClosingTime = MakeJAM(0, 21, 0); /* Waktu tutup */
    Graph Map; /* Map */
    Player P; /* Player */
    Pengunjung Pgj; /* Pengunjung yang sedang diproses */
    PrioQueuePengunjung Antrian; /* Antrian pengunjung */
    Stack ActionStack; /* Stack pada preparation phase */
    Stack ExecuteStack;
    S_infotype StackElmt;
    Wahana WBuilt;
    List WListUpg;
    Kata KATANEW = MK_MakeKata("new", 3);
    Kata KATALOAD = MK_MakeKata("load", 4);
    Kata KATAEXIT = MK_MakeKata("exit", 4);

    /* Inisialisasi data-data game */
    initActionDatabase(&ActionDatabase);
    initPrepActionArray(&PrepActionArray);
    initMainActionArray(&MainActionArray);
    PQ_MakeEmpty(&Antrian);
    AM_BacaFile(&MaterialDatabase, "../files/material.txt");
    AW_BacaFile(&WahanaDatabase, "../files/wahana.txt");

    printf("Welcome to Willy Wangky's\n");
    printf("Commands:\n");
    printf("new - New game\n");
    printf("load - Load game (blm ada)\n");
    printf("exit - Exit game\n\n");

    MK_STARTKATAINPUT();
    while (!MK_EndKata)
    {   
        while (!MK_isKataSama(MK_CKata, KATANEW) && !MK_isKataSama(MK_CKata, KATALOAD) && !MK_isKataSama(MK_CKata, KATAEXIT))
        {
            printf("Input tidak valid\n");
            MK_ADVKATAINPUT();
        }
        
        if (!MK_isKataSama(MK_CKata, KATAEXIT))
        {
            if (MK_isKataSama(MK_CKata, KATANEW))
            {
                printf("Memulai permainan baru...\n");
                printf("Masukkan nama: ");
                MK_ADVKATAINPUT();
                /* Insialisasi player dgn nama MK_CKata */
                Nama(P) = MK_CKata;
                Money(P) = 500;
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

                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, 2, 2);


                /* Inisialisasi data game lain */
                AW_MakeEmpty(&BuiltWahana);
                WU_CreateEmpty(&ArrWahanaUpg);
                CreateEmptyStack(&ActionStack);
                prepPhase = true;
                CurrentTime = MakeJAM(1, 21, 0);
            }
            else /* (MK_isKataSama(MK_CKata, KATALOAD)) */
            {
                printf("Load game\n");
                /* Baca state dari file */
                /* NANTI GANTI JADI DARI FILE EKSTERNAL */
                CreateEmptyGraph(&Map);
                Gaddress P1 = AlokasiNodeGraph("../files/map1.txt");
                Gaddress P2 = AlokasiNodeGraph("../files/map2.txt");
                Gaddress P3 = AlokasiNodeGraph("../files/map3.txt");
                Gaddress P4 = AlokasiNodeGraph("../files/map4.txt");
                InsertLastGraph(&Map, P1);
                InsertLastGraph(&Map, P2);
                InsertLastGraph(&Map, P3);
                InsertLastGraph(&Map, P4);

                /* Load Wahana History */
                loadwahanahistory("../../WahanaHistory.txt",&ArrWahanaUpg);
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
                        /* Gaktau nambah waktu apa ngga, di contoh ngga kalo prep phase */
                        // if (moveStatus == 1)
                        // {
                        //     CurrentTime = NextNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID))));
                        // }
                        printf("\n");
                        break;
                    case 4:
                        /* BUILD */
                        printf("Ingin membangun apa?\n");
                        printf("List:\n");
                        AW_ListNamaWahana(WahanaDatabase); /* Harusnya BaseWahana */

                        MK_ADVKATAINPUT();
                        if (AW_SearchB(BuiltWahana, MK_CKata)) /* Nanti ada bug klo bisa dua wahana yg sama jdi fix sementara ini dlu */
                        {
                            printf("Anda sudah membangun wahana tersbeut\n");
                        }
                        else if (!AW_SearchB(WahanaDatabase, MK_CKata)) /* Harusnya BaseWahana */
                        {
                            printf("Input tidak valid\n");
                        }
                        else if (nearChar(P, '^') || nearChar(P, '>') || nearChar(P, 'V') || nearChar(P, '<'))
                        {
                            printf("Tidak bisa membangun wahana di sebelah gerbang\n");
                        }
                        else
                        {
                            int pushCode = 0;
                            while (T_Type(Surround(P)[pushCode]) != '-' && pushCode <= 3)
                            {
                                pushCode++;
                            }

                            if (pushCode == 4)
                            {
                                printf("Tidak bisa menempatkan wahana di sini\n");
                            }
                            else if ((JLT(DurasiJam(CurrentTime, OpeningTime), MenitToJAM(JAMToMenit(TotalTime(ActionStack))+JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 4)))))))
                            {
                                printf("Waktu yang dibutuhkan tidak cukup\n");
                            }
                            else
                            {
                                /* CEK RESOURCE DAN UANG PLAYER */
                                setTile(&Map, G_CurrentArea(Map), Pos(P), 'W', AW_GetId(WahanaDatabase, MK_CKata));

                                StackElmt = CreateStackInfo(MK_MakeKata("build", 5), A_Duration(AA_Elmt(ActionDatabase, 4)), 0/* Harusnya harga bangun wahana */, Pos(P));
                                Push(&ActionStack, StackElmt);

                                WBuilt = AW_GetWahana(WahanaDatabase, MK_CKata);
                                W_Location(WBuilt) = Pos(P);
                                W_WahanaId(WBuilt) = AW_GetId(WahanaDatabase, MK_CKata);

                                LL_CreateEmpty(&ArrWahanaUpg.Tab[W_WahanaId(WBuilt)]);
                                LL_InsVLast(&ArrWahanaUpg.Tab[W_WahanaId(WBuilt)],WBuilt);
                                
                                AW_AddAsLastEl(&BuiltWahana, WBuilt);
                                

                                move(&Map, &P, pushCode, &moveStatus);
                            }
                        }
                        break;
                    case 5:
                        /* UPGRADE */
                        /* CEK DISEBELAH WAHANA/TIDAK */
                        // boolean foundwahana = false;

                        // /* KALO IYA, NAMPILIN LIST UPGRADE */
                        // printf("Ingin melakukan upgrade apa?\n List:");
                        // for (size_t i = 0; i < 4; i++)
                        // {
                        //     if (T_Type(Surround(P)[i]) == 'W')
                        //     {
                        //         // NAMPILIN LIST UPGRADE UNTUK WAHANA DI POINT ITU (DARI TREE?)


                        //         foundwahana = true;
                        //     }
                        // }

                        // if (!foundwahana)
                        // {
                        //     printf("Tidak ada wahana di sekitar.");
                        // }
                        
                        break;
                    case 6: ;
                        /* BUY */
                        int matCount, price;
                        Kata matName;
                        printf("Ingin membeli apa?\n");
                        printf("List:\n");
                        AM_TulisIsiTab(MaterialDatabase);

                        /* Nerima input dengan format 'jumlah nama_material' */
                        MK_ADV();
                        MK_ADVKATA();
                        matCount = MK_KataToInt(MK_CKata);
                        MK_ADVKATA();
                        matName = MK_CKata;
                        price = matCount * AM_GetPrice(MaterialDatabase, matName);

                        if (!AM_SearchB(MaterialDatabase, matName))
                        {
                            printf("Input tidak valid\n");
                        }
                        else if (TotalMoney(ActionStack)+price > Money(P))
                        {
                            printf("Uang anda tidak cukup\n");
                        }
                        else if (JLT(DurasiJam(CurrentTime, OpeningTime), MenitToJAM(JAMToMenit(TotalTime(ActionStack))+JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, 6))))))
                        {
                            printf("Waktu yang dibutuhkan tidak cukup\n");
                        }
                        else
                        {
                            StackElmt = CreateStackInfo(MK_MakeKata("buy", 3), A_Duration(AA_Elmt(ActionDatabase, 6)), price, MakePOINT(-1,-1));
                            S_MatName(StackElmt) = matName;
                            S_MatCount(StackElmt) = matCount;
                            Push(&ActionStack, StackElmt);
                            // Money(P) -= price;
                            // AM_AddCount(&Materials(P), matName, matCount, AM_GetPrice(MaterialDatabase, matName));
                        }
                        printf("\n");
                        break;
                    case 7:
                        /* UNDO */
                        if (!IsEmptyStack(ActionStack))
                        {
                            Pop(&ActionStack, &StackElmt);
                            if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("build", 5)))
                            {
                                setTile(&Map, G_CurrentArea(Map), S_PosWahana(StackElmt), '-', -1);
                                setPlayer(GetMap(Map, G_CurrentArea(Map)), &P, Baris(Pos(P)), Kolom(Pos(P)));
                                AW_DelLastEl(&BuiltWahana, &WBuilt);
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
                            if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("buy", 3)))
                            {
                                Money(P) -= S_MoneyNeeded(StackElmt);
                                AM_AddCount(&Materials(P), S_MatName(StackElmt), S_MatCount(StackElmt), AM_GetPrice(MaterialDatabase, matName));
                            }
                            else if (MK_isKataSama(S_Name(StackElmt), MK_MakeKata("upgrade", 7)))
                            {
                                /* Blm tau sistem upgrade */
                            }
                            else /* build */
                            {
                                /* NGURANGIN UANG DAN RESOURCE PLAYER */
                            }

                        }
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;
                        randomPengunjung(&Antrian, BuiltWahana);
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
                            }
                        }
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;
                        randomPengunjung(&Antrian, BuiltWahana);
                        counter = 0;
                        break;
                    default:
                        break;
                    }
                }
                else /* Main Phase */
                {
                    
                    if ((JAMToMenit(DurasiJam(OpeningTime, CurrentTime)) / 45) > counter)
                    {
                        counter++;
                        processKesabaran(&Antrian);     
                    }                  

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
                                printf("Pengunjung tersebut tidak ingin menaiki wahana tersebut\n");
                                PQ_Enqueue(&Antrian, Pgj);
                            }
                            else
                            {
                                if (IsWahanaRusak(AW_GetWahana(BuiltWahana, MK_CKata)))
                                {
                                    printf("Wahana tersebut rusak\n");
                                    PQ_Enqueue(&Antrian, Pgj);
                                }
                                else
                                {
                                    
                                    Money(P) += AW_GetPrice(BuiltWahana, MK_CKata);
                                    CurrentTime = NextNMenit(CurrentTime, W_Duration(AW_GetWahana(BuiltWahana, MK_CKata)));
                                    AK_DelKata(&P_Wahana(Pgj), MK_CKata);
                                    if (AK_NbElmt(P_Wahana(Pgj)) > 0)
                                    {
                                        P_Prio(Pgj)--;
                                        PQ_Enqueue(&Antrian, Pgj);
                                    }
                                    int r = rand() % 100;
                                    if (r < 30)
                                    {
                                        AW_setRusak(&BuiltWahana, MK_CKata);
                                    }             
                                }                                
                            }
                        }   
                        break;
                    case 11:
                        /* REPAIR */
                        /* CEK SEKITAR KALO ADA WAHANA RUSAK, KALO ADA BENERIN, TAMBAHIN CURRENTTIME */
                        break;
                    case 12:
                        /* DETAIL */
                        for (size_t i = 0; i < 4; i++)
                        {
                            if (T_Type(Surround(P)[i]) == 'W')
                            {
                                AW_detailWahana(AW_GetWahanaId(BuiltWahana, T_ID(Surround(P)[i])),ArrWahanaUpg);
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
                        CurrentTime = MakeJAM(Day(CurrentTime)+1, 21, 0);
                        prepPhase = true;
                        break;
                    default:
                        break;
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
    int numPengunjung = rand() % PQ_MaxEl + 1;
    for (size_t i = 0; i < numPengunjung; i++)
    {
        Pengunjung Pgj;
        P_Kesabaran(Pgj) = 5;
        P_Prio(Pgj) = rand() % 100 + 20;
        AK_MakeEmpty(&P_Wahana(Pgj));
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
    int r = rand() % PQ_NBElmt(*Antrian);
    P_Kesabaran(PQ_Elmt(*Antrian, r))--;
    if (P_Kesabaran(PQ_Elmt(*Antrian, r)) == 0)
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

void initActionDatabase(ArrAction * AA)
/* Menginisialisasi array action yang dapat diisi semua action */
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
}