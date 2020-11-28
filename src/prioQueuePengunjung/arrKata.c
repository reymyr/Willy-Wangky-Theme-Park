#include <stdio.h>
#include <stdlib.h>
#include "../boolean.h"
#include "arrKata.h"
#include "../string_production/mesinkata.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AK_MakeEmpty(ArrKata *T)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    AK_NEff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AK_NbElmt(ArrKata T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
    return AK_NEff(T);
}
/* *** Daya tampung container *** */
int AK_MaxElement(ArrKata T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return IdxMax+1;
}
/* *** Selektor INDEKS *** */
IdxType AK_GetFirstIdx(ArrKata T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}
IdxType AK_GetLastIdx(ArrKata T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return AK_NEff(T) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean AK_IsIdxValid(ArrKata T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IdxMin <= i && i <= AK_MaxElement(T)-1);
}
boolean AK_IsIdxEff(ArrKata T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return (AK_GetFirstIdx(T) <= i && i <= AK_GetLastIdx(T));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AK_IsEmpty(ArrKata T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return (AK_NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean AK_IsFull(ArrKata T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return (AK_NbElmt(T) == AK_MaxElement(T));
}

void AK_TulisIsiTab(ArrKata T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    IdxType i;
    printf("(");
    for (i = AK_GetFirstIdx(T); i <= AK_GetLastIdx(T); i++)
    {
        MK_printKata(AK_Elmt(T, i));
        if (i < AK_GetLastIdx(T))
        {
            printf(", ");
        }
    }
    printf(")");
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AK_SearchI(ArrKata T, Kata K)
/* Search apakah ada elemen tabel T yang dengan nama K*/
/* Jika ada, menghasilkan indeks i terkecil, dengan nama K */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
    if (AK_IsEmpty(T))
    {
        return IdxUndef;
    }
    else
    {
        boolean found = false;
        IdxType i = AK_GetFirstIdx(T);
        while (!found && i <= AK_GetLastIdx(T))
        {
            if (MK_isKataSama(K, AK_Elmt(T, i)))
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
boolean AK_SearchB(ArrKata T, Kata K)
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
    boolean found = false;
    IdxType i = AK_GetFirstIdx(T);
    while (!found && i <= AK_GetLastIdx(T))
    {
        if (MK_isKataSama(K, AK_Elmt(T, i)))
        {
            found = true;
        }
        i++;
    }  
    return found;    
}

/* ********** OPERASI LAIN ********** */
void AK_CopyTab(ArrKata Tin, ArrKata *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, NEff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    IdxType i;
    AK_MakeEmpty(Tout);
    for (i = AK_GetFirstIdx(Tin); i <= AK_GetLastIdx(Tin); i++)
    {
        AK_Elmt(*Tout, i) = AK_Elmt(Tin, i);
    }
    AK_NEff(*Tout) = AK_NbElmt(Tin);
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AK_AddAsLastEl(ArrKata *T, Kata X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    if (AK_IsEmpty(*T))
    {
        AK_Elmt(*T, IdxMin) = X;
        AK_NEff(*T) = 1;
    }
    else
    {
        AK_Elmt(*T, AK_GetLastIdx(*T)+1) = X;
        AK_NEff(*T)++;
    }    
}
/* ********** MENGHAPUS ELEMEN ********** */
void AK_DelLastEl(ArrKata *T, Kata *X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    *X = AK_Elmt(*T, AK_GetLastIdx(*T));
    AK_NEff(*T)--;
}

void AK_DelKata(ArrKata *T, Kata K)
/* I.S. Tabel tiadk kosong, K terdapat dalam tabel */
/* F.S. Kata K dihapus dari Tabel, Neff berkurang 1 */
{
    int idx = AK_SearchI(*T, K);
    for (size_t i = idx+1; i <= AK_GetLastIdx(*T); i++)
    {
        AK_Elmt(*T, idx) = AK_Elmt(*T, i);
        idx++;
    }
    AK_NEff(*T)--;
}