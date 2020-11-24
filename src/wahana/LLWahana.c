#include <stdio.h>
#include "../string_production/mesinkata.h"
#include "LLWahana.h"

//gcc -o wh wahanahistory.c wahana.c ../listlinier/listlinier.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../jam/jam.c ../point/point.c

void loadwahanahistory(char *filename, ArrAddressBaseWahana * A){
    int currentid;
    Wahana W;
    List WahanaHistory;

    MK_STARTKATAINPUT(filename);
    while (!MK_EndKata)
    {
        LL_CreateEmpty(&WahanaHistory);
        W_WahanaId(W) = MK_KataToInt(MK_CKata);
        currentid = W_WahanaId(W);
        while (currentid == W_WahanaId(W))
        {
            MK_ADVKATAINPUT();
            W_Name(W) = MK_CKata;
            MK_ADVKATAINPUT();
            W_Type(W) = MK_CKata;
            MK_ADVKATAINPUT();
            W_Price(W) = MK_KataToInt(MK_CKata);
            MK_ADVKATAINPUT();
            W_Location(W) = MK_KataToPoint(MK_CKata);
            MK_ADVKATAINPUT();
            W_Desc(W) = MK_CKata;
            MK_ADVKATAINPUT();
            W_Capacity(W) = MK_KataToInt(MK_CKata);
            MK_ADVKATAINPUT();
            W_Duration(W) = MK_KataToInt(MK_CKata);
            MK_ADVKATAINPUT();
            W_UseCount(W) = MK_KataToInt(MK_CKata);
            MK_ADVKATAINPUT();
            W_Penghasilan(W) = MK_KataToInt(MK_CKata);
            MK_ADVKATAINPUT();
            W_IsBroken(W) = MK_isKataSama(MK_CKata,MK_MakeKata("0",1))?false : true;
            W_TodayPenghasilan(W) = 0;
            W_TodayUseCount(W) = 0;
            LL_InsVLast(&WahanaHistory,W);
            MK_ADVKATAINPUT();
            if (!MK_EndKata){
                W_WahanaId(W) = MK_KataToInt(MK_CKata);
            } else{
                break;
            }
        }
        (*A).Tab[currentid] = WahanaHistory;
        (*A).Neff = currentid+1;
    }
}

void PrintWahanaHistory(Wahana W, ArrAddressBaseWahana A)
/* Menampilkan history dari wahana W*/
{
    LL_PrintInfoNamaWahana(A.Tab[W_WahanaId(W)]);
}