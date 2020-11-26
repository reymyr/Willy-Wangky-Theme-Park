#include "../boolean.h"
#include "listlinier.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean LL_IsEmpty (List L)
/* Mengirim true jika list kosong */
{
    return First(L) == LL_Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void LL_CreateEmpty (List *L)
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
{
    First(*L) = LL_Nil;
}

/****************** Manajemen Memori ******************/
address LL_Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=LL_Nil */
/* Jika alokasi gagal, mengirimkan LL_Nil */
{
    ElmtList *P = (ElmtList *)malloc(sizeof(ElmtList));

    if (P==LL_Nil)
    {
        return LL_Nil;
    } else
    {
        Info(P) = X;
        Next(P) = LL_Nil;
        return P;
    }
}
void LL_Dealokasi (address *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address LL_Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan LL_Nil */
{
    address P = First(L);
    boolean found = false;

    if (!LL_IsEmpty(L))
    {
        while (!found && P!=LL_Nil)
        {
            if (W_WahanaId(X)==W_WahanaId(Info(P))){
                found = true;
            } else
            {
                P = Next(P);
            }
        }
    }
    return P;
}
boolean LL_FSearch (List L, address P)
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
{
    boolean found = false;
    address X = First(L);

    while (!found && X!=LL_Nil)
    {
        if (X==P)
        {
            found=true;
        } else
        {
            X = Next(X);
        }
    }
    return found;
}
address LL_SearchPrec (List L, infotype X)
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan LL_Nil */
/* Jika P adalah elemen pertama, maka Prec=LL_Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
{
    address Prec = LL_Nil;
    address P = First(L);
    boolean found = false;
    
    while (!found && P!=LL_Nil)
    {
        if (W_WahanaId(X)==W_WahanaId(Info(P))){
            found = true;
        } else
        {
            Prec = P;
            P = Next(P);
        }
    }
    return Prec;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void LL_InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
    address P = LL_Alokasi(X);
    if (P!=LL_Nil)
    {
        LL_InsertFirst(L,P);
    }
    
}
void LL_InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
    address P  = LL_Alokasi(X);
    if (P != LL_Nil){
        LL_InsertLast(L,P);
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void LL_DelVFirst (List *L, infotype *X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
    address P;
    LL_DelFirst(L,&P);
    *X = Info(P);
    LL_Dealokasi(&P);
}

void LL_DelVLast (List *L, infotype *X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
    address P;
    LL_DelLast(L,&P);
    *X = Info(P);
    LL_Dealokasi(&P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void LL_InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    Next(P) = First(*L);
    First(*L) = P;
}

void LL_InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
    Next(P) = Next(Prec);
    Next(Prec) = P;
}

void LL_InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (!LL_IsEmpty(*L)){
        // Mendapat address dari last element list
        address El = First(*L);
        while (Next(El) != LL_Nil)
        {
            El = Next(El);
        }
        // El merupakan last element
        LL_InsertAfter(L,P,El);
    } else
    {
        LL_InsertFirst(L, P);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void LL_DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
    *P = First(*L);
    First(*L) = Next(*P);
}

void LL_DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
    address P = LL_Search(*L,X);
    address Prev;
    if (P != LL_Nil)
    {
        Prev=First(*L);

        if (Prev == P)
        {
            LL_DelFirst(L,&P);
        } else
        {
            while (Next(Prev)!=P)
            {
                Prev=Next(Prev);
            }
            LL_DelAfter(L,&P,Prev);
        }   
    }
    LL_Dealokasi(&P);
}

void LL_DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
{
    address Prev=LL_Nil;
    address Last = First(*L);
    while (Next(Last)!=LL_Nil)
    {
        Prev= Last;
        Last = Next(Last);
    }
    *P = Last;
    if (Prev==LL_Nil)
    {
        LL_DelFirst(L,P);
    } else
    {
        LL_DelAfter(L,P,Prev);
    }
}

void LL_DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
    *Pdel = Next(Prec);
    if (*Pdel!=LL_Nil)
    {
        Next(Prec) = Next(Next(Prec));
    }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void LL_PrintInfoNamaWahana (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
    address P = First(L);
    
    if (!LL_IsEmpty(L))
    {
        MK_printKata(W_Name(Info(P)));
        P = Next(P);
        while (P!=LL_Nil){
            printf(" -> ");
            MK_printKata(W_Name(Info(P)));
            P=Next(P);
        }
    }
}

int LL_NbElmt (List L)
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
{
    int nbelmt = 0;
    address P = First(L);
    while (P!=LL_Nil)
    {
        nbelmt+=1;
        P=Next(P);
    }
    return nbelmt;
}

/****************** PROSES TERHADAP LIST ******************/
void LL_DelAll (List *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
    infotype X;
    while (!LL_IsEmpty(*L))
    {
        LL_DelVLast(L,&X);
    }
}

void LL_writeList(FILE * f, List L){
    address P = First(L);
    while (P != LL_Nil)
    {
        fprintf(f, "%d ", W_WahanaId(Info(P)));
        MK_WriteKata(f,W_Name(Info(P)));fprintf(f,"_");
        MK_WriteKata(f,W_Type(Info(P)));fprintf(f,"_");
        fprintf(f,"%d_",W_Price(Info(P)));
        MK_WritePoint(f,W_Location(Info(P)));fprintf(f,"_");
        MK_WriteKata(f,W_Desc(Info(P)));fprintf(f,"_");
        fprintf(f,"%d_",W_Capacity(Info(P)));
        fprintf(f,"%d_",W_Duration(Info(P)));
        fprintf(f,"%d_",W_UseCount(Info(P)));
        fprintf(f,"%d_",W_Penghasilan(Info(P)));
        fprintf(f,"%d",W_IsBroken(Info(P)));
        if (Next(P)!= LL_Nil)
        {
            fprintf(f,"%c",MK_NEWLINE);
        }
        P = Next(P);
    }
}