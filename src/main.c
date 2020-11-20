#include <stdio.h>
#include "adt.h"

int main()
{
    boolean started = false;
    Kata NEW = MK_MakeKata("new", 3);
    Kata LOAD = MK_MakeKata("load", 4);
    Kata EXIT = MK_MakeKata("exit", 4);
    Peta Map;

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
                printf("Selamat bermain, ");
                MK_printKata(MK_CKata); printf("\n");

                /* Inisialisasi player baru */
                BacaPeta(&Map, "../files/map1.txt");
            }
            else if (MK_isKataSama(MK_CKata, LOAD))
            {
                printf("Load game\n");
                /* Baca state dari file */
                BacaPeta(&Map, "../files/map1.txt");
            }

            boolean lose = false;
            PrintAreai(Map, 0);

            MK_STARTKATAINPUT();
            do
            {
                /* GANTI JADI GAME LOGIC */
                MK_printKata(MK_CKata); printf("\n");
                MK_ADVKATAINPUT();
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
