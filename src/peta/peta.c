#include "peta.h"
#include <stdio.h>

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk Peta *** */
void BacaPeta(Peta *P, char *filename)
/* Membaca File bernama 'filename' yang menyimpan Matriks-matriks yang menyusun area-area pada Peta */
/* I.S. Peta sembaarang */
/* F.S. Array Mem terisi dengan elemen elemen bertipe Area yang dibaca dari File */
{
    STARTMATRIKS("map.txt");
    int i = 0;
    while (!ENDMATRIKS)
    {
        Area(*P,i) = CMatriks;
        i++;
        ADVMATRIKS();
    }
}

void TulisPeta(Peta P, char *filename)
/* Menuliskan dan menyimpan isi Peta P ke dalam file 'filename'*/
/* I.S. Area-area yang disimpan pada array Mem di Peta P sudah terdefinisi */
/* F.S. File <filename> sudah diisi dengan area-area pada Peta P.*/
{
    FILE * f = fopen(filename,"w");
    if (f == NULL)
    {
        printf("Fail\n");
    } else
    {
        for (int k=0;k<4;k++){
            TulisMATRIKS(Area(P,k),f);
            if (k<3)
            {
                fprintf(f,"%c\n",SEPARATOR);
            } else
            {
                fprintf(f,"%c",MK_MARK);
            }
        }
        fclose(f);
    }
}

void PrintAreai(Peta P, indeks i){
    PrintMATRIKS(Area(P,i));
}