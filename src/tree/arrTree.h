#ifndef _ARRTREE_H_
#define _ARRTREE_H_

#include "bintree.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;

typedef struct {
    BinTree Tab[IdxMax+1];
    int Neff;
} ArrTree;

#define AT_Neff(A) (A).Neff
#define AT_Elmt(A,i) (A).Tab[i]

void AT_MakeEmpty(ArrTree *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */

IdxType AT_SearchI(ArrTree T, BT_infotype x);
/* Mengembalikan index tree dalam array yang memiliki Akar(P) = x */

BinTree AT_SearchBase(ArrTree T, BT_infotype x);
/* Mengembalikan tree dalam array yang memiliki Akar(P) = x */

#endif