/* Realisasi ADT Jam */

#include <stdio.h>
#include "jam.h"
#include "../boolean.h"

/*** Validasi ***/
boolean IsJAMValid (int D, int H, int M)
/* Mengirim true jika D,H,M dapat membentuk JAM yang valid */
{
   return ((D >= 0) && (H >= 0 && H <= 23) && (M >= 0 && M <= 59));
}

/*** Konstruktor ***/
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

void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen DD, HH, MM sehingga membentuk J */
{
    int DD, HH, MM;

    do{
        printf("Masukkan day: "); scanf("%d", &DD);
        printf("Masukkan jam: "); scanf("%d", &HH);
        printf("Masukkan menit: "); scanf("%d", &MM);
    } while (!IsJAMValid(DD, HH, MM));

   *J = MakeJAM(DD, HH, MM);
}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. : Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format Day DD - HH.MM
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll. */
{
    printf("%02d.%02d", Hour(J), Minute(J));
}

void TulisJamMenit (JAM J)
/* I.S : J terdefinisi */
/* Menulis Jam dan Menit dari J */
{
    if (Hour(J) != 0)
    {
        printf("%d hour(s) ", Hour(J));
    }
    if (Minute(J) != 0)
    {
        printf("%d minute(s)", Minute(J));
    }
}

/*** Konversi ***/
long JAMToMenit (JAM J)
/* Diberikan sebuah JAM, mengkonversi menjadi jumlah menit dari pukul 0:0:0 */
/* Rumus : menit = 1440*DD + 60*HH + MM */
{
    return(1440 * Day(J) + 60 * Hour(J) + Minute(J));  
}

JAM MenitToJAM (long N)
/* Mengirim  konversi menit ke JAM */
{
    JAM J;
    int remainder;

    Day(J) = N / 1440;
    remainder = N % 1440;
    Hour(J) = remainder / 60;
    Minute(J) = remainder % 60;

    return J;
}

/*** Operasi ***/
/*** Operator Relasional ***/
boolean JEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1=J2, false jika tidak */
{
    return (JAMToMenit(J1) == JAMToMenit(J2));
}

boolean JNEQ (JAM J1, JAM J2)
/* Mengirimkan true jika J1 tidak sama dengan J2 */
{
    return (JAMToMenit(J1) != JAMToMenit(J2));
}

boolean JLT (JAM J1, JAM J2)
/* Mengirimkan true jika J1<J2, false jika tidak */
{
    return (JAMToMenit(J1) < JAMToMenit(J2));
}

boolean JGT (JAM J1, JAM J2)
/* Mengirimkan true jika J1>J2, false jika tidak */
{
    return (JAMToMenit(J1) > JAMToMenit(J2));
}

/*** Operator Aritmatika ***/
JAM NextMenit (JAM J)
/* Mengirim 1 menit setelah J dalam bentuk JAM */
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time + 1);

    return res; 
}

JAM NextNMenit (JAM J, int N)
/* Mengirim N menit setelah J dalam bentuk JAM */
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time + N);

    return res;
}

JAM PrevMenit (JAM J)
/* Mengirim 1 menit sebelum J dalam bentuk JAM */
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time - 1 + 1440);

    return res;
}

JAM PrevNMenit (JAM J, int N)
/* Mengirim N menit sebelum J dalam bentuk JAM */
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time - N + 1440);

    return res;
}

long Durasi (JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw dlm menit, dengan kalkulasi */
/* Jika JAw > JAkh, maka JAkh adalah 1 hari setelah JAw */
{
    long dif = JAMToMenit(JAkh) - JAMToMenit(JAw);

    if (JAMToMenit(JAw) > JAMToMenit(JAkh)){
        dif += 1440;
    }

    return dif;
}

JAM DurasiJam(JAM JAw, JAM JAkh)
/* Mengirim JAkh-JAw tanpa memperhatikan komponen Hari */
{
    int HAw = Hour(JAw);
    long MAw = Minute(JAw) + 60*HAw;
    int HAkh = Hour(JAkh);
    long MAkh = Minute(JAkh) + 60*HAkh;

    if (MAw > MAkh)
    {
        return MenitToJAM(1440-MAw+MAkh);
    }
    else
    {
        return MenitToJAM(MAkh-MAw);
    }
}