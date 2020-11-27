
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

void PrintWahanaHistory(Wahana W, ArrListWahanaUpg A);
/* Menampilkan History Upgrade Wahana W */

boolean IsWahanaRusak(Wahana W);
/* Mengembalikan true jika Wahana rusak dan false jika tidak*/

void UpgradeWahana(Wahana W0, Wahana W1, ArrListWahanaUpg A);
/* Meng-upgrade Wahana W0 menjadi Wahana W1 */
/* I.S : Asumsi W1 sudah valid merupakan upgrade dari wahana W0*/
#endif