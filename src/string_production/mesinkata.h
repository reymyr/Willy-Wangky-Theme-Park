#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean.h"
#include "mesinkar.h"
#include <string.h>

#define MK_NMax 50
#define MK_BLANK ' '

typedef struct {
	char TabKata[MK_NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
    int Length;
} MK_Kata;

/* State Mesin Kata */
extern boolean MK_EndKata;
extern MK_Kata MK_CKata;

void MK_IgnoreBlank();
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void MK_STARTKATA(string filename);
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void MK_ADVKATA();
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void MK_SalinKata();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

#endif

