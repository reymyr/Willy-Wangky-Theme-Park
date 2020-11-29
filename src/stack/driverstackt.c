/* Driver Stack */
#include <stdio.h>
#include "stackt.h"

int main(){
	Stack S,S1;
	CreateEmpty(&S);
	CreateEmpty(&S1);
	Push(&S,"UPGRADE");
	Push(&S,"UPGRADE");
	Push(&S,"BUY");
	InverseStack(&S,&S1);
	while(!IsEmptyStack(S1)){
		infotype X;
		Pop(&S1,&X);
		printf("Command %d berhasil dieksekusi.\n",X);
	}	
}
