/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#ifndef PETA_H
#define PETA_H
#include "stdio.h"
#include "../matriks/matriks.h"
#include "../boolean.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define NArea 4

typedef int indeks;
typedef MATRIKS area;
typedef char ElType; 
typedef struct { 
    area Mem[NArea];
} Peta;

/* *** Selektor *** */
#define Area(Peta,i) (Peta).Mem[(i)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk Peta *** */
void BacaPeta(Peta *M,char *filename);
/* Membaca File bernama 'filename' yang menyimpan Matriks-matriks yang menyusun area-area pada Peta */
/* I.S. Peta sembaarang */
/* F.S. Array Mem terisi dengan elemen elemen bertipe Area yang dibaca dari File */

void TulisPeta(Peta P, char *filename);
/* Menuliskan dan menyimpan isi Peta P ke dalam file 'filename'*/
/* I.S. Area-area yang disimpan pada array Mem di Peta P sudah terdefinisi */
/* F.S. File <filename> sudah diisi dengan area-area pada Peta P.*/

void PrintAreai(Peta P, indeks i);
/* Proses : Menampilkan Area(P,i) ke layar dengan meggunakan primitif PrintMATRIKS*/
/*I.S. Area(P,i) sudah terdefinisi*/
/*F.S. Output berupa tampilan matriks Area(P,i) */

#endif