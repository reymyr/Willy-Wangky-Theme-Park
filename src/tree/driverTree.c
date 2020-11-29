#include <stdio.h>
#include "bintree.h"

/* gcc driverTree.c bintree.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../point/point.c -o driverTree -lm */

int main()
{
    BinTree P;
    readTreeFile(&P, "testtree.txt");

    PrintTree(P, 2);

    printf("Jumlah elemen tree: %d\n", NbElmt(P));
    printf("Jumlah daun: %d\n", NbDaun(P));
    printf("Tinggi tree: %d\n", Tinggi(P));

    return 0;
}
