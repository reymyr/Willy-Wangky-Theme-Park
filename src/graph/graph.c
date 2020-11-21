/* Realisasi ADT Graph */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void CreateEmptyGraph (Graph *G)
/* I.S. G sembarang */
/* F.S. Terbentuk graph G dengan First(*G) = Nil */
{
    First(*G) = Nil;
}