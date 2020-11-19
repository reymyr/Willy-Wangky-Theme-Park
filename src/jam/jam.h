/* File header ADT Jam */

#ifndef JAM_H
#define JAM_H

#include "../boolean.h"

/* *** Definisi TYPE JAM <DD:HH:MM> *** */
typedef struct {
   int DD; /* integer[0..] */
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
} JAM;

/*** Selektor ***/
#define Day(J) (J).DD
#define Hour(J) (J).HH
#define Minute(J) (J).MM

/*** Validasi ***/
boolean IsJAMValid (int D, int H, int M);

/*** Konstruktor ***/
JAM MakeJAM (int HH, int MM);
void BacaJAM (JAM * J);
void TulisJAM (JAM J);

/*** Konversi ***/
long JAMToMenit (JAM J);
JAM MenitToJAM (long N);

/*** Operasi ***/
/*** Operator Relasional ***/
boolean JEQ (JAM J1, JAM J2);
boolean JNEQ (JAM J1, JAM J2);
boolean JLT (JAM J1, JAM J2); /* J1 < J2 */
boolean JGT (JAM J1, JAM J2); /* J1 > J2 */
/*** Operator Aritmatika ***/
JAM NextMenit (JAM J);
JAM NextNMenit (JAM J, int N);
JAM PrevMenit (JAM J);
JAM PrevNMenit (JAM J, int N);
long Durasi (JAM JAw, JAM JAkh);

#endif