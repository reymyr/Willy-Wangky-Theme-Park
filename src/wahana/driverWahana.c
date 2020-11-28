#include <stdio.h>
#include "wahana.h"
#include "ArrWahana.h"
#include "LLWahana.h"

int main()
{
    ArrListWahanaUpg A;
    ArrWahana AW;

    WU_CreateEmpty(&A);
    loadwahanahistory("testwahanahistory.txt",&A);

    printf("History wahana yang terbaca:\n");
    for (size_t i = 0; i < NEff_ArrListWahanaUpg(A); i++)
    {
        PrintWahanaHistory(i, A); printf("\n");
    }
    
    savewahanahistory("hasilsavehistory.txt",A);

    AW_BacaFile(&AW, "testwahana.txt");

    printf("Hasil nama wahana yang terbaca: \n");
    AW_ListNamaWahana(AW); printf("\n");

    ArrListWahanaUpg A2;
    WU_CreateEmpty(&A2);

    printf("Detail dan Report:\n");
    for (size_t i = 0; i < AW_NbElmt(AW); i++)
    {
        AW_detailWahana(AW, AW_Elmt(AW, i), A2);
        printf("\n");
        AW_reportWahana(AW_Elmt(AW, i));
        printf("\n");
    }
    return 0;
}

