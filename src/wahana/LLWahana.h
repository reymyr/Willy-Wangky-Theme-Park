
#ifndef LLWAHANA_H
#define LLWAHANA_H

#include "wahana.h"
#include "../listlinier/listlinier.h"

#define MaxWahana 50

typedef struct arrListWahanaUpg{
    List Tab[MaxWahana];
    int Neff;
} ArrListWahanaUpg;

#define NEff_ArrListWahanaUpg(A) (A).Neff
#define WU_Info(A,i) (A).Tab[i]

void WU_CreateEmpty(ArrListWahanaUpg* A);
/* I.S A sembarang, F.S A merupakan sebuah Array kosong (Neff=0) */

boolean WU_IsEmpty(ArrListWahanaUpg A);
/* Mengembalikan True jika Neff A = 0, false jika tidak*/

void loadwahanahistory(char *filename, ArrListWahanaUpg * A);
/* Melakukan load data dari file wahana history, tiap wahana dan history upgradenya disimpan pada sebuah List berkait, dan tiap List dicatat pada Array of List A */

void savewahanahistory(char *filename, ArrListWahanaUpg A);
/* Menyalin dan menyimpan riwayat wahana pada array A ke file eksternal*/

void PrintWahanaHistory(int idx, ArrListWahanaUpg A);
/* Menampilkan History Upgrade Wahana W */

boolean IsWahanaRusak(Wahana W);
/* Mengembalikan true jika Wahana rusak dan false jika tidak*/

void WU_AddAsLastEl(ArrListWahanaUpg *A, List X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

#endif