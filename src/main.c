#include <stdio.h>
#include <stdlib.h>
#include "adt.h"

void initActionDatabase(ArrAction * AA);
/* Menginisialisasi array action yang dapat diisi semua action */
void initPrepActionArray(ArrAction * AA);
/* Menginisialisasi array action yang dapat dilakukan saat preparation phase */
void initMainActionArray(ArrAction * AA);
/* Menginisialisasi array action yang dapat dilakukan saat main phase */

int main()
{
    int moveStatus;
    ArrAction ActionDatabase;
    initActionDatabase(&ActionDatabase);
    ArrAction PrepActionArray;
    initPrepActionArray(&PrepActionArray);
    ArrAction MainActionArray;
    initMainActionArray(&MainActionArray);
    TabMaterial MaterialDatabase;
    JAM CurrentTime;
    JAM OpeningTime = MakeJAM(0, 9, 0);
    JAM ClosingTime = MakeJAM(0, 21, 0);
    Kata KATANEW = MK_MakeKata("new", 3);
    Kata KATALOAD = MK_MakeKata("load", 4);
    Kata KATAEXIT = MK_MakeKata("exit", 4);
    Graph Map;
    Player P;
    boolean prepPhase;

    AM_BacaFile(&MaterialDatabase, "../files/material.txt");

    printf("Welcome to Willy Wangky's\n");
    printf("Commands:\n");
    printf("new - New game\n");
    printf("load - Load game\n");
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
                /* insialisasi player dgn nama MK_CKata */
                Nama(P) = MK_CKata;
                Money(P) = 100;
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
                prepPhase = true;
                CurrentTime = MakeJAM(1, 21, 0);
            }
            else if (MK_isKataSama(MK_CKata, KATALOAD))
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
            }

            boolean lose = false;
 
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
                    printf("Total aksi yang akan dilakukan: \n"); /* diisi data dr stack (NBelmtStack) */
                    printf("Total waktu yang dilakukan: \n"); /* diisi data dr stack (build, buy, upgrade) */
                    printf("Total uang yang dilakukan: \n\n"); /* diisi data dr stack (build, buy, upgrade) */

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
                        if (moveStatus == 1)
                        {
                            CurrentTime = NextNMenit(CurrentTime, JAMToMenit(A_Duration(AA_Elmt(ActionDatabase, ActionID))));
                        }
                        printf("\n");
                        break;
                    case 4:
                        /* BUILD */
                        break;
                    case 5:
                        /* UPGRADE */
                        break;
                    case 6:
                        /* BUY */
                        break;
                    case 7:
                        /* UNDO */
                        break;
                    case 8:
                        /* EXECUTE */
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;
                        break;
                    case 9:
                        CurrentTime = MakeJAM(Day(CurrentTime), 9, 0);
                        prepPhase = false;
                        break;
                    default:
                        break;
                    }
                    
                }
                else /* Main Phase */
                {
                    printf("Main Phase Day %d\n", Day(CurrentTime)); 
                    printCurrentMap(Map, P);
                }

            } while (!lose && !MK_EndKata);
            
        }        
        else
        {
            printf("Thank you for playing!!!\n");
            break;
        }
    }
    return 0;
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
    AA_AddAsLastEl(AA, createAction(12, MK_MakeKata("detail", 3), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(13, MK_MakeKata("office", 4), MakeJAM(0,0,0)));
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
    AA_AddAsLastEl(AA, createAction(12, MK_MakeKata("detail", 3), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(13, MK_MakeKata("office", 4), MakeJAM(0,0,0)));
    AA_AddAsLastEl(AA, createAction(14, MK_MakeKata("prepare", 7), MakeJAM(0,0,0)));
}