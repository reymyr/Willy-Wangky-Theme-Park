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
    int idx = 0;
    List WahanaHistory;
    LL_CreateEmpty(&WahanaHistory);
    WU_CreateEmpty(A);

    MK_STARTKATA(filename);
    (*A).Neff = MK_KataToInt(MK_CKata);
    MK_ADVKATAINPUT();
    while (!MK_EndKata)
    {
        LL_InsVLast(&WahanaHistory, MK_CKata);
        if (MK_CC == MK_NEWLINE || MK_CC == MK_MARK)
        {
            (*A).Tab[idx] = WahanaHistory;
            idx++;
            LL_CreateEmpty(&WahanaHistory);
        }
        MK_ADVKATAINPUT();
    }
}


void savewahanahistory(char *filename, ArrListWahanaUpg A){
/* Menyalin dan menyimpan riwayat wahana pada array A ke file eksternal*/
    FILE * f = fopen(filename,"w");

    fprintf(f, "%d\n", NEff_ArrListWahanaUpg(A));
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

void PrintWahanaHistory(int idx, ArrListWahanaUpg A)
/* Menampilkan history dari wahana W*/
{
    LL_PrintInfoNamaWahana(A.Tab[idx]);
}

boolean IsWahanaRusak(Wahana W)
/* Mengembalikan true jika Wahana rusak dan false jika tidak*/
{
    return W_IsBroken(W) == true;
}

void WU_AddAsLastEl(ArrListWahanaUpg *A, List X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    if (WU_IsEmpty(*A))
    {
        WU_Info(*A, IdxMin) = X;
        NEff_ArrListWahanaUpg(*A) = 1;
    }
    else
    {
        WU_Info(*A, NEff_ArrListWahanaUpg(*A)) = X;
        NEff_ArrListWahanaUpg(*A)++;
    }    
}