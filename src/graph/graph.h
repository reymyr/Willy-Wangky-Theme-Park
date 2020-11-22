/* File header ADT Graph */

#ifndef graph_H
#define graph_H

#include "../boolean.h"
#include "../peta/peta.h"
#include "../matriks/matriks.h"
#include "../point/point.h"

#define G_Nil NULL

typedef struct tNodeGraph *address;
typedef struct tNodeGate *Gaddress;

typedef struct tNodeGate {
    int destArea;
    POINT from;
    POINT to;
    Gaddress next;
} Gate;
typedef struct tNodeGraph {
    int area;
    MATRIKS map;
    address next;
    Gaddress gates;
} NodeGraph;

typedef struct {
    int currentArea;
    address First;
} Graph;

/*** Selektor, Note: masi belom bener kayanya ***/
#define G_First(G) ((G).First)
#define G_CurrentArea(G) (G).currentArea

#define G_Area(NG) (NG)->area
#define G_Map(NG) (NG)->map
#define G_Next(NG) (NG)->next
#define G_Gates(NG) (NG)->gates

#define GT_DestArea(Gt) (Gt)->destArea
#define GT_From(Gt) (Gt)->from
#define GT_To(Gt) (Gt)->to
#define GT_Next(Gt) (Gt)->next


void CreateEmptyGraph (Graph *G);
/* I.S. G sembarang */
/* F.S. Terbentuk graph G dengan First(G) = Nil */

boolean IsEmptyGraph (Graph *G);
/* mengecek apakah G adalah graph kosong atau bukan */
/* Definisi graph kosong adalah First(G) = Nil */

address AlokasiNodeGraph (int area, MATRIKS M);
/* I.S. */
/* F.S. */

void DealokasiNodeGraph (address P);
/* I.S. */
/* F.S. */

Gaddress AlokasiGate ();
/* I.S. */
/* F.S. */

void DealokasiGate (Gaddress GP);
/* I.S. */
/* F.S. */

void InsertFirstGraph (Graph *G, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */

void InsertLastGraph (Graph *G, address P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

MATRIKS GetMap(Graph G, int area);
/* Mengembalikan matriks peta pada area */
/* Asumsi area valid */

void BacaGraph(Graph *G,char *filename);
/* Membaca File bernama 'filename' yang menyimpan Matriks-matriks yang menyusun area-area pada Peta */
/* I.S. Graph sembarang */
/* F.S. Terbentuk graph sebagai representasi map dari file */

#endif