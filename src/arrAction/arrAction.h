/* Daftar action dengan memodifikasi ADT list dengan implementasi array */
/* Array rapat kiri, banyak elemen didefinisikan dengan eksplisit dengan memori statik */

#ifndef ARRACTION_H
#define ARRACTION_H

#include "../boolean.h"
#include "../jam/jam.h"
#include "../string_production/mesinkata.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;
typedef struct {
    int actionId;
    Kata name;
    JAM duration;
} Action;

typedef struct {
    Action T[IdxMax+1]; // Memori tempat penyimpanan aksi
    int NEff;           // Banyak elemen efektif
} ArrAction;

/* SELEKTOR */
/* Misal A adalah variabel bertipe Action */
#define A_ActionID(A) (A).actionId
#define A_Name(A) (A).name
#define A_Duration(A) (A).duration

/* Misal Arr adalah variabel bertipe ArrAction */
#define AA_NEff(Arr) (Arr).NEff
#define AA_T(Arr) (Arr).T
#define AA_Elmt(Arr, i) (Arr).T[(i)]

Action createAction(int id, Kata nama, JAM durasi);
/* Fungsi untuk membuat Action baru */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AA_MakeEmpty(ArrAction *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AA_NbElmt(ArrAction T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int AA_MaxElement(ArrAction T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType AA_GetFirstIdx(ArrAction T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType AA_GetLastIdx(ArrAction T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean AA_IsIdxValid(ArrAction T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean AA_IsIdxEff(ArrAction T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AA_IsEmpty(ArrAction T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean AA_IsFull(ArrAction T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
void AA_TulisIsiTab(ArrAction T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AA_SearchI(ArrAction T, Kata K);
/* Search apakah ada elemen tabel T yang dengan id ID */
/* Jika ada, menghasilkan indeks i terkecil, dengan id = ID */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean AA_SearchB(ArrAction T, Kata K);
/* Search apakah ada elemen tabel T dengan id ID */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
int AA_SearchID(ArrAction T, Kata K);
/* Search apakah ada elemen tabel T yang dengan nama K*/
/* Jika ada, menghasilkan id action, dengan nama K */
/* Jika tidak ada, mengirimkan -1 */


/* ********** OPERASI LAIN ********** */
void AA_CopyTab(ArrAction Tin, ArrAction *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AA_AddAsLastEl(ArrAction *T, Action X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void AA_DelLastEl(ArrAction *T, Action *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

#endif