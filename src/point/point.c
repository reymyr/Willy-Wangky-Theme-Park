/*File: point.c*/
/* Body ADT point */

#include "point.h"
#include "../boolean.h"
#include <math.h>
#include <stdio.h>

/* *** Notasi Akses: Selektor POINT *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

/*Konstruktor point*/
POINT MakePOINT(int X, int Y)
/*Membuat point*/
{
	/*KAMUS LOKAL*/
	POINT P;
	/*ALGORITMA*/
	P.X = X;
	P.Y = Y;
	return P;
}

void TulisPOINT (POINT P)
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan bulat.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
{
	/*KAMUS LOKAL*/
	int X;
	int Y;
	/*ALGORITMA*/
	X = P.X;
	Y = P.Y;
	printf("(%d,%d)\n", &X, &Y);
}

POINT PlusDelta (POINT P, int deltaX, int deltaY)
/* Mengirim salinan P yang absisnya adalah P.X + deltaX dan ordinatnya adalah P.Y + deltaY */
{
	/*KAMUS LOKAL*/
	int X, NewX;
	int Y, NewY;
	POINT PNew;
	/*ALGORITMA*/
	X = P.X;
	Y = P.Y;
	NewX = X + deltaX;
	NewY = Y + deltaY;
	PNew = MakePOINT(NewX, NewY);
	return PNew;
}

int Panjang (POINT P1, POINT P2)
/* Menghitung jarak dari titik P1 ke P2*/
{
	/*KAMUS LOKAL*/
	int X1, X2, distX;
	int Y1, Y2, distY;
	int dist;
	/*ALGORITMA*/
	X1 = P1.X;
	Y1 = P1.Y;
	X2 = Absis(P2);
	Y2 = Ordinat(P2);
	distX = X1 - X2;
	distY = Y1 - Y2;
	dist = sqrt(distX*distX + distY*distY);
	return dist;
}

void Geser (POINT *P, int deltaX, int deltaY)
/* I.S. P terdefinisi */
/* F.S. P digeser, absisnya sebesar deltaX dan ordinatnya sebesar deltaY */
{
	/*KAMUS LOKAL*/
	int X, NewX;
	int Y, NewY;
	/*ALGORITMA*/
	X = P->X;
	Y = P->Y;
	NewX = X + deltaX;
	NewY = Y + deltaY;
	P->X = NewX; 
	P->Y = NewY;
}

	
