/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "boolean.h"
#include <stdio.h>

#define Nil -1
#define MaxEl 100
/* Nil adalah stack dengan elemen kosong . */

typedef char infotype[50];
typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  infotype T[MaxEl]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
{
	Top(*S)= Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmpty (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return (Top(S)==Nil);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	Top(*S)++;
	InfoTop(*S)=X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
	*X=InfoTop(*S);
	Top(*S)--;
}

//Kata kakaknya kalo mau eksekusi command di InverseStack dulu baru nanti di-pop
//Kalo mau nambah command setelah eksekusi command InverseStack->Push
void InverseStack(Stack *Sin, Stack *Sout){
	infotype* X;
	while(Top(*Sin)!=Nil){
		*X=InfoTop(*Sin);
		Top(*Sin)--;
		Top(*Sout)++;
		InfoTop(*Sout)=*X;
	}
}

void CopyStack(Stack *Sin, Stack *Sout){
	Stack *STemp;
	Top(*STemp)=Nil;
	infotype* X;
	while(Top(*Sin)!=Nil){
		*X=InfoTop(*Sin);
		Top(*Sin)--;
		Top(*STemp)++;
		InfoTop(*STemp)=*X;
	}
	while(Top(*STemp)!=Nil){
		*X=InfoTop(*STemp);
		Top(*STemp)--;
		Top(*Sout)++;
		InfoTop(*Sout)=*X;
	}
}

#endif

