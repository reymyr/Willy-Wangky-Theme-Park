#include "../boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <string.h>

/* State Mesin Kata */
boolean MK_EndKata;
MK_Kata MK_CKata;

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

