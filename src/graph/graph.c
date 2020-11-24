/* Realisasi ADT Graph */

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "../string_production/mesinkata.h"
#include "../matriks/matriks.h"

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

Gaddress AlokasiNodeGraph(char *filename)
/* Mengalokasikan address hasil alokasi elemen NodeGraph dari file map */
{
    Gaddress P = (Gaddress) malloc(sizeof(NodeGraph));
    if (P != G_Nil)
    {
        MK_START(filename);
        G_Area(P) = MK_CToI(MK_CC);
        ADVMATRIKS();
        G_Map(P) = CMatriks;
        G_Next(P) = G_Nil;
        MK_ADV();
        MK_ADV();
        MK_ADVKATA();
        int loop = MK_KataToInt(MK_CKata);
        G_Gates(P) = G_Nil;
        MK_ADV();
        MK_ADVKATA();
        for (size_t i = 0; i < loop; i++)
        {
            int XTo, YTo, XFrom, YFrom, dest;
            XFrom = MK_KataToInt(MK_CKata);
            MK_ADVKATA();
            YFrom = MK_KataToInt(MK_CKata);
            MK_ADVKATA();
            XTo = MK_KataToInt(MK_CKata);
            MK_ADVKATA();
            YTo = MK_KataToInt(MK_CKata);
            MK_ADVKATA();
            dest = MK_KataToInt(MK_CKata);
            GTaddress Gt = AlokasiGate(dest, MakePOINT(XFrom, YFrom), MakePOINT(XTo, YTo));
            GT_Next(Gt) = G_Gates(P);
            G_Gates(P) = Gt;
            MK_ADV();
            MK_ADVKATA();
        }
    }
    return P;
}

void DealokasiNodeGraph (Gaddress P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
    free(P);
}

GTaddress AlokasiGate (int destArea, POINT from, POINT to)
/* Mengirimkan address hasil alokasi elemen Gate */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan GP, maka GT_DestArea(GP) = destArea, GT_From(GP) = from, GT_To(GP) = to, GT_Next(GP) = G_Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
    GTaddress GP = (GTaddress) malloc(sizeof(Gate));

    if (GP != G_Nil){
        GT_DestArea(GP) = destArea;
        GT_From(GP) = from;
        GT_To(GP) = to;
        GT_Next(GP) = G_Nil;
    }

    return GP;
}

void DealokasiGate (GTaddress GP)
/* I.S. GP terdefinisi */
/* F.S. GP dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian GTaddress GP */
{
    free(GP);
}

void InsertFirstGraph (Graph *G, Gaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
    G_Next(P) = G_First(*G);
    G_First(*G) = P;
}

void InsertLastGraph (Graph *G, Gaddress P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
    if (IsEmptyGraph(G))
    {
        InsertFirstGraph(G, P);
    }
    else
    {
        Gaddress last = G_First(*G);
        while (G_Next(last) != G_Nil)
        {
            last = G_Next(last);
        }
        G_Next(last) = P;
    }
}

Gaddress GetAreaAddress(Graph G, int area)
/* Mengembalikan address dari node dengan area=area pada G */
{
    Gaddress P = G_First(G);
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
    
    return P;
}

void EnterDoor(Graph G, int area, POINT door, POINT * exit, int * newArea)
/* I.S. G, area, door valid, exit dan newArea bebas */
/* F.S. exit terisi lokasi baru setelah memasuki gerbang, newArea terisi area baru setelah memasuki gerbang */
{
    GTaddress GP = G_Gates(GetAreaAddress(G, area));
    boolean found = false;
    while (!found && GP != G_Nil)
    {
        if (PointEQ(GT_From(GP), door))
        {
            found = true;
        }
        else
        {
            GP = GT_Next(GP);
        }
    }

    *exit = GT_To(GP);
    *newArea = GT_DestArea(GP);
}

MATRIKS GetMap(Graph G, int area)
/* Mengembalikan matriks peta pada area */
/* Asumsi area valid */
{
    Gaddress P = G_First(G);
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

void printCurrentMap(Graph G, Player P)
/* I.S. Graph terdefinisi */
/* F.S. Map di area sekarang tertulis di layar */
{
    PrintMATRIKS(GetMap(G, G_CurrentArea(G)), P);
    printf("Legend:\n");
    printf("A = Antrian\n");
    printf("P = Player\n");
    printf("W = Wahana\n");
    printf("O = Office\n");
    printf("<, ^, >, V = Gerbang\n\n");
}

void setTile(Graph * G, int area, POINT pos, char type, int id)
/* I.S. Graph terdefinisi */
/* F.S. Tile pada posisi pos di area 'area' berubah */
{
    Gaddress P = GetAreaAddress(*G, area);
    T_Type(Elmt(G_Map(P), Baris(pos), Kolom(pos))) = type;
    T_ID(Elmt(G_Map(P), Baris(pos), Kolom(pos))) = id;
}

void setPlayer(MATRIKS M, Player * P, int x, int y)
/* Menempatkan player pada posisi (x,y) */
{
    if (IsIdxMatriksEff(M, x, y))
    {
        if (T_Type(Elmt(M, x, y)) == '-' || T_Type(Elmt(M, x, y)) == 'O')
        {
            Baris(Pos(*P)) = x;
            Kolom(Pos(*P)) = y;
            Surround(*P)[0] = Elmt(M, x-1, y);
            Surround(*P)[1] = Elmt(M, x, y+1);
            Surround(*P)[2] = Elmt(M, x+1, y);
            Surround(*P)[3] = Elmt(M, x, y-1);
        }
        else
        {
            printf("Tidak bisa menempatkan player di situ\n");
        }
    }
    else
    {
        printf("Koordinat player tidak valid\n");
    }
    
}

void move(Graph *G, Player * P, int move_code, int * status)
/* Prosedur bergerak untuk player */
/* Jika tidak bergerak karena menabrak pagar/wahana, status = 0 */
/* Jika berhasil bergerak, status = 1 */
{
    MATRIKS M = GetMap(*G, G_CurrentArea(*G));
    int x = Baris(Pos(*P));
    int y = Kolom(Pos(*P));
    char nextChar = T_Type(Surround(*P)[move_code]);
    if (nextChar == '-' || nextChar == 'O')
    {
        switch (move_code)
        {
        case 0:
            x--;
            setPlayer(M, P, x, y);
            break;
        case 1:
            y++;
            setPlayer(M, P, x, y);
            break;
        case 2:
            x++;
            setPlayer(M, P, x, y);
            break;
        case 3:
            y--;
            setPlayer(M, P, x, y);
            break;
        default:
            break;
        }
        *status = 1;
    }
    else if (nextChar == '<' || nextChar == 'V' || nextChar == '^' || nextChar == '>')
    {
        POINT exit;
        int newArea;
        switch (move_code)
        {
        case 0:
            x--;
            EnterDoor(*G, G_CurrentArea(*G), MakePOINT(x, y), &exit, &newArea);
            setPlayer(GetMap(*G, newArea), P, --Baris(exit), Kolom(exit));
            break;
        case 1:
            y++;
            EnterDoor(*G, G_CurrentArea(*G), MakePOINT(x, y), &exit, &newArea);
            setPlayer(GetMap(*G, newArea), P, Baris(exit), ++Kolom(exit));
            break;
        case 2:
            x++;
            EnterDoor(*G, G_CurrentArea(*G), MakePOINT(x, y), &exit, &newArea);
            setPlayer(GetMap(*G, newArea), P, ++Baris(exit), Kolom(exit));
            break;
        case 3:
            y--;
            EnterDoor(*G, G_CurrentArea(*G), MakePOINT(x, y), &exit, &newArea);
            setPlayer(GetMap(*G, newArea), P, Baris(exit), --Kolom(exit));
            break;
        default:
            break;
        }
        *status = 1;
        G_CurrentArea(*G) = newArea;
    }
    else
    {
        *status = 0;
    }
    
}

boolean nearGate(Player P)
/* Mengembamilak true jika player berada di sebelah gate, false jika tidak */
{
    for (size_t i = 0; i < 4; i++)
    {
        if (T_Type(Surround(P)[i]) == '^' || T_Type(Surround(P)[i]) == '>' || T_Type(Surround(P)[i]) == 'V' || T_Type(Surround(P)[i]) == '<')
        {
            return true;
        }
    }
    return false;
}