#include <stdio.h>
#include<math.h>
#include "point.h"

int main(){
	int x,y,a,b;
	printf("Absis1: ");
	scanf("%d",&x);
	printf("Ordinat1: ");
	scanf("%d",&y);
	POINT P1=MakePOINT(x,y);
	TulisPOINT(P1);
	printf("\n");
	printf("Masukkan Koordinat titik kedua!\n");
	printf("Absis2: ");
	scanf("%d",&a);
	printf("Ordinat2: ");
	scanf("%d",&b);
	POINT P2=MakePOINT(a,b);
	if(PointEQ(P1,P2)){
		printf("Titik pertama dan titik kedua terletak pada koordinat yang sama.\n");
	}
	else{
		printf("Titik pertama dan titik kedua terletak pada koordinat yang berbeda.\n");
	}
	int m,n;
	printf("Menggeser POINT pertama sejauh x,y\n");
	printf("x: ");
	scanf("%d",&m);
	printf("y: ");
	scanf("%d",&n);
	TulisPOINT(PlusDelta(P1,m,n));
}
