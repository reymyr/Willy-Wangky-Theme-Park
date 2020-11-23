#include <stdio.h>
#include <stdlib.h>
#include "../boolean.h"
#include "wahana.h"
#include "../jam/jam.h"
#include "../string_production/mesinkata.h"

Wahana createWahana(int id, Kata nama, Kata tipe, int harga, Kata desc, int kapasitas, int durasi)
/* Fungsi untuk membuat Wahana baru */
{
    Wahana W;

    W_WahanaId(W) = id;
    W_Name(W) = nama;
    W_Type(W) = tipe;
    W_Price(W) = harga;
    W_Location(W) = MakePOINT(-1, -1);
    W_Desc(W) = desc;
    W_Capacity(W) = kapasitas;
    W_Duration(W) = durasi;
    W_UseCount(W) = 0;
    W_Penghasilan(W) = 0;
    W_TodayUseCount(W) = 0;
    W_TodayPenghasilan(W) = 0;
    W_IsBroken(W) = false;

    return W;
}

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void AW_MakeEmpty(ArrWahana *T)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    AW_NEff(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int AW_NbElmt(ArrWahana T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
    return AW_NEff(T);
}
/* *** Daya tampung container *** */
int AW_MaxElement(ArrWahana T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
    return IdxMax+1;
}
/* *** Selektor INDEKS *** */
IdxType AW_GetFirstIdx(ArrWahana T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
    return IdxMin;
}
IdxType AW_GetLastIdx(ArrWahana T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
    return AW_NEff(T) - 1;
}

/* ********** Test Indeks yang valid ********** */
boolean AW_IsIdxValid(ArrWahana T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
    return (IdxMin <= i && i <= AW_MaxElement(T)-1);
}
boolean AW_IsIdxEff(ArrWahana T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
    return (AW_GetFirstIdx(T) <= i && i <= AW_GetLastIdx(T));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean AW_IsEmpty(ArrWahana T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
    return (AW_NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean AW_IsFull(ArrWahana T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
    return (AW_NbElmt(T) == AW_MaxElement(T));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void AW_BacaFile(ArrWahana *T, char* filename)
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
{
    int id, harga, kapasitas, durasi;
    Kata nama, tipe, deskripsi;
    Wahana W;
    AW_MakeEmpty(T);
    MK_STARTKATA(filename);
    while (!MK_EndKata)
    {
        id = MK_KataToInt(MK_CKata);
        MK_ADVKATAINPUT();
        nama = MK_CKata;
        MK_ADVKATAINPUT();
        tipe = MK_CKata;
        MK_ADVKATAINPUT();
        harga = MK_KataToInt(MK_CKata);
        MK_ADVKATAINPUT();
        kapasitas = MK_KataToInt(MK_CKata);
        MK_ADVKATAINPUT();
        durasi = MK_KataToInt(MK_CKata);
        MK_ADVKATAINPUT();
        deskripsi = MK_CKata;
        W = createWahana(id, nama, tipe, harga, deskripsi, kapasitas, durasi);
        AW_AddAsLastEl(T, W);
        MK_ADV();
        MK_ADVKATA();
    }    
}
void AW_ListNamaWahana(ArrWahana T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
    IdxType i;
    for (i = AW_GetFirstIdx(T); i <= AW_GetLastIdx(T); i++)
    {
        printf(" - "); MK_printKata(W_Name(AW_Elmt(T,i))); printf("\n");
    }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType AW_SearchI(ArrWahana T, Kata K)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
{
    if (AW_IsEmpty(T))
    {
        return IdxUndef;
    }
    else
    {
        boolean found = false;
        IdxType i = AW_GetFirstIdx(T);
        while (!found && i <= AW_GetLastIdx(T))
        {
            if (MK_isKataSama(K, W_Name(AW_Elmt(T, i))))
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
boolean AW_SearchB(ArrWahana T, Kata K)
/* Search apakah ada elemen tabel T dengan nama K */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
{
    boolean found = false;
    IdxType i = AW_GetFirstIdx(T);
    while (!found && i <= AW_GetLastIdx(T))
    {
        if (MK_isKataSama(K, W_Name(AW_Elmt(T, i))))
        {
            found = true;
        }
        i++;
    }  
    return found;    
}

Wahana AW_GetWahana(ArrWahana T, Kata K)
/* Mengembalikan wahana yang bernama K dari TabWahana */
/* Prekondisi wahana dengan nama K ada di dalam Tabel */
{
    return AW_Elmt(T, AW_SearchI(T, K));
}

Wahana AW_GetWahanaId(ArrWahana T, int id)
/* Mengembalikan wahana dengan id tertentu */
/* Prekondisi wahana dengan id 'id' ada di dalam Tabel */
{
    boolean found = false;
    IdxType i = AW_GetFirstIdx(T);
    while (!found && i <= AW_GetLastIdx(T))
    {
        if (W_WahanaId(AW_Elmt(T, i)) == id)
        {
            found = true;
        }
        i++;
    }  
    return AW_Elmt(T, i-1);
}

int AW_GetPrice(ArrWahana T, Kata K)
/* Mengembalikan harga dari Wahana K */
/* Jika tidak ada mengembalikan -1 */
{
    int idx = AW_SearchI(T, K);
    if (idx == IdxUndef)
    {
        return -1;
    }
    else
    {
        return W_Price(AW_Elmt(T, idx));
    }
}

int AW_GetId(ArrWahana T, Kata K)
/* Mengembalikan id dari Wahana K */
/* Jika tidak ada mengembalikan -1 */
{
    int idx = AW_SearchI(T, K);
    if (idx == IdxUndef)
    {
        return -1;
    }
    else
    {
        return W_WahanaId(AW_Elmt(T, idx));
    }
}

/* ********** OPERASI LAIN ********** */
void AW_CopyTab(ArrWahana Tin, ArrWahana *Tout)
/* I.S. Tin terdefinisi tidak kosong, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (identik, AW_NEff dan MaxEl sama) */
/* Proses : Menyalin isi Tin ke Tout */
{
    IdxType i;
    AW_MakeEmpty(Tout);
    for (i = AW_GetFirstIdx(Tin); i <= AW_GetLastIdx(Tin); i++)
    {
        AW_Elmt(*Tout, i) = AW_Elmt(Tin, i);
    }
    AW_NEff(*Tout) = AW_NbElmt(Tin);
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AW_AddAsLastEl(ArrWahana *T, Wahana X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
    if (AW_IsEmpty(*T))
    {
        AW_Elmt(*T, IdxMin) = X;
        AW_NEff(*T) = 1;
    }
    else
    {
        AW_Elmt(*T, AW_GetLastIdx(*T)+1) = X;
        AW_NEff(*T)++;
    }    
}
/* ********** MENGHAPUS ELEMEN ********** */
void AW_DelLastEl(ArrWahana *T, Wahana *X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
    *X = AW_Elmt(*T, AW_GetLastIdx(*T));
    AW_NEff(*T)--;
}

void AW_detailWahana(Wahana W)
/* I.S. sembarang */
/* F.S. detail wahana tertulis di layar */
{
    printf("Details:\n");
    printf("Nama : "); MK_printKata(W_Name(W)); printf("\n");
    printf("Tipe : "); MK_printKata(W_Type(W)); printf("\n");
    printf("Harga : %d\n", W_Price(W));
    printf("Lokasi : "); TulisPOINT(W_Location(W)); printf("\n");
    printf("Deskripsi : "); MK_printKata(W_Desc(W)); printf("\n");
    printf("Kapasitas : %d\n", W_Capacity(W));
    printf("History : "); /*Print history*/ printf("\n");
    printf("Durasi : %d menit\n", W_Duration(W));
    printf("Status : "); (W_IsBroken(W) ? printf("Rusak") : printf("Berfungsi")); printf("\n");
}

void AW_reportWahana(Wahana W)
/* I.S. sembarang */
/* F.S. laporan wahana tertulis di layar */
{
    printf("Laporan wahana "); MK_printKata(W_Name(W)); printf("\n");
    printf("Total wahana dinaiki : %d kali\n", W_UseCount(W));
    printf("Total penghasilan : %d\n", W_Penghasilan(W));
    printf("Total wahana dinaiki hari ini : %d kali\n", W_TodayUseCount(W));
    printf("Penghasilan hari ini : %d\n", W_TodayPenghasilan(W));
}