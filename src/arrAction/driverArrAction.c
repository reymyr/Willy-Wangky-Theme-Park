#include <stdio.h>

#include "arrAction.h"

int main()
{
    ArrAction T;
    AA_MakeEmpty(&T);
    int input;
    int id;
    long menit;
    Action ActTemp;
    do
    {
        printf("1. AddAsLastEl\n");
        printf("2. DelLastEl\n");
        printf("3. Search\n");
        printf("4. Test index\n");
        printf("5. Full/Empty\n");
        printf("6. Exit\n");

        printf("Isi Array:\n");
        AA_TulisIsiTab(T);
        printf("\n");

        printf("Pilihan: ");
        scanf("%d", &input);
        if (input == 6)
        {
            break;
        }

        switch (input)
        {
        case 1:

            printf("Id Action: ");
            scanf("%d", &id);           

            printf("Nama action: ");
            MK_STARTKATAINPUT();

            printf("Durasi Action (menit): ");
            scanf("%ld", &menit);

            AA_AddAsLastEl(&T, createAction(id, MK_CKata, MenitToJAM(menit)));

            break;
        case 2:
            if (AA_IsEmpty(T))
            {
                printf("Array kosong\n");
            }
            else
            {
                AA_DelLastEl(&T, &ActTemp);
                printf("Id action: %d\n", A_ActionID(ActTemp));
                printf("Nama action: "); MK_printKata(A_Name(ActTemp)); printf("\n");
                printf("Durasi action: "); TulisJAM(A_Duration(ActTemp)); printf("\n");
            }            
            break;
        case 3:
            printf("Nama action yang ingin dicari: ");
            MK_STARTKATAINPUT();
            if (!AA_SearchB(T, MK_CKata))
            {
                printf("Action tersebut tidak ada di array\n");
            }
            else
            {
                printf("Action ada pada index %d\n", AA_SearchI(T, MK_CKata));
            }          
            break;
        case 4:
            printf("Masukkan index: ");
            scanf("%d", &id);

            (AA_IsIdxEff(T, id) ? printf("Index efektif\n") : printf("Index tidak efektif\n"));
            (AA_IsIdxValid(T, id) ? printf("Index valid\n") : printf("Index tidak valid\n"));

            break;
        case 5:

            (AA_IsEmpty(T) ? printf("Array kosong\n") : printf("Array tidak kosong\n"));
            (AA_IsFull(T) ? printf("Array penuh\n") : printf("Array tidak penuh\n"));

            break;
        default:
            printf("Input tidak valid\n");
            break;
        }
        printf("\n");
    } while (true);    
    return 0;
}
