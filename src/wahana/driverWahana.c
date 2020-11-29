#include <stdio.h>
#include "wahana.h"
#include "ArrWahana.h"
#include "LLWahana.h"

/* gcc driverWahana.c ArrWahana.c LLWahana.c ../listlinier/listlinier.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../point/point.c ../arrMaterial/arrMaterial.c ../tree/arrTree.c ../tree/bintree.c -o driverW -lm */

int main()
{
    ArrListWahanaUpg A;
    WU_CreateEmpty(&A);
    loadwahanahistory("testwahanahistory.txt",&A);

    for (int i=0;i<A.Neff;i++){
        printf("\n");
        AW_detailWahana(Info(First(A.Tab[i])),A);
    }

    ArrWahana AW;
    printf("\nMembaca file 'testwahana.txt'\n");
    AW_BacaFile(&AW, "testwahana.txt");

    printf("List nama wahana yang terbaca:\n");
    AW_ListNamaWahana(AW); printf("\n\n");

    printf("Menyimpan history di file 'savedWahanHistory.txt'...\n");
    savewahanahistory("savedWahanHistory.txt",A);


    return 0;
}

