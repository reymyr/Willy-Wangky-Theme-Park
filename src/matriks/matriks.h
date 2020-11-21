/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#ifndef MATRIKS_H
#define MATRIKS_H
#include "../string_production/mesinkar.h"
#include "stdio.h"

#include "../boolean.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 0
#define BrsMax 19
#define KolMin 0
#define KolMax 19
#define SEPARATOR '-'

typedef int indeks; /* indeks baris, kolom */

typedef struct { 
	char type;
   int id; /* berisi id wahana jika type='W', -1 jiak bukan */
} Tile;

typedef Tile ElType; 
typedef struct { 
	ElType Mem[BrsMax+1][KolMax+1];
   int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;
/* NBrsEff >= 1 dan NKolEff >= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

extern boolean ENDMATRIKS;
extern MATRIKS CMatriks;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M); 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define T_Type(T) (T).type
#define T_ID(T) (T).id

#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxMatriksValid (int i, int j);
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxMatriksEff (MATRIKS M, indeks i, indeks j);
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */


/* ********** KELOMPOK BACA/TULIS ********** */ 

void TulisMATRIKS(MATRIKS M, FILE *f);
/* Menuliskan matriks M ke dalam sebuah file bernama <filename>*/

void PrintMATRIKS (MATRIKS M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ******** KELOMPOK PEMROSESAN BEBERAPA MATRIKS YANG DIBACA DARI SEBUAH FILE ********* */
void STARTMATRIKS(char *filename);

void ADVMATRIKS();
/* I.S. : CC dapat berupa MARK atau SEPARATOR 
   F.S. : CMatriks adalah matriks terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, ENDMATRIKS = true.     
   Proses : Akuisisi matriks menggunakan procedure SalinMatriks */

void SalinMatriks();
/* Mengakuisisi matriks, menyimpan dalam CMatriks
   I.S. : CC adalah karakter pertama dari matriks
   F.S. : CMatriks berisi matriks yang sudah diakuisisi{} 
          CC = SEPARATOR atau CC = MARK
          CC adalah karakter sesudah karakter terakhir yang diakuisisi. */

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M);
/* Mengirimkan banyaknya elemen M */
#endif