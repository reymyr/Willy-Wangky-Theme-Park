#include <stdio.h>
#include "wahana.h"

int main()
{
    ArrWahana AW;
    AW_BacaFile(&AW, "../../files/wahana.txt");

    AW_ListNamaWahana(AW); printf("\n");

    for (size_t i = 0; i < AW_NbElmt(AW); i++)
    {
        AW_detailWahana(AW_Elmt(AW, i));
        printf("\n");
        AW_reportWahana(AW_Elmt(AW, i));
        printf("\n");
    }
    
    return 0;
}
