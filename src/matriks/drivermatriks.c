#include "matriks.h"
#include <stdio.h>

int main(){
    MATRIKS Area[4];

    Player P;
    Nama(P) = MK_MakeKata("Akifa",5);
    Money(P) = 1000;
    Pos(P) = MakePOINT(3,3);

    /* Baca Matriks dari File dan disimpan ke array of Matriks */
    STARTMATRIKS("testmap.txt");
    int i = 0;

    while (!ENDMATRIKS){
        Area[i] = CMatriks;
        i++;
        ADVMATRIKS();
    }

    /* Menampilkan tiap matriks pada array tersebut. */
    for (i = 0; i < 4; i++){
        PrintMATRIKS(Area[i],P);
    }

    
    /* Menyimpan matriks pada file eksternal */
    FILE * f = fopen("testmap.txt","w");

    for (int k=0;k<4;k++){
        TulisMATRIKS(Area[k],f);
        if (k<3){
            fprintf(f,"%c\n",SEPARATOR);
        } else{
            fprintf(f,"%c",MK_MARK);
        }
    }


    fclose(f);
    
    return 0;
}

// gcc -o matriks matriks.c drivermatriks.c ../string_production/mesinkar.c ../string_production/mesinkata.c ../point/point.c