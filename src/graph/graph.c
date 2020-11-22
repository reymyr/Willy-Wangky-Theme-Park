/* Realisasi ADT Graph */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void CreateEmptyGraph (Graph *G)
/* I.S. G sembarang */
/* F.S. Terbentuk graph G dengan G_First(*G) = G_Nil */
{
    G_First(*G) = G_Nil;
    G_CurrentArea(*G) = 0;
}

boolean IsEmptyGraph (Graph *G)
/* mengecek apakah G adalah graph kosong atau bukan */
/* Definisi graph kosong adalah G_First(G) = Nil */
{
    return G_First(*G) == G_Nil;
}

address AlokasiNodeGraph (int area, MATRIKS M)
/* Mengirimkan address hasil alokasi elemen NodeGraph */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka  G_Area(P) = area, G_Map(P) = M, G_Next(P) = G_Nil, G_Gates(P) = G_Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    address P = (address) malloc(sizeof(NodeGraph));

    if (P != G_Nil)
    {
        G_Area(P) = area;
        G_Map(P) = M;
        G_Next(P) = G_Nil;
        G_Gates(P) = G_Nil;
    }

    return P;
}

void DealokasiNodeGraph (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(P);
}

Gaddress AlokasiGate (int destArea, POINT from, POINT to)
/* Mengirimkan address hasil alokasi elemen Gate */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan GP, maka GT_DestArea(GP) = destArea, GT_From(GP) = from, GT_To(GP) = to, GT_Next(GP) = G_Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    Gaddress GP = (Gaddress) malloc(sizeof(Gate));

    if (GP != G_Nil){
        GT_DestArea(GP) = destArea;
        GT_From(GP) = from;
        GT_To(GP) = to;
        GT_Next(GP) = G_Nil;
    }

    return GP;
}

void DealokasiGate (Gaddress GP)
/* I.S. GP terdefinisi */
/* F.S. GP dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian Gaddress GP */
{
    free(GP);
}

void InsertFirstGraph (Graph *G, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    G_Next(P) = G_First(*G);
    G_First(*G) = P;
}

void InsertLastGraph (Graph *G, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (IsEmptyGraph(G))
    {
        InsertFirstGraph(G, P);
    }
    else
    {
        address last = G_First(*G);
        while (G_Next(last) != G_Nil)
        {
            last = G_Next(last);
        }
        G_Next(last) = P;
    }
}

MATRIKS GetMap(Graph G, int area)
/* Mengembalikan matriks peta pada area */
/* Asumsi area valid */
{
    address P = G_First(G);
    boolean found = false;
    while (!found && P != G_Nil)
    {
        if (G_Area(P) == area)
        {
            found = true;
        }
        else
        {
            P = G_Next(P);
        }
    }
    
    return G_Map(P);
}

void BacaGraph(Graph *G, char *filename)
/* Membaca File bernama 'filename' yang menyimpan Matriks-matriks yang menyusun area-area pada Peta */
/* I.S. Graph sembarang */
/* F.S. Terbentuk graph sebagai representasi map dari file */
{
    CreateEmptyGraph(G);
    STARTMATRIKS(filename);
    int i = 0;
    while (!ENDMATRIKS)
    {
        address P = AlokasiNodeGraph(i, CMatriks);
        InsertLastGraph(G, P);
        i++;
        ADVMATRIKS();
    }
}

void printCurrentMap(Graph G)
/* I.S. Graph terdefinisi */
/* F.S. Map di area sekarang tertulis di layar */
{
    PrintMATRIKS(GetMap(G, G_CurrentArea(G)));
    printf("Legend:\n");
    printf("A = Antrian\n");
    printf("P = Player\n");
    printf("W = Wahana\n");
    printf("O = Office\n");
    printf("<, ^, >, V = Gerbang\n\n");
}