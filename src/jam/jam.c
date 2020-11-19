/* Realisasi ADT Jam */

#include <stdio.h>
#include "jam.h"
#include "../boolean.h"

/*** Validasi ***/
boolean IsJAMValid (int D, int H, int M)
{
   return ((D >= 0) && (H >= 0 && H <= 23) && (M >= 0 && M <= 59));
}

/*** Konstruktor ***/
JAM MakeJAM (int DD, int HH, int MM)
{
   JAM J;

   Day(J) = DD;
   Hour(J) = HH;
   Minute(J) = MM;

   return J;
}

void BacaJAM (JAM * J)
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
{
    printf("Day %d - %d.%d", Day(J), Hour(J), Minute(J));
}

/*** Konversi ***/
long JAMToMenit (JAM J)
{
    return(1440 * Day(J) + 60 * Hour(J) + Minute(J));  
}

JAM MenitToJAM (long N)
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
{
    return (JAMToMenit(J1) == JAMToMenit(J2));
}

boolean JNEQ (JAM J1, JAM J2)
{
    return (JAMToMenit(J1) != JAMToMenit(J2));
}

boolean JLT (JAM J1, JAM J2)
{
    return (JAMToMenit(J1) < JAMToMenit(J2));
}

boolean JGT (JAM J1, JAM J2)
{
    return (JAMToMenit(J1) > JAMToMenit(J2));
}

/*** Operator Aritmatika ***/
JAM NextMenit (JAM J)
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time + 1);

    return res; 
}

JAM NextNMenit (JAM J, int N)
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time + N);

    return res;
}

JAM PrevMenit (JAM J)
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time - 1 + 1440);

    return res;
}

JAM PrevNMenit (JAM J, int N)
{
    long time = JAMToMenit(J);

    JAM res = MenitToJAM(time - N + 1440);

    return res;
}

long Durasi (JAM JAw, JAM JAkh)
{
    long dif = JAMToMenit(JAkh) - JAMToMenit(JAw);

    if (JAMToMenit(JAw) > JAMToMenit(JAkh)){
        dif += 1440;
    }

    return dif;
}