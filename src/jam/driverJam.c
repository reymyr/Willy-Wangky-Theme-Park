/* Driver Jam */

#include <stdio.h>
#include "jam.h"

int main() {
    JAM J1, J2;

    BacaJAM(&J1);
    J2 = MakeJAM(1,13,35);
    printf("J1: "); TulisJamMenit(J1); printf("\n");
    printf("J2: "); TulisJamMenit(J2); printf("\n");

    long menit1 = JAMToMenit(J1);
    long menit2 = JAMToMenit(J2);
    printf("Menit J1: %d", menit1); printf("\n");
    printf("Menit J2: %d", menit2); printf("\n");

    JAM jam1 = MenitToJAM(menit1);
    JAM jam2 = MenitToJAM(menit2);
    printf("Jam J1: "); TulisJAM(jam1); printf("\n");
    printf("Jam J2: "); TulisJAM(jam2); printf("\n");

    if (JEQ(J1,J2)){
        printf("J1 = J2\n");
    }
    else if (JLT(J1,J2)){
        printf("J1 < J2\n");
    }
    else{
        printf("J1 > J2\n");
    }

    printf("1 menit setelah J1: "); TulisJAM(NextMenit(J1)); printf("\n");
    printf("1 menit setelah J2: "); TulisJAM(NextMenit(J2)); printf("\n");
    printf("20 menit setelah J1: "); TulisJAM(NextNMenit(J1,20)); printf("\n");
    printf("20 menit setelah J2: "); TulisJAM(NextNMenit(J2,20)); printf("\n");

    printf("1 menit sebelum J1: "); TulisJAM(PrevMenit(J1)); printf("\n");
    printf("1 menit sebelum J2: "); TulisJAM(PrevMenit(J2)); printf("\n");
    printf("20 menit sebelum J1: "); TulisJAM(PrevNMenit(J1,20)); printf("\n");
    printf("20 menit sebelum J2: "); TulisJAM(PrevNMenit(J2,20)); printf("\n");

    long dur1 = Durasi(J1,J2);
    printf("Durasi J1-J2: %d\n",dur1);
    JAM dur2 = DurasiJam(J1,J2);
    printf("Durasi J1-J2 dalam jam: "); TulisJAM(dur2); printf("\n");

    return 0;
}