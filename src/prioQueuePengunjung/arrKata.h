#ifndef ARRKATA_H
#define ARRKATA_H

#include "../boolean.h"
#include "../string_production/mesinkata.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;

typedef struct {
    Kata T[IdxMax+1]; // Memori tempat penyimpanan kata
    int NEff;           // Banyak elemen efektif
} ArrKata;

/* SELEKTOR */
/* Misal Arr adalah variabel bertipe ArrKata */
#define AK_NEff(Arr) (Arr).NEff
#define AK_T(Arr) (Arr).T
#define AK_Elmt(Arr, i) (Arr).T[(i)]

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AK_MakeEmpty(ArrKata *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AK_NbElmt(ArrKata T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int AK_MaxElement(ArrKata T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType AK_GetFirstIdx(ArrKata T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType AK_GetLastIdx(ArrKata T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean AK_IsIdxValid(ArrKata T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean AK_IsIdxEff(ArrKata T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AK_IsEmpty(ArrKata T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean AK_IsFull(ArrKata T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** TULIS dengan INPUT/OUTPUT device ********** */
void AK_TulisIsiTab(ArrKata T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AK_SearchI(ArrKata T, Kata K);
/* Search apakah ada elemen tabel T yang dengan id ID */
/* Jika ada, menghasilkan indeks i terkecil, dengan id = ID */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean AK_SearchB(ArrKata T, Kata K);
/* Search apakah ada elemen tabel T dengan id ID */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */


/* ********** OPERASI LAIN ********** */
void AK_CopyTab(ArrKata Tin, ArrKata *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AK_AddAsLastEl(ArrKata *T, Kata X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void AK_DelLastEl(ArrKata *T, Kata *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
void AK_DelKata(ArrKata *T, Kata K);
/* I.S. Tabel tiadk kosong, K terdapat dalam tabel */
/* F.S. Kata K dihapus dari Tabel, Neff berkurang 1 */

#endif