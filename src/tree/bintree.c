// NIM              : 13519167
// Nama             : Reyhan Emyr Arrosyid
// Tanggal          : 25 November 2020
// Topik praktikum  : ADT Binary Tree
// Deskripsi        : Implementasi bintree.h

/* Modul lain yang digunakan : */
#include <stdlib.h>
#include <stdio.h>
#include "../boolean.h"
#include "bintree.h"
#include "../string_production/mesinkata.h"
#include "../wahana/ArrWahana.h"
#include "../wahana/wahana.h"

/* *** Konstruktor *** */
BinTree Tree(BT_infotype Akar, BinTree L, BinTree R)
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (BT_Nil) jika alokasi gagal */
{
    BinTree P = (BinTree) malloc(sizeof(Node));
    if (P != BT_Nil)
    {
        Akar(P) = Akar;
        Left(P) = L;
        Right(P) = R;
    }
    return P;
}
void MakeTree(BT_infotype Akar, BinTree L, BinTree R, BinTree *P)
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R 
		jika alokasi berhasil. P = BT_Nil jika alokasi gagal. */
{
    *P = (BinTree) malloc(sizeof(Node));
    if (*P != BT_Nil)
    {
        Akar(*P) = Akar;
        Left(*P) = L;
        Right(*P) = R;
    }
}
BinTree BuildBalanceTree(int n)
/* Menghasilkan sebuah balanced tree dengan n node, nilai setiap node dibaca */
{
    if (n == 0)
    {
        return BT_Nil;
    }
    else
    {
        int x;
        scanf("%d", &x);
        BinTree P = AlokNode(x);
        if (P != BT_Nil)
        {
            int nL = n / 2;
            int nR = n - nL - 1;
            BinTree L = BuildBalanceTree(nL);
            BinTree R = BuildBalanceTree(nR);
            Left(P) = L;
            Right(P) = R;
        }
        return P;
    }
}

/* Manajemen Memory */
addrNode AlokNode(BT_infotype X)
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak BT_Nil, dan misalnya menghasilkan P, 
  maka Akar(P) = X, Left(P) = BT_Nil, Right(P)=BT_Nil */
/* Jika alokasi gagal, mengirimkan BT_Nil */
{
    addrNode P = (addrNode) malloc(sizeof(Node));
    if (P != BT_Nil)
    {
        Akar(P) = X;
        Left(P) = BT_Nil;
        Right(P) = BT_Nil;
    }
    return P;
}
void DealokNode(addrNode P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */
{
    free(P);
}

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P)
/* Mengirimkan true jika P adalah pohon biner kosong */
{
    return P == BT_Nil;
}
boolean IsTreeOneElmt(BinTree P)
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {
        return Right(P) == BT_Nil && Left(P) == BT_Nil;
    }
}
boolean IsUnerLeft(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {
        return Right(P) == BT_Nil && Left(P) != BT_Nil;
    }
}
boolean IsUnerRight(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {
        return Right(P) != BT_Nil && Left(P) == BT_Nil;
    }
}
boolean IsBiner(BinTree P)
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {
        return Right(P) != BT_Nil && Left(P) != BT_Nil;
    }
}

void readTreeFile(BinTree *P, char* filename)
{
    MK_START(filename); 
    readTree(P);
}

void readTree(BinTree *P)
{

    MK_ADV();
    if (MK_CC == ')')
    {
        *P = BT_Nil;
    }
    else
    {
        MK_SalinKataTree();
        *P = Tree(MK_KataToInt(MK_CKata), BT_Nil, BT_Nil);
        readTree(&Left(*P));
        readTree(&Right(*P));
    }
    MK_ADV();
}

void PrintTreeLevel(BinTree P, int h, int level)
{
    if (!IsTreeEmpty(P))
    {
        for (size_t i = 0; i < h*(level-1); i++)
        {
            printf(" ");
        }
        printf("%d\n", Akar(P));
        if (Left(P) != BT_Nil)
        {
            PrintTreeLevel(Left(P), h, level+1);
        }
        if (Right(P) != BT_Nil)
        {
            PrintTreeLevel(Right(P), h, level+1);
        }
    }
}
void PrintTree(BinTree P, int h)
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/
{
    PrintTreeLevel(P, h, 1);
}

/* *** Searching *** */
boolean SearchTree(BinTree P, BT_infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {    
        if (Akar(P) == X)
        {
            return true;
        }
        else
        {
            return SearchTree(Left(P), X) || SearchTree(Right(P), X);
        }
    }
}

BinTree SearchNode(BinTree P, BT_infotype X)
{
    if (Akar(P)==X)
    {
        return P;
    }
    else
    {
        if (SearchTree(Left(P), X))
        {
            SearchNode(Left(P), X);
        }
        else if (SearchTree(Right(P), X))
        {
            SearchNode(Right(P), X);
        }
    }    
    return BT_Nil;
}

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P)
/* Mengirimkan banyaknya elemen (node) pohon biner P */
{
    if (IsTreeEmpty(P))
    {
        return 0;
    }
    else
    {
        return NbElmt(Left(P)) + 1 + NbElmt(Right(P));
    }    
}
int NbDaun(BinTree P)
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
{
    if (IsTreeOneElmt(P))
    {
        return 1;
    }
    else
    {
        if (IsUnerLeft(P))
        {
            return NbDaun(Left(P));
        }
        else if (IsUnerRight(P))
        {
            return NbDaun(Right(P));
        }
        else
        {
            return NbDaun(Left(P)) + NbDaun(Right(P));
        }     
    }    
}
boolean IsSkewLeft(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
{
    if (IsTreeEmpty(P))
    {
        return true;
    }
    else if (IsTreeOneElmt(P))
    {
        return true;
    }    
    else
    {
        if (IsUnerLeft(P))
        {
            return IsSkewLeft(Left(P));
        }
        else
        {
            return false;
        }        
    }    
}
boolean IsSkewRight(BinTree P)
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
{
    if (IsTreeEmpty(P))
    {
        return true;
    }
    else if (IsTreeOneElmt(P))
    {
        return true;
    }    
    else
    {
        if (IsUnerRight(P))
        {
            return IsSkewRight(Right(P));
        }
        else
        {
            return false;
        }        
    }   
}
int Level(BinTree P, BT_infotype X)
/* Mengirimkan level dari node X yang merupakan salah satu simpul dari pohon biner P. 
   Akar(P) level-nya adalah 1. Pohon P tidak kosong. */
{
    if (Akar(P) == X)
    {
        return 1;
    }
    else
    {
        if (SearchTree(Left(P), X))
        {
            return 1 + Level(Left(P), X);
        }
        else
        {
            return 1 + Level(Right(P), X);
        }
    }    
}
int Tinggi(BinTree P)
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */
{
    if (IsTreeEmpty(P))
    {
        return 0;
    }
    else
    {
        int tL = Tinggi(Left(P));
        int tR = Tinggi(Right(P));
        if (tL > tR) 
        {
            return 1 + tL;
        } 
        else 
        {
            return 1 + tR;
        }      
    }    
}

/* *** Operasi lain *** */
void AddDaunTerkiri(BinTree *P, BT_infotype X)
/* I.S. P boleh kosong */
/* F.S. P bertambah simpulnya, dengan X sebagai simpul daun terkiri */
{
    if (IsTreeEmpty(*P))
    {
        *P = AlokNode(X);
    }
    else
    {
        AddDaunTerkiri(&Left(*P), X);
    }    
}
void AddDaun(BinTree *P, BT_infotype X, BT_infotype Y, boolean Kiri)
/* I.S. P tidak kosong, X adalah salah satu daun Pohon Biner P */
/* F.S. P bertambah simpulnya, dengan Y sebagai anak kiri X (jika Kiri = true), atau 
        sebagai anak Kanan X (jika Kiri = false) */
/*		Jika ada > 1 daun bernilai X, diambil daun yang paling kiri */
{
    if (IsTreeOneElmt(*P))
    {
        if (Kiri)
        {
            Left(*P) = AlokNode(Y);
        }
        else
        {
            Right(*P) = AlokNode(Y);
        }
    }
    else
    {
        if (SearchTree(Left(*P), X))
        {
            AddDaun(&Left(*P), X, Y, Kiri);
        }
        else
        {
            AddDaun(&Right(*P), X, Y, Kiri);
        }        
    }        
}
void DelDaunTerkiri(BinTree *P, BT_infotype *X)
/* I.S. P tidak kosong */
/* F.S. P dihapus daun terkirinya, dan didealokasi, dengan X adalah info yang semula 
        disimpan pada daun terkiri yang dihapus */
{
    addrNode PTemp;
    if (IsTreeOneElmt(*P))
    {
        *X = Akar(*P);
        PTemp = *P;
        *P = BT_Nil;
        DealokNode(PTemp);
    }
    else
    {
        if (IsUnerRight(*P))
        {
            DelDaunTerkiri(&Right(*P), X);
        }
        else
        {
            DelDaunTerkiri(&Left(*P), X);
        }        
    } 
}
void DelDaun(BinTree *P, BT_infotype X)
/* I.S. P tidak kosong, minimum ada 1 daun bernilai X. */
/* F.S. Semua daun bernilai X dihapus dari P. */
{
    if (IsTreeEmpty(*P)) {

    } else if (IsTreeOneElmt(*P)) {
        if (Akar(*P) == X) {
            *P = BT_Nil;
            DealokNode(*P);
        }
    } else {
        DelDaun(&Left(*P),X);
        DelDaun(&Right(*P),X);
    }
}

/* *** Binary  Search  Tree  *** */
boolean BSearch(BinTree P, BT_infotype X)
/* Mengirimkan true jika ada node dari P yang bernilai X */
{
    if (IsTreeEmpty(P))
    {
        return false;
    }
    else
    {
        if (Akar(P) == X)
        {
            return true;
        }
        else
        {
            if (X < Akar(P))
            {
                return BSearch(Left(P), X);
            }
            else
            {
                return BSearch(Right(P), X);
            }            
        }        
    }    
}

void InsSearch(BinTree *P, BT_infotype X)
/* Menghasilkan sebuah pohon Binary Search Tree P dengan tambahan simpul X. Belum ada simpul P yang bernilai X. */
{
    if (IsTreeEmpty(*P))
    {
        MakeTree(X, BT_Nil, BT_Nil, P);
    }
    else
    {
        if (IsTreeOneElmt(*P))
        {
            if (X < Akar(*P))
            {
                Left(*P) = AlokNode(X);
            }
            else
            {
                Right(*P) = AlokNode(X);
            }
        }
        else
        {
            if (X < Akar(*P))
            {
                InsSearch(&Left(*P), X);
            }
            else
            {
                InsSearch(&Right(*P), X);
            }          
        }        
    }  
}

void DelBtree(BinTree *P, BT_infotype X)
/* I.S. Pohon P tidak  kosong */
/* F.S. Nilai X yang dihapus pasti ada */
/* Sebuah node dengan nilai X dihapus */
{
    if (IsTreeOneElmt(*P))
    {
        addrNode PTemp = *P;
        DealokNode(PTemp);
        *P = BT_Nil;
    }
    else
    {
        if (X < Akar(*P))
        {
            DelBtree(&Left(*P), X);
        }
        else
        {
            DelBtree(&Right(*P), X);
        }        
    }    
}

boolean isChild(BinTree P, BT_infotype x, BT_infotype y)
/* mengembalikan apakah x anak dari y */
{
    BinTree Pt = SearchNode(P, y);
    if (IsUnerLeft(Pt))
    {
        return Akar(Left(Pt)) == x;
    }
    else if (IsUnerRight(Pt))
    {
        return Akar(Right(Pt)) == x;
    }
    else
    {
        return (Akar(Left(Pt)) == x) || Akar(Right(Pt)) == x;
    }   
}

void getChildId(BinTree P, BT_infotype x, BT_infotype * CL, BT_infotype * CR)
{
    BinTree Pt = SearchNode(P, x);
    *CL = -1;
    *CR = -1;
    if (IsUnerLeft(Pt))
    {
        *CL = Akar(Left(Pt));
    }
    else if (IsUnerRight(Pt))
    {
        *CR = Akar(Right(Pt));
    }
    else
    {
        *CL = Akar(Left(Pt));
        *CR = Akar(Right(Pt));
    } 
}