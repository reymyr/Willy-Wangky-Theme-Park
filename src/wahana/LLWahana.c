#include <stdio.h>
#include "../string_production/mesinkata.h"
#include "LLWahana.h"

//gcc -o wh wahanahistory.c wahana.c ../listlinier/listlinier.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../jam/jam.c ../point/point.c

void WU_CreateEmpty(ArrListWahanaUpg* A)
/* I.S A sembarang, F.S A merupakan sebuah Array kosong (Neff=0) */
{
    NEff_ArrListWahanaUpg(*A) = 0;
}

boolean WU_IsEmpty(ArrListWahanaUpg A)
/* Mengembalikan True jika Neff A = 0, false jika tidak*/
{
    return NEff_ArrListWahanaUpg(A) == 0;
}


void loadwahanahistory(char *filename, ArrListWahanaUpg * A){
    int currentid;
    Wahana W;
    List WahanaHistory;

    MK_STARTKATA(filename);
    while (!MK_EndKata)
    {
        LL_CreateEmpty(&WahanaHistory);
        W_WahanaId(W) = MK_KataToInt(MK_CKata);
        currentid = W_WahanaId(W);
        printf("%d",currentid);
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
            MK_ADV();
            MK_ADVKATA();
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


void savewahanahistory(char *filename, ArrListWahanaUpg A){
/* Menyalin dan menyimpan riwayat wahana pada array A ke file eksternal*/
    FILE * f = fopen(filename,"w");

    for (int i = 0; i < NEff_ArrListWahanaUpg(A); i++){
        LL_writeList(f,WU_Info(A,i));
        if (i != NEff_ArrListWahanaUpg(A)-1)
        {
            fprintf(f,"%c",MK_NEWLINE);
        }   
    }
    fprintf(f,"%c",MK_MARK);
    
    fclose(f);   
}

void PrintWahanaHistory(Wahana W, ArrListWahanaUpg A)
/* Menampilkan history dari wahana W*/
{
    LL_PrintInfoNamaWahana(A.Tab[W_BaseId(W)]);
}

boolean IsWahanaRusak(Wahana W){
    return W_IsBroken(W) == true;
}