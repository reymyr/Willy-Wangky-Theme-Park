#include "../boolean.h"
#include "mesinkar.h"
#include <string.h>
#include <stdio.h>
/* State Mesin */
char MK_CC;
boolean MK_EOP;

static FILE * MK_pita;
static int MK_retval;


void MK_STARTINPUT(string filename) {
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita. Jika CC != MARK maka EOP akan padam (false).
          Jika CC = MARK maka EOP akan menyala (true) */

	/* Algoritma */
	MK_pita = fopen(filename,"r");
	MK_ADV();
}


void MK_START(string filename){
/* Mesin siap dioperasikan. Pita disiapkan untuk dibaca.
   Karakter pertama yang ada pada pita posisinya adalah pada jendela.
   I.S. : sembarang
   F.S. : CC adalah karakter pertama pada pita
          Jika CC != MARK maka EOP akan padam (false)
          Jika CC = MARK maka EOP akan menyala (true) */
    MK_pita = fopen(filename,"r");
    MK_ADV();
}
void MK_ADV(){
/* Pita dimajukan satu karakter. 
   I.S. : Karakter pada jendela = CC, CC != MARK
   F.S. : CC adalah karakter berikutnya dari CC yang lama, 
          CC mungkin = MARK
          Jika  CC = MARK maka EOP akan menyala (true) */
    MK_retval = fscanf(MK_pita,"%c",&MK_CC);
    MK_EOP = (MK_CC==MK_MARK);
    if(MK_EOP){
        fclose(MK_pita);
    }
}