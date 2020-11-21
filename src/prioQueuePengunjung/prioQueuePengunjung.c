#include <stdio.h>
#include <stdlib.h>

#include "boolean.h"
#include "prioQueuePengunjung.h"

/* ********* Prototype ********* */
boolean PQ_IsEmpty (PrioQueuePengunjung Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (PQ_Head(Q) == Nil && Tail(Q) == Nil);
}
boolean PQ_IsFull (PrioQueuePengunjung Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak PQ_MaxEl */
{
    return PQ_NBElmt(Q) == PQ_MaxEl;
}
int PQ_NBElmt (PrioQueuePengunjung Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if (PQ_IsEmpty(Q))
    {
        return 0;
    }
    else if (PQ_Head(Q) > Tail(Q))
    {
        return (PQ_MaxEl - PQ_Head(Q) + Tail(Q) + 1);
    }   
    else
    {
        return (Tail(Q) - PQ_Head(Q) + 1);
    }   
}

/* *** Kreator *** */
void PQ_MakeEmpty (PrioQueuePengunjung * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk*/
/* Proses : Membuat sebuah Q kosong */
{
    PQ_Head(*Q) = Nil;
    PQ_Tail(*Q) = Nil;
}

/* *** Primitif Add/Delete *** */
void PQ_Enqueue (PrioQueuePengunjung * Q, Pengunjung X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
{
    if (PQ_IsEmpty(*Q))
    {
        PQ_Head(*Q) = 0;
        PQ_Tail(*Q) = 0;
        PQ_InfoTail(*Q) = X;
    }
    else
    {
        int i = Tail(*Q);
        PQ_Tail(*Q) = (Tail(*Q) + 1) % PQ_MaxEl;
        while (Prio(Elmt(*Q, i)) > Prio(X) && i != (Head(*Q)-1+PQ_MaxEl) % PQ_MaxEl)
        {
            PQ_Elmt(*Q, (i+1) % PQ_MaxEl) = PQ_Elmt(*Q, i);
            i = (i-1+PQ_MaxEl) % PQ_MaxEl;
        }
        PQ_Elmt(*Q, (i+1) % PQ_MaxEl) = X;
    }
}
void PQ_Dequeue (PrioQueuePengunjung * Q, Pengunjung * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */
{
    *X = PQ_InfoHead(*Q);
    if (PQ_Head(*Q) == PQ_Tail(*Q))
    {
        PQ_Head(*Q) = Nil;
        PQ_Tail(*Q) = Nil;
    }
    else
    {
        PQ_Head(*Q) = (PQ_Head(*Q) + 1) % PQ_MaxEl;
    }
}

/* Operasi Tambahan */
void PrintPrioQueuePengunjung (PrioQueuePengunjung Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/
{
    printf("Antrian [%d/%d] :\n", PQ_NBElmt(Q), PQ_MaxEl);
    for (int i = 0; i < PQ_NBElmt(Q); i++)
    {
        int current = (PQ_Head(Q) + i) % PQ_MaxEl;
        printf("(GANTI JADI LIST WAHANA),  kesabaran: %d\n", P_Kesabaran(PQ_Elmt(Q, current)));
    }
}