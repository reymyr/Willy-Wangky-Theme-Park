/* File header ADT Jam */

#ifndef JAM_H
#define JAM_H

/* *** Definisi TYPE JAM <HH:MM  DD> *** */
typedef struct {
   int DD; /* hari, integer */
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
} JAM;

/* *** Notasi Akses: selektor JAM *** */
#define Day(J) (J).DD
#define Hour(J) (J).HH
#define Minute(J) (J).MM

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int DD, int HH, int MM);
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, DD valid untuk membentuk JAM */

void StartJAM (JAM *J);
/* I.S. : J sembarang */
/* F.S. : Jam terdefinisi sebagai waktu start game */
/* Proses : Setiap komponen J didefinisikan menjadi 0 */

void TulisJAM (JAM J);
/* I.S. : J sembarang */
/* F.S. : Nilai J tertulis dalam format HH.MM */
/* Proses : Menuliskan nilai komponen J ke layar dengan format HH.MM */

void ProsesJAM (JAM *J, int N);
/* I.S. : J sembarang */
/* F.S. : J telah diproses */
/* Proses : Menjumlahkan komponen menit (MM) dalam J sebanyak N
            Jika MM > 59, MM diubah menjadi MM mod 60 dan HH bertambah 1
            Jika HH > 23, HH diubah menjadi HH mod 24 dan DD bertambah 1
*/

#endif