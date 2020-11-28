/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "../boolean.h"
#include "../jam/jam.h"
#include "../point/point.h"
#include "../string_production/mesinkata.h"

#define Nil -1
#define S_MaxEl 50
/* Nil adalah stack dengan elemen kosong . */

typedef struct {
    Kata name;        /* Nama aksi */
    Kata matName;     /* Nama material jika name=buy */
    int matCount;     /* Jumlah material juka name=buy */
    JAM timeNeeded;   /* Waktu yang dibutuhkan aksi */
    int moneyNeeded;  /* Uang yang dibutuhkan aksi */
    POINT posWahana;  /* Posisi wahana jika name=build atau name=upgrade */
    int idWahanaFrom; /* Id wahana lama jika name=build atau name=upgrade */
    int idWahanaTo;   /* Id wahana baru jika name=build atau name=upgrade */
} S_infotype;
typedef int S_address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  S_infotype T[S_MaxEl]; /* tabel penyimpan elemen */
  S_address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[S_MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define S_Name(SI) (SI).name
#define S_TimeNeeded(SI) (SI).timeNeeded
#define S_MoneyNeeded(SI) (SI).moneyNeeded
#define S_PosWahana(SI) (SI).posWahana
#define S_IdWahanaFrom(SI) (SI).idWahanaFrom
#define S_IdWahanaTo(SI) (SI).idWahanaTo
#define S_MatName(SI) (SI).matName
#define S_MatCount(SI) (SI).matCount

#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

S_infotype CreateStackInfo(Kata name, JAM time, int money, POINT pos);
/* Membentuk elemen Stack dari data inputan */

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas S_MaxEl */
/* jadi indeksnya antara 0.. S_MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFull (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
int NbElmtStack (Stack S);
/* Mengirim banyak elemen Stack */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, S_infotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, S_infotype* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

void InverseStack(Stack *Sin, Stack *Sout);
/* I.S. Sin terdefinisi */
/* F.S. Sout berisi Sin yang sudah dibaluk */

void CopyStack(Stack *Sin, Stack *Sout);
/* I.S. Sin terdefinisi */
/* F.S. Sout terisi Sin */

int TotalMoney(Stack S);
/* Mengembalikan total uang yang dibutuhkan dari semua elemen Stack */

JAM TotalTime(Stack S);
/* Mengembalikan total waktu yang dibutuhkan dari semua elemen Stack */

#endif
