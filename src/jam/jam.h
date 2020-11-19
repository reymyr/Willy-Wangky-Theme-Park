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
/* Mengirim true jika D,H,M dapat membentuk JAM yang valid */

/*** Konstruktor ***/
JAM MakeJAM (int DD, int HH, int MM);
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk JAM */
void BacaJAM (JAM *J);
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen DD, HH, MM sehingga membentuk J */
void TulisJAM (JAM J);
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format Day DD - HH.MM
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll. */

/*** Konversi ***/
long JAMToMenit (JAM J);
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah menit dari pukul 0:0:0 */
/* Rumus : menit = 1440*DD + 60*HH + MM */
JAM MenitToJAM (long N);
/* Mengirim  konversi menit ke JAM */

/*** Operasi ***/
/*** Operator Relasional ***/
boolean JEQ (JAM J1, JAM J2);
/* Mengirimkan true jika J1=J2, false jika tidak */
boolean JNEQ (JAM J1, JAM J2);
/* Mengirimkan true jika J1 tidak sama dengan J2 */
boolean JLT (JAM J1, JAM J2);
/* Mengirimkan true jika J1<J2, false jika tidak */
boolean JGT (JAM J1, JAM J2);
/* Mengirimkan true jika J1>J2, false jika tidak */
/*** Operator Aritmatika ***/
JAM NextMenit (JAM J);
/* Mengirim 1 menit setelah J dalam bentuk JAM */
JAM NextNMenit (JAM J, int N);
/* Mengirim N menit setelah J dalam bentuk JAM */
JAM PrevMenit (JAM J);
/* Mengirim 1 menit sebelum J dalam bentuk JAM */
JAM PrevNMenit (JAM J, int N);
/* Mengirim N menit sebelum J dalam bentuk JAM */
long Durasi (JAM JAw, JAM JAkh);
/* Mengirim JAkh-JAw dlm menit, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */

#endif