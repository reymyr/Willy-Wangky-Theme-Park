#include <stdio.h>
#include "adt.h"

int main()
{
    ArrAction ActionDatabase;
    TabMaterial MaterialDatabase;
    JAM CurrentTime;
    JAM OpeningTime = MakeJAM(0, 9, 0);
    JAM ClosingTime = MakeJAM(0, 21, 0);
    Kata NEW = MK_MakeKata("new", 3);
    Kata LOAD = MK_MakeKata("load", 4);
    Kata EXIT = MK_MakeKata("exit", 4);
    Peta Map;
    boolean prepPhase = true;

    AM_BacaFile(&MaterialDatabase, "../files/material.txt");

    printf("Welcome to Willy Wangky's\n");
    printf("Commands:\n");
    printf("new - New game\n");
    printf("load - Load game\n");
    printf("exit - Exit game\n\n");

    MK_STARTKATAINPUT();
    while (!MK_EndKata)
    {   
        while (!MK_isKataSama(MK_CKata, NEW) && !MK_isKataSama(MK_CKata, LOAD) && !MK_isKataSama(MK_CKata, EXIT))
        {
            printf("Input tidak valid\n");
            MK_ADVKATAINPUT();
        }
        
        if (!MK_isKataSama(MK_CKata, EXIT))
        {
            if (MK_isKataSama(MK_CKata, NEW))
            {
                printf("Memulai permainan baru...\n");
                printf("Masukkan nama: ");
                MK_ADVKATAINPUT();
                /* insialisasi player dgn nama MK_CKata */
                printf("Selamat bermain, ");
                MK_printKata(MK_CKata); printf("\n");

                /* Inisialisasi data game lain */
                CurrentTime = MakeJAM(1, 21, 0);
                BacaPeta(&Map, "../files/map1.txt");
            }
            else if (MK_isKataSama(MK_CKata, LOAD))
            {
                printf("Load game\n");
                /* Baca state dari file */
                BacaPeta(&Map, "../files/map1.txt"); /* diganti jadi map hasil save */
            }

            boolean lose = false;
            PrintAreai(Map, 0);

            MK_STARTKATAINPUT();
            do
            {
                MK_printKata(MK_CKata); printf("\n");
                MK_ADVKATAINPUT();
                /* GANTI JADI GAME LOGIC */
                /* Preparation Phase */
                

                /* Main Phase */

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
