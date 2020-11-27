#include<stdio.h>
#include "stackt.c"
#include<math.h>
int main(){
	Stack S,S1;
	// S buat nambah command S1 buat eksekusi command
	CreateEmpty(&S);
	CreateEmpty(&S1);
	//Tambah command
	printf("1. Tambah command untuk dieksekusi.\n");
	printf("2. Eksekusi Command\n");
	printf("0. Keluar\n");
	printf("Masukkan pilian: ");
	int n;
	scanf("%d",&n);
	int NCmd=0;
	while(n!=0){
		if(n==1){
			if(IsEmpty(S)){
				InverseStack(&S1,&S);
			}
			printf("Tekan 0 untuk kembali.\n");
			printf("Daftar Command:\n");
			printf("1. A\n");
			printf("2. B\n");
			boolean y=true;
			int x;
			scanf("%d",&x);
			if(x==0){
				y=false;
			}
			while(y){
				Push(&S,x);
				NCmd++;
				printf("Command berhasil ditambahkan.\n");
				scanf("%d",&x);
				if(x==0){
					y=false;
				}
			}
		}
		if(n==2){
			InverseStack(&S,&S1);
			int x;
			printf("Masukkan banyaknya command yang akan dieksekusi (Command maks %d): ",NCmd);
			scanf("%d\n",&x);
			while(x>0){
				infotype X;
				Pop(&S1,&X);
				NCmd--;
				printf("Command %d berhasil dieksekusi.\n",X);
				x--;
			}
		}
		printf("1. Tambah command untuk dieksekusi.\n");
		printf("2. Eksekusi Command\n");
		printf("0. Keluar\n");
		printf("Masukkan pilian: ");
		scanf("%d",&n);
	}
}
