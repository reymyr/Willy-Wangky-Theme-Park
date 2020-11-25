/* File header ADT Graph */

#ifndef graph_H
#define graph_H

#include "../boolean.h"
#include "../matriks/matriks.h"
#include "../point/point.h"
#include "player.h"

#define G_Nil NULL

typedef struct tNodeGraph *Gaddress;
typedef struct tNodeGate *GTaddress;

typedef struct tNodeGate {
    int destArea;
    POINT from;
    POINT to;
    GTaddress next;
} Gate;
typedef struct tNodeGraph {
    int area;
    MATRIKS map;
    Gaddress next;
    GTaddress gates;
} NodeGraph;

typedef struct {
    int currentArea;
    Gaddress First;
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

Gaddress AlokasiNodeGraph(char *filename);
/* Mengalokasikan address hasil alokasi elemen NodeGraph dari file map */

void DealokasiNodeGraph (Gaddress P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

GTaddress AlokasiGate (int destArea, POINT from, POINT to);
/* Mengirimkan address hasil alokasi elemen Gate */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan GP, maka GT_DestArea(GP) = destArea, GT_From(GP) = from, GT_To(GP) = to, GT_Next(GP) = G_Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiGate (GTaddress GP);
/* I.S. GP terdefinisi */
/* F.S. GP dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian GTaddress GP */

void InsertFirstGraph (Graph *G, Gaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */

void InsertLastGraph (Graph *G, Gaddress P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */

Gaddress GetAreaAddress(Graph G, int area);
/* Mengembalikan address dari node dengan area=area pada G */

void EnterDoor(Graph G, int area, POINT door, POINT * exit, int * newArea);
/* I.S. G, area, door valid, exit dan newArea bebas */
/* F.S. exit terisi lokasi baru setelah memasuki gerbang, newArea terisi area baru setelah memasuki gerbang */

MATRIKS GetMap(Graph G, int area);
/* Mengembalikan matriks peta pada area */
/* Asumsi area valid */

void printCurrentMap(Graph G, Player P);
/* I.S. Graph terdefinisi */
/* F.S. Map di area sekarang tertulis di layar */

void setTile(Graph * G, int area, POINT pos, char type, int id);
/* I.S. Graph terdefinisi */
/* F.S. Tile pada posisi pos di area 'area' berubah */

void setPlayer(MATRIKS M, Player * P, int x, int y);
/* Menempatkan player pada posisi (x,y) */

void move(Graph *G, Player * P, int move_code, int * status);
/* Prosedur bergerak untuk player */
/* Jika tidak bergerak karena menabrak pagar/wahana, status = 0 */
/* Jika berhasil bergerak, status = 1 */

boolean nearChar(Player P, char c);
/* Mengembalikan true jika player berada di sebelah char c, false jika tidak */

#endif