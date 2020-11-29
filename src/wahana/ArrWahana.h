#ifndef ARRWAHANA_H
#define ARRWAHANA_H

#include "wahana.h"
#include "../string_production/mesinkata.h"
#include "../jam/jam.h"
#include "../point/point.h"
#include "LLWahana.h"
#include "../tree/arrTree.h"
#include "../tree/bintree.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;

typedef struct {
    Wahana T[IdxMax+1]; // Memori tempat penyimpanan aksi
    int NEff;           // Banyak elemen efektif
} ArrWahana;

/* SELEKTOR */
/* Misal Arr adalah variabel bertipe ArrWahana */
#define AW_NEff(Arr) (Arr).NEff
#define AW_T(Arr) (Arr).T
#define AW_Elmt(Arr, i) (Arr).T[(i)]

Wahana createWahana(int base, int id, Kata nama, Kata tipe, int harga, Kata desc, int kapasitas, int durasi, int moneyCost, TabMaterial matCost);
/* Fungsi untuk membuat Wahana baru */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AW_MakeEmpty(ArrWahana *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */


/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AW_NbElmt(ArrWahana T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int AW_MaxElement(ArrWahana T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType AW_GetFirstIdx(ArrWahana T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType AW_GetLastIdx(ArrWahana T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** Test Indeks yang valid ********** */
boolean AW_IsIdxValid(ArrWahana T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
boolean AW_IsIdxEff(ArrWahana T, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AW_IsEmpty(ArrWahana T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean AW_IsFull(ArrWahana T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void AW_BacaFile(ArrWahana *T, char* filename);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= AW_MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= AW_MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void AW_ListNamaWahana(ArrWahana T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
void AW_printWahanaCost(Wahana W);
/* I.S. W terdefinisi */
/* F.S. Jumlah material dan uang yang dibutuhkan untuk membangun W tertulis di layar */

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AW_SearchI(ArrWahana T, Kata K);
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan indeks i terkecil, dengan id = ID */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
boolean AW_SearchB(ArrWahana T, Kata K);
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
Wahana AW_GetWahana(ArrWahana T, Kata K);
/* Mengembalikan wahana yang bernama K dari TabWahana */
/* Prekondisi wahana dengan nama K ada di dalam Tabel */
Wahana AW_GetWahanaId(ArrWahana T, int id);
/* Mengembalikan wahana dengan id tertentu */
/* Prekondisi wahana dengan id 'id' ada di dalam Tabel */
int AW_GetPrice(ArrWahana T, Kata K);
/* Mengembalikan harga dari Wahana K */
/* Jika tidak ada mengembalikan -1 */
int AW_GetCost(ArrWahana T, Kata K);
/* Mengembalikan harga bangun dari Wahana K */
/* Jika tidak ada mengembalikan -1 */
int AW_GetId(ArrWahana T, Kata K);
/* Mengembalikan id dari Wahana K */
/* Jika tidak ada mengembalikan -1 */

/* ********** OPERASI LAIN ********** */
void AW_CopyTab(ArrWahana Tin, ArrWahana *Tout);
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, Neff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */


/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AW_AddAsLastEl(ArrWahana *T, Wahana X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
/* ********** MENGHAPUS ELEMEN ********** */
void AW_DelLastEl(ArrWahana *T, Wahana *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

void AW_detailWahana(Wahana W, ArrListWahanaUpg A);
/* I.S. sembarang */
/* F.S. detail wahana tertulis di layar */

void AW_reportWahana(Wahana W);
/* I.S. sembarang */
/* F.S. laporan wahana tertulis di layar */

void AW_printBroken(ArrWahana AW);
/* I.S. AW terdefinisi */
/* F.S. Nama wahana yang rusak tertulis di layar */

void AW_setRusak(ArrWahana * AW, Kata K);
/* I.S. AW terdefinisi */
/* F.S. Wahana W pada AW menjadi rusak */

void AW_pengungjungNaik(ArrWahana * AW, Kata K);
/* I.S. AW terdefinisi */
/* F.S. penghasilan dan useCount Wahana dengan nama K bertambah */

void AW_RepairWahanaRusak(ArrWahana * AW, Kata K);
/* I.S : W_IsBroken(W) = true, F.S. : W_IsBroken(W) = false*/

void AW_readWahanaDanTree(ArrTree * BT, ArrWahana * AW, char* filename);
/* I.S. Sembarang */
/* F.S. Membaca file tree dan wahana, BT terisi array upgrade tree, AW terisi array wahana */

void AW_delElmt(ArrWahana * AW, Kata K);
/* Menghapus wahana dengan nama K pada AW */

void AW_newDay(ArrWahana * AW);
/* I.S. AW terdefinisi */
/* F.S todayPenghasilan dan todayUseCount diset menjadi 0 untuk setiap wahana */

void UpgradeWahana(ArrWahana * AW, Wahana W0, Wahana W1, ArrListWahanaUpg A);
/* Meng-upgrade Wahana W0 menjadi Wahana W1 */
/* I.S : Asumsi W1 sudah valid merupakan upgrade dari wahana W0*/

#endif