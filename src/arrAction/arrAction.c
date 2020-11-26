#include <stdio.h>
#include <stdlib.h>
#include "../boolean.h"
#include "arrAction.h"
#include "../jam/jam.h"
#include "../string_production/mesinkata.h"

Action createAction(int id, Kata nama, JAM durasi)
/* Fungsi untuk membuat Action baru */
{
    Action A;

    A_ActionID(A) = id;
    A_Name(A) = nama;
    A_Duration(A) = durasi;

    return A;
}

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AA_MakeEmpty(ArrAction *T)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    AA_NEff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AA_NbElmt(ArrAction T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
    return AA_NEff(T);
}
/* *** Daya tampung container *** */
int AA_MaxElement(ArrAction T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return IdxMax+1;
}
/* *** Selektor INDEKS *** */
IdxType AA_GetFirstIdx(ArrAction T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}
IdxType AA_GetLastIdx(ArrAction T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return AA_NEff(T) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean AA_IsIdxValid(ArrAction T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IdxMin <= i && i <= AA_MaxElement(T)-1);
}
boolean AA_IsIdxEff(ArrAction T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return (AA_GetFirstIdx(T) <= i && i <= AA_GetLastIdx(T));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AA_IsEmpty(ArrAction T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return (AA_NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean AA_IsFull(ArrAction T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return (AA_NbElmt(T) == AA_MaxElement(T));
}

void AA_TulisIsiTab(ArrAction T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    IdxType i;
    for (i = AA_GetFirstIdx(T); i <= AA_GetLastIdx(T); i++)
    {
        MK_printKata(A_Name(AA_T(T)[i]));
        printf(", Duration: ");
        TulisJAM(A_Duration(AA_T(T)[i]));
        printf("\n");
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AA_SearchI(ArrAction T, Kata K)
/* Search apakah ada elemen tabel T yang dengan nama K*/
/* Jika ada, menghasilkan indeks i terkecil, dengan nama K */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
    if (AA_IsEmpty(T))
    {
        return IdxUndef;
    }
    else
    {
        boolean found = false;
        IdxType i = AA_GetFirstIdx(T);
        while (!found && i <= AA_GetLastIdx(T))
        {
            if (MK_isKataSama(K, A_Name(AA_Elmt(T, i))))
            {
                found = true;
            }
            i++;
        }  

        if (found)
        {
            return i-1;
        }
        else
        {
            return IdxUndef;
        }   
    }
}
boolean AA_SearchB(ArrAction T, Kata K)
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
    boolean found = false;
    IdxType i = AA_GetFirstIdx(T);
    while (!found && i <= AA_GetLastIdx(T))
    {
        if (MK_isKataSama(K, A_Name(AA_Elmt(T, i))))
        {
            found = true;
        }
        i++;
    }  
    return found;    
}
int AA_SearchID(ArrAction T, Kata K)
/* Search apakah ada elemen tabel T yang dengan nama K*/
/* Jika ada, menghasilkan id action, dengan nama K */
/* Jika tidak ada, mengirimkan -1 */
{
    IdxType i = AA_SearchI(T, K);
    if (i == IdxUndef)
    {
        return -1;
    }
    else
    {
        return A_ActionID(AA_Elmt(T, i));
    }   
}

/* ********** OPERASI LAIN ********** */
void AA_CopyTab(ArrAction Tin, ArrAction *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, NEff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    IdxType i;
    AA_MakeEmpty(Tout);
    for (i = AA_GetFirstIdx(Tin); i <= AA_GetLastIdx(Tin); i++)
    {
        AA_Elmt(*Tout, i) = AA_Elmt(Tin, i);
    }
    AA_NEff(*Tout) = AA_NbElmt(Tin);
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AA_AddAsLastEl(ArrAction *T, Action X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    if (AA_IsEmpty(*T))
    {
        AA_Elmt(*T, IdxMin) = X;
        AA_NEff(*T) = 1;
    }
    else
    {
        AA_Elmt(*T, AA_GetLastIdx(*T)+1) = X;
        AA_NEff(*T)++;
    }    
}
/* ********** MENGHAPUS ELEMEN ********** */
void AA_DelLastEl(ArrAction *T, Action *X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    *X = AA_Elmt(*T, AA_GetLastIdx(*T));
    AA_NEff(*T)--;
}