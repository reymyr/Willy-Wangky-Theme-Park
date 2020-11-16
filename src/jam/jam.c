/* Realisasi ADT Jam */

#include <stdio.h>
#include "jam.h"

/* ***Konstruktor: Membuat jam mulai game*** */
JAM MakeJAM (int DD, int HH, int MM)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : DD, HH, MM valid untuk membentuk JAM */
{
    JAM J;

    Day(J) = DD;
    Hour(J) = HH;
    Minute(J) = MM;

    return J;
}

void StartJAM (JAM *J)
/* I.S. : J sembarang */
/* F.S. : Jam terdefinisi sebagai waktu start game */
/* Proses : Setiap komponen J didefinisikan menjadi 0 */
{
    Day(*J) = 0;
    Hour(*J) = 0;
    Minute(*J) = 0;
}

/* ***Menuliskan jam*** */
void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. : Nilai J tertulis dalam format HH.MM */
/* Proses : Menuliskan nilai komponen J ke layar dengan format HH.MM */
{
    printf("%d.%d", Hour(J), Minute(J));
}

/* ***Memproses jam*** */
void ProsesJAM (JAM *J, int N)
/* I.S. : J sembarang */
/* F.S. : J telah diproses */
/* Proses : Menjumlahkan komponen menit (MM) dalam J sebanyak N
            Jika MM > 59, MM diubah menjadi MM mod 60 dan HH bertambah 1
            Jika HH > 23, HH diubah menjadi HH mod 24 dan DD bertambah 1
*/
{
    Minute(*J) += N;

    if (Minute(*J) > 59){
        int addHour = Minute(*J) / 60;
        Hour(*J) += addHour;
        Minute(*J) %= 60;

        if (Hour(*J) > 23){
            int addDay = Hour(*J) / 24;
            Day(*J) += addDay;
            Hour(*J) %= 24;
        }
    }
}