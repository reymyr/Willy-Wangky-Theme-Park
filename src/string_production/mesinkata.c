#include "../boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <string.h>
#include <stdio.h>

/* State Mesin Kata */
boolean MK_EndKata;
Kata MK_CKata;

/* Mesin Kata input */
void MK_IgnoreNewline(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : MK_CC sembarang 
   F.S. : MK_CC ≠ BLANK atau MK_CC = MARK */
    while(MK_CC==MK_NEWLINE){
        MK_ADV();
    }
    return;
}

void MK_STARTKATAINPUT()
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
    MK_STARTINPUT();
    MK_IgnoreNewline();
    if (MK_CC == MK_MARK)
    {
        MK_EndKata = true;
    }
    else
    {
        MK_EndKata = false;
        MK_SalinKataInput();
    }    
}

void MK_ADVKATAINPUT()
/* I.S. : MK_CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          MK_CC adalah karakter pertama dari kata berikutnya, mungkin MK_MK_MARK
          Jika MK_CC = MK_MARK, EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure SalinKata */
{
    MK_IgnoreNewline();
    if (MK_CC == MK_MARK)
    {
        MK_EndKata = true;
    }
    else
    {
        MK_SalinKataInput();
    }    
}

void MK_SalinKataInput()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
    int i = 0;
    while (MK_CC != MK_MARK && MK_CC != MK_NEWLINE && i < MK_NMax)
    {
        MK_CKata.TabKata[i] = MK_CC;
        i++;
        MK_ADV();
    }
    MK_CKata.Length = i;
}

/* Mesin Kata file */
void MK_IgnoreBlank(){
/* Mengabaikan satu atau beberapa BLANK
   I.S. : MK_CC sembarang 
   F.S. : MK_CC ≠ BLANK atau MK_CC = MARK */
    while(MK_CC==MK_BLANK){
        MK_ADV();
    }
    return;
}
void MK_STARTKATA(string filename){
/* I.S. : MK_CC sembarang 
   F.S. : MK_EndKata = true, dan MK_CC = MARK; 
          atau MK_EndKata = false, MK_CKata adalah kata yang sudah diakuisisi,
          MK_CC karakter pertama sesudah karakter terakhir kata */
    MK_START(filename);
    MK_IgnoreBlank();
    if(MK_CC==MK_MARK){
        MK_EndKata = true;
    }
    else{
        MK_EndKata = false;
        MK_SalinKata();
    }
    return;
}
void MK_ADVKATA(){
/* I.S. : MK_CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : MK_CKata adalah kata terakhir yang sudah diakuisisi, 
          MK_CC adalah karakter pertama dari kata berikutnya, mungkin MK_MARK
          Jika MK_CC = MK_MARK, MK_EndKata = true.		  
   Proses : Akuisisi kata menggunakan procedure MK_SalinKata */
    MK_IgnoreBlank();
    if(MK_CC==MK_MARK){
        MK_EndKata = true;
    }
    else{
        MK_EndKata = false;
        MK_SalinKata();
    }
    return;
}
void MK_SalinKata(){
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
    int i;
    i = 0;
    while((MK_CC!=MK_MARK)&&(MK_CC!=MK_BLANK)&&(i<MK_NMax)){
        MK_CKata.TabKata[i]=MK_CC;
        MK_ADV();
        i++;
    }
    while((MK_CC!=MK_MARK)&&(MK_CC!=MK_BLANK)){
        MK_ADV();
    }
    MK_IgnoreBlank();
    MK_CKata.Length = i;
    return;
}

void MK_printKata(Kata kata)
/* I.S. : Sembarang 
   F.S. : kata tertulis di layar */
{
    for (size_t i = 0; i < kata.Length; i++)
    {
        printf("%c", kata.TabKata[i]);
    }   
}

Kata MK_MakeKata(char* string, int len)
/* Mengubah string menjadi Kata dan mengembalikannya */
{
   Kata K;
   for (size_t i = 0; i < len; i++)
   {
       K.TabKata[i] = string[i];
   }
   
   K.Length = len;
   return K;
}

boolean MK_isKataSama(Kata K1, Kata K2)
/* Mengembalikan true jika K1 = K2, false jika tidak */
{
    if (K1.Length != K2.Length)
    {
        return false;
    }
    else
    {
        boolean sama = true;
        int i = 0;
        while (sama && i < K1.Length)
        {
            if (K1.TabKata[i] != K2.TabKata[i])
            {
                sama = false;
            }
            i++;
        }
        return sama;
    }
}