#include <stdio.h>
#include <stdlib.h>
#include "../boolean.h"
#include "arrMaterial.h"

Material createMaterial(int id,/*KATA nama,*/ int price)
/* Fungsi untuk membuat Material baru */
{
    Material M;

    M_MaterialID(M) = id;
    // M_Name(M) = nama;
    M_Price(M) = price;

    return M;
}

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AM_MakeEmpty(TabMaterial *T)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    AM_NEff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AM_NbElmt(TabMaterial T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
    return AM_NEff(T);
}
/* *** Daya tampung container *** */
int AM_MaxElement(TabMaterial T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return IdxMax+1;
}
/* *** Selektor INDEKS *** */
IdxType AM_GetFirstIdx(TabMaterial T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}
IdxType AM_GetLastIdx(TabMaterial T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return AM_NEff(T) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean AM_IsIdxValid(TabMaterial T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IdxMin <= i && i <= AM_MaxElement(T)-1);
}
boolean AM_IsIdxEff(TabMaterial T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return (AM_GetFirstIdx(T) <= i && i <= AM_GetLastIdx(T));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AM_IsEmpty(TabMaterial T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return (AM_NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean AM_IsFull(TabMaterial T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return (AM_NbElmt(T) == AM_MaxElement(T));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void AM_BacaIsi(TabMaterial *T)
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= AM_MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= AM_MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
    int i, N;
    
    do
    {
        scanf("%d", &N);
    } while (N < 0 || N > AM_MaxElement(*T));
    
    if (N == 0)
    {
        AM_NEff(*T) = 0;
    }
    else
    {
        for (i = IdxMin; i < N; i++)
        {
            Material x;
            scanf("%d", &x);
            AM_Elmt(*T, i) = x;
            AM_NEff(*T)++;
        }
    }
}
void AM_TulisIsiTab(TabMaterial T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    IdxType i;
    printf("[");
    for (i = AM_GetFirstIdx(T); i <= AM_GetLastIdx(T); i++)
    {
        printf("%d", AM_Elmt(T, i));
        if (i != AM_GetLastIdx(T))
        {
            printf(",");
        }
    }
    printf("]");
}


/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean AM_IsEQ(TabMaterial T1, TabMaterial T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika AM_NEff T1 = T2 dan semua elemennya sama */
{
    if (AM_NbElmt(T1) != AM_NbElmt(T2))
    {
        return false;
    }
    else
    {
        boolean equal = true;
        IdxType i = AM_GetFirstIdx(T1);
        while (equal && i <= AM_GetLastIdx(T1))
        {
            if (Elmt(T1, i) != Elmt(T2, i))
            {
                equal = false;
            }
            i++;
        }  
        return equal;
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AM_Search1(TabMaterial T, int ID)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
    if (AM_IsEmpty(T))
    {
        return IdxUndef;
    }
    else
    {
        boolean found = false;
        IdxType i = AM_GetFirstIdx(T);
        while (!found && i <= AM_GetLastIdx(T))
        {
            if (M_MaterialID(AM_Elmt(T, i)) == ID)
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
boolean AM_SearchIdB(TabMaterial T, int ID)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
    boolean found = false;
    IdxType i = AM_GetFirstIdx(T);
    while (!found && i <= AM_GetLastIdx(T))
    {
        if (M_MaterialID(AM_Elmt(T, i)) == ID)
        {
            found = true;
        }
        i++;
    }  
    return found;    
}


/* ********** OPERASI LAIN ********** */
void AM_CopyTab(TabMaterial Tin, TabMaterial *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, AM_NEff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    IdxType i;
    AM_MakeEmpty(Tout);
    for (i = AM_GetFirstIdx(Tin); i <= AM_GetLastIdx(Tin); i++)
    {
        AM_Elmt(*Tout, i) = AM_Elmt(Tin, i);
    }
    AM_NEff(*Tout) = AM_NbElmt(Tin);
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AM_AddAsLastEl(TabMaterial *T, Material X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    if (AM_IsEmpty(*T))
    {
        AM_Elmt(*T, IdxMin) = X;
        AM_NEff(*T) = 1;
    }
    else
    {
        AM_Elmt(*T, AM_GetLastIdx(*T)+1) = X;
        AM_NEff(*T)++;
    }    
}
/* ********** MENGHAPUS ELEMEN ********** */
void AM_DelLastEl(TabMaterial *T, Material *X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    *X = AM_Elmt(*T, AM_GetLastIdx(*T));
    AM_NEff(*T)--;
}