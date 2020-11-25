
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

void WU_CreateEmpty(ArrListWahanaUpg* A);
/* I.S A sembarang, F.S A merupakan sebuah Array kosong (Neff=0) */

void loadwahanahistory(char *filename, ArrListWahanaUpg * A);
/* Melakukan load data dari file wahana history, tiap wahana dan history upgradenya disimpan pada sebuah List berkait, dan tiap List dicatat pada Array of List A */

void PrintWahanaHistory(Wahana W, ArrListWahanaUpg A);
/* Menampilkan History Upgrade Wahana W */

boolean IsWahanaRusak(Wahana W);
/* Mengembalikan true jika Wahana rusak dan false jika tidak*/

void RepairWahanaRusak(Wahana W);
/* I.S : W_IsBroken(W) = true, F.S. : W_IsBroken(W) = false*/


#endif