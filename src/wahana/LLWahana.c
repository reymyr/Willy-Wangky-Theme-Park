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


void loadwahanahistory(char *filename, ArrListWahanaUpg * A)
/* Melakukan load data dari file wahana history, tiap wahana dan history upgradenya disimpan pada sebuah List berkait, dan tiap List dicatat pada Array of List A */
{
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

int SearchIdxByLoc(int W_Area, POINT W_Location, ArrListWahanaUpg A){
/* Mengembalikan indeks dari list yg menyimpan history wahana pada area W_Area , W_Locatio  pada array A*/
    boolean found = false;
    int id = 0;
    while (!found && id< NEff_ArrListWahanaUpg(A)){
        if (W_Area(Info(First(WU_Info(A,id))))== W_Area && PointEQ(W_Location , W_Location(Info(First(WU_Info(A,id)))))){
            found = true;
        } else{
            id++;
        }
    }
    if (found){
        return id;
    } else
    {
        return -1;
    }
}

void PrintWahanaHistory(int W_Area, POINT W_Location , ArrListWahanaUpg A)
/* Menampilkan history dari wahana W*/
{
    // Cari wahana pada W_Area dan W_Location
    int id = SearchIdxByLoc(W_Area,W_Location,A);
    if (id != -1){
        LL_PrintInfoNamaWahana(WU_Info(A,id));
    } else
    {
        printf("Wahana tidak ditemukan.");
    }
}

void WU_Build(ArrListWahanaUpg * A, Wahana W){
/* Menambahkan elemen list baru pada array A yang berisi wahana W yaitu wahana yang akan dibangun*/
    LL_CreateEmpty(&WU_Info(*A,NEff_ArrListWahanaUpg(*A)));
    LL_InsVLast(&WU_Info(*A,NEff_ArrListWahanaUpg(*A)),W);
    NEff_ArrListWahanaUpg(*A)++;
}

boolean IsWahanaRusak(Wahana W)
/* Mengembalikan true jika Wahana rusak dan false jika tidak*/
{
    return W_IsBroken(W) == true;
}