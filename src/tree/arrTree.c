#include "arrTree.h"

void AT_MakeEmpty(ArrTree *T)
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
{
    AT_Neff(*T) = 0;
}

IdxType AT_SearchI(ArrTree T, BT_infotype x)
/* Mengembalikan index tree dalam array yang memiliki Akar(P) = x */
{
    if (AT_Neff(T) == 0)
    {
        return IdxUndef;
    }
    else
    {
        boolean found = false;
        IdxType i = 0;
        while (!found && i <= AT_Neff(T)-1)
        {
            if (Akar(AT_Elmt(T, i)) == x)
            {
                found = true;
            }
            i++;
        }  

        if (found)
        {
            return i-1;
        }
        else
        {
            return IdxUndef;
        }   
    }
}

BinTree AT_SearchBase(ArrTree T, BT_infotype x)
/* Mengembalikan tree dalam array yang memiliki Akar(P) = x */
{
    return AT_Elmt(T, AT_SearchI(T, x));
}