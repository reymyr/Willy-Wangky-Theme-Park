#include <stdio.h>
#include "wahana.h"
#include "ArrWahana.h"
#include "LLWahana.h"

int main()
{
    ArrListWahanaUpg A;
    WU_CreateEmpty(&A);
    loadwahanahistory("../../files/WahanaHistory.txt",&A);

    for (int i=0;i<A.Neff;i++){
        AW_detailWahana(Info(First(A.Tab[i])),A);
    }

    savewahanahistory("testwahanahist.txt",A);

    ArrWahana AW;
    AW_BacaFile(&AW, "../../files/wahana.txt");

    AW_ListNamaWahana(AW); printf("\n");

    UpgradeWahana(Info(First(WU_Info(A,0))),AW.T[0],A);

    AW_detailWahana(Info(First(WU_Info(A,0))),A);

    savewahanahistory("testwahanahist.txt",A);


    
    // for (size_t i = 0; i < AW_NbElmt(AW); i++)
    // {
    //     AW_detailWahana(AW_Elmt(AW, i));
    //     printf("\n");
    //     AW_reportWahana(AW_Elmt(AW, i));
    //     printf("\n");
    // }
    return 0;
}

