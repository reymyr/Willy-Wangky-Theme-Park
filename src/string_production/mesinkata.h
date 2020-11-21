#ifndef __MESINKATA_H__
#define __MESINKATA_H__

#include "../boolean.h"
#include "mesinkar.h"
#include <string.h>

#define MK_NMax 50
#define MK_BLANK ' '
#define MK_NEWLINE '\n'

typedef struct {
	char TabKata[MK_NMax]; /* container penyimpan kata, indeks yang dipakai [0..NMax-1] */
    int Length;
} Kata;

/* State Mesin Kata */
extern boolean MK_EndKata;
extern Kata MK_CKata;

/* Mesin Kata input */
void MK_IgnoreNewline();
/* Mengabaikan satu atau beberapa NEWLINE
   I.S. : MK_CC sembarang 
   F.S. : MK_CC ≠ NEWLINE atau MK_CC = MARK */

void MK_STARTKATAINPUT();
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void MK_ADVKATAINPUT();
/* I.S. : MK_CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          MK_CC adalah karakter pertama dari kata berikutnya, mungkin MK_MK_MARK
          Jika MK_CC = MK_MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void MK_SalinKataInput();
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */


/* Mesin Kata file */
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

void MK_printKata(Kata kata);
/* I.S. : Sembarang 
   F.S. : kata tertulis di layar */

Kata MK_MakeKata(char* string, int len);
/* Mengubah string menjadi Kata dan mengembalikannya */

boolean MK_isKataSama(Kata K1, Kata K2);
/* Mengembalikan true jika K1 = K2, false jika tidak */

int MK_CToI(char c);
/* Mengubah karakter ke integer */

int MK_KataToInt(Kata K);
/* Mengubah kata ke integer */

#endif

