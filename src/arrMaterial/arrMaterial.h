/* Daftar material dengan memodifikasi ADT list dengan implementasi array */
/* Array rapat kiri, banyak elemen didefinisikan dengan eksplisit dengan memori statik */

#ifndef ARRMATERIAL_H
#define ARRMATERIAL_H

#include "../boolean.h"
#include "../string_production/mesinkata.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;
typedef struct {
    Kata name;
    int count;
    int price;
} Material;

typedef struct {
    Material T[IdxMax+1];  // Memori tempat penyimpanan material
    int NEff;              // Banyak elemen efektif
} TabMaterial;

/* SELEKTOR */
#define M_Price(M) (M).price
#define M_Name(M) (M).name
#define M_Count(M) (M).count

#define AM_NEff(Arr) (Arr).NEff
#define AM_T(Arr) (Arr).T
#define AM_Elmt(Arr, i) (Arr).T[(i)]

Material createMaterial(Kata nama, int count, int price);
/* Fungsi untuk membuat Material baru */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AM_MakeEmpty(TabMaterial *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AM_NbElmt(TabMaterial T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int AM_MaxElement(TabMaterial T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType AM_GetFirstIdx(TabMaterial T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType AM_GetLastIdx(TabMaterial T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean AM_IsIdxValid(TabMaterial T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean AM_IsIdxEff(TabMaterial T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AM_IsEmpty(TabMaterial T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean AM_IsFull(TabMaterial T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void AM_BacaFile(TabMaterial *T, char* filename, boolean fileOpened);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= AM_MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= AM_MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void AM_TulisIsiTab(TabMaterial T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
void AM_TulisIsiTabCount(TabMaterial T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AM_SearchI(TabMaterial T, Kata K);
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan indeks i terkecil, dengan id = ID */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean AM_SearchB(TabMaterial T, Kata K);
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
int AM_GetPrice(TabMaterial T, Kata K);
/* Mengembalikan harga dari material K */
/* Jika tidak ada mengembalikan -1 */
int AM_GetCount(TabMaterial T, Kata K);
/* Mengembalikan jumlah material K pada T */

/* ********** OPERASI LAIN ********** */
void AM_CopyTab(TabMaterial Tin, TabMaterial *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AM_AddAsLastEl(TabMaterial *T, Material X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void AM_DelLastEl(TabMaterial *T, Material *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

void AM_AddCount(TabMaterial *T, Kata MatName, int count, int price);
/* Proses : Menambah material bernama MatName sebanyak count dari T */
/* I.S. Tabel terdefinisi dan boleh kosong, MatName merupakan material yang valid, count > 0 */
/* F.S. material bernama MatName bertambah sebanyak count dari T, jika sudah ada, count bertambah */
/*      Jika belum, terbentuk Material baru dalam tabel */

void AM_DelCount(TabMaterial *T, Kata MatName, int count);
/* Proses : Membuang material bernama MatName sebanyak count dari T */
/* I.S. Tabel tidak kosong, MatName terdapat dalam T, count tidak melebihi jumlah material dalam T */
/* F.S. material bernama MatName berkurang sebanyak count dari T, jika menjadi 0 dihilangkan */

boolean AM_MoreThan(TabMaterial T1, TabMaterial T2);
/* Mengembalikan apakah semua material pada T1 memiliki jumlah >= di T2 */

#endif