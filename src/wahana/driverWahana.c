#include <stdio.h>
#include "wahana.h"
#include "ArrWahana.h"
#include "LLWahana.h"

int main()
{
    ArrListWahanaUpg A;
    WU_CreateEmpty(&A);
    loadwahanahistory("../../files/wahanahistory.txt",&A);

    for (int i=0;i<A.Neff;i++){
        AW_detailWahana(Info(First(A.Tab[i])),A);
    }


    ArrWahana AW;
    AW_BacaFile(&AW, "testwahana.txt");

    AW_ListNamaWahana(AW); printf("\n");

    AW_detailWahana(Info(First(WU_Info(A,0))),A);

    savewahanahistory("testwahanahist.txt",A);


    return 0;
}

