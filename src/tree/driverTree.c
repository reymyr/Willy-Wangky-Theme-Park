#include "bintree.h"

/* gcc .\driverTree.c .\bintree.c ..\string_production\mesinkata.c ..\string_production\mesinkar.c ..\point\point.c */

int main()
{
    BinTree P;
    readTreeFile(&P, "testtree.txt");

    PrintTree(P, 2);
    return 0;
}
