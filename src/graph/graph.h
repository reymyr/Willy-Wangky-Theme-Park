/* File header ADT Graph */

#ifndef graph_H
#define graph_H

#include "../boolean.h"
#include "../peta/peta.h"

#define Nil NULL

typedef struct tNodeGraph *address;
typedef struct tNodeGraph {
    Peta map;
    address next;
    address prev;
} NodeGraph;

typedef struct {
    address First;
} Graph;

/*** Selektor, Note: masi belom bener kayanya ***/
#define Map(G) (G)->map
#define First(G) ((G).First)
#define Next(G) (G)->next
#define Prev(G) (G)->prev



void CreateEmptyGraph (Graph *G);
/* I.S. G sembarang */
/* F.S. Terbentuk graph G dengan First(*G) = Nil */

#endif