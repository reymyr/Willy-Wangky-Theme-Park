#include <stdio.h>
#include "wahana.h"
#include "ArrWahana.h"
#include "LLWahana.h"

int main()
{
    ArrAddressBaseWahana A;
    loadwahanahistory("../../files/WahanaHistory.txt",&A);

    for (int i=0;i<A.Neff;i++){
        AW_detailWahana(Info(First(A.Tab[i])),A);
    }


    // ArrWahana AW;
    // AW_BacaFile(&AW, "../../files/wahana.txt");

    // AW_ListNamaWahana(AW); printf("\n");

    // for (size_t i = 0; i < AW_NbElmt(AW); i++)
    // {
    //     AW_detailWahana(AW_Elmt(AW, i));
    //     printf("\n");
    //     AW_reportWahana(AW_Elmt(AW, i));
    //     printf("\n");
    // }
    
    return 0;
}


// gcc -o wh driverWahana.c Arrwahana.c ../listlinier/listlinier.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../jam/jam.c ../point/point.c LLWahana.c