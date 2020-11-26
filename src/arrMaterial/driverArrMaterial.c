#include <stdio.h>

#include "arrMaterial.h"
#include "../string_production/mesinkata.h"

int main()
{

    TabMaterial T;
    
    AM_MakeEmpty(&T);
    int input;
    int cnt, price, id;
    Material MatTemp;
    do
    {
        printf("1. AddAsLastEl\n");
        printf("2. DelLastEl\n");
        printf("3. Search\n");
        printf("4. Test index\n");
        printf("5. Full/Empty\n");
        printf("6. Baca dari file\n");
        printf("7. Exit\n");

        printf("Isi Array:\n");
        AM_TulisIsiTab(T);
        printf("\n");

        printf("Pilihan: ");
        scanf("%d", &input);
        if (input == 7)
        {
            break;
        }

        switch (input)
        {
        case 1:


            printf("Nama Material: ");
            MK_STARTKATAINPUT();

            printf("Jumlah Material: ");
            scanf("%d", &cnt);           

            printf("Harga Material: ");
            scanf("%d", &price);

            AM_AddAsLastEl(&T, createMaterial(MK_CKata, cnt, price));

            break;
        case 2:
            if (AM_IsEmpty(T))
            {
                printf("Array kosong\n");
            }
            else
            {
                AM_DelLastEl(&T, &MatTemp);
                printf("Nama material:"); MK_printKata(M_Name(MatTemp)); printf("\n");
                printf("Junmlah: %d\n",  M_Count(MatTemp));
                printf("Harga: %d\n", M_Price(MatTemp)); 
            }            
            break;
        case 3:
            printf("Nama material yang ingin dicari: ");
            MK_STARTKATAINPUT();
            if (!AM_SearchB(T, MK_CKata))
            {
                printf("Material tersebut tidak ada di array\n");
            }
            else
            {
                printf("Material ada pada index %d\n", AM_SearchI(T, MK_CKata));
            }          
            break;
        case 4:
            printf("Masukkan index: ");
            scanf("%d", &id);

            (AM_IsIdxEff(T, id) ? printf("Index efektif\n") : printf("Index tidak efektif\n"));
            (AM_IsIdxValid(T, id) ? printf("Index valid\n") : printf("Index tidak valid\n"));

            break;
        case 5:

            (AM_IsEmpty(T) ? printf("Array kosong\n") : printf("Array tidak kosong\n"));
            (AM_IsFull(T) ? printf("Array penuh\n") : printf("Array tidak penuh\n"));

            break;
        case 6:
            AM_BacaFile(&T, "../../files/material.txt");
            break;
        default:
            printf("Input tidak valid\n");
            break;
        }
        printf("\n");
    } while (true);    

    
    return 0;
}
