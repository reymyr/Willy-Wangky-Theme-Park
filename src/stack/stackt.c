
#include "../boolean.h"
#include "stackt.h"

S_infotype CreateStackInfo(Kata name, JAM time, int money, POINT pos)
/* Membentuk elemen Stack dari data inputan */
{
    S_infotype SI;

    S_Name(SI) = name;
    S_TimeNeeded(SI) = time;
    S_MoneyNeeded(SI) = money;
    S_PosWahana(SI) = pos;

    return SI;
}

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas S_MaxEl */
/* jadi indeksnya antara 0.. S_MaxEl */
/* Ciri stack kosong : TOP bernilai Nil */
{
	Top(*S)= Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return (Top(S)==Nil);
}
boolean IsFull (Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
    return Top(S) == S_MaxEl-1;
}
int NbElmtStack (Stack S)
/* Mengirim banyak elemen Stack */
{
    S_infotype SI;
    int count = 0;
    while (!IsEmptyStack(S))
    {
        count++;
        Pop(&S, &SI);
    }
    return count;
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, S_infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	Top(*S)++;
	InfoTop(*S)=X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, S_infotype* X)
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
	CreateEmptyStack(Sout);
	S_infotype X;
	while(Top(*Sin)!=Nil){
		X=InfoTop(*Sin);
		Top(*Sin)--;
		Top(*Sout)++;
		InfoTop(*Sout)=X;
	}
}

void CopyStack(Stack *Sin, Stack *Sout){
	CreateEmptyStack(Sout);
	Stack *STemp;
	Top(*STemp)=Nil;
	S_infotype* X;
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

int TotalMoney(Stack S)
/* Mengembalikan total uang yang dibutuhkan dari semua elemen Stack */
{
    S_infotype SI;
    int total = 0;
    while (!IsEmptyStack(S))
    {
        Pop(&S, &SI);
		total += S_MoneyNeeded(SI);
    }
    return total;
}

JAM TotalTime(Stack S)
/* Mengembalikan total waktu yang dibutuhkan dari semua elemen Stack */
{
    S_infotype SI;
    JAM total = MakeJAM(0, 0, 0);
    while (!IsEmptyStack(S))
    {
        Pop(&S, &SI);
        total = MenitToJAM(JAMToMenit(total)+JAMToMenit(S_TimeNeeded(SI)));
    }
    return total;
}