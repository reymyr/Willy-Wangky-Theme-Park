#include <stdio.h>
#include <stdlib.h>

#include "../boolean.h"
#include "../jam/jam.h"
#include "prioQueuePengunjung.h"

/* ********* Prototype ********* */
boolean PQ_IsEmpty (PrioQueuePengunjung Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (PQ_Head(Q) == PQ_Nil && PQ_Tail(Q) == PQ_Nil);
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
    else if (PQ_Head(Q) > PQ_Tail(Q))
    {
        return (PQ_MaxEl - PQ_Head(Q) + PQ_Tail(Q) + 1);
    }   
    else
    {
        return (PQ_Tail(Q) - PQ_Head(Q) + 1);
    }   
}

/* *** Kreator *** */
void PQ_MakeEmpty (PrioQueuePengunjung * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk*/
/* Proses : Membuat sebuah Q kosong */
{
    PQ_Head(*Q) = PQ_Nil;
    PQ_Tail(*Q) = PQ_Nil;
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
        int i = PQ_Tail(*Q);
        PQ_Tail(*Q) = (PQ_Tail(*Q) + 1) % PQ_MaxEl;
        while (P_Prio(PQ_Elmt(*Q, i)) > P_Prio(X) && i != (PQ_Head(*Q)-1+PQ_MaxEl) % PQ_MaxEl)
        {
            PQ_Elmt(*Q, (i+1) % PQ_MaxEl) = PQ_Elmt(*Q, i);
            i = (i-1+PQ_MaxEl) % PQ_MaxEl;
        }
        PQ_Elmt(*Q, (i+1) % PQ_MaxEl) = X;
    }
}

void PQ_EnqueueTimeLeft(PrioQueuePengunjung * Q, Pengunjung X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan timeLeft */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan timeLeft,
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
        int i = PQ_Tail(*Q);
        PQ_Tail(*Q) = (PQ_Tail(*Q) + 1) % PQ_MaxEl;
        while (P_TimeLeft(PQ_Elmt(*Q, i)) > P_TimeLeft(X) && i != (PQ_Head(*Q)-1+PQ_MaxEl) % PQ_MaxEl)
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
        PQ_Head(*Q) = PQ_Nil;
        PQ_Tail(*Q) = PQ_Nil;
    }
    else
    {
        PQ_Head(*Q) = (PQ_Head(*Q) + 1) % PQ_MaxEl;
    }
}

/* Operasi Tambahan */
void PQ_PrintQueuePengunjung (PrioQueuePengunjung Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
Antrian[NbElmt/MaxEl] :
(List_Wahana-1), kesabaran: kesabaran-1
...
(List_Wahana-n), kesabaran: kesabaran-n
*/
{
    Pengunjung P;
    printf(" --- Antrian [%d/%d] ------------------------\n", PQ_NBElmt(Q), PQ_MaxEl);
    while (!PQ_IsEmpty(Q))
    {
        PQ_Dequeue(&Q, &P);
        AK_TulisIsiTab(P_Wahana(P));
        printf(", kesabaran: %d\n", P_Kesabaran(P));
    }
}

void PQ_decTimeLeft(PrioQueuePengunjung * Q, JAM curTime)
/* I.S. Q terdefinisi */
/* F.S. timeLeft Semua pengunjung dalam Q berkurang sesuai startTime dan curTime  */
{
    for (int i = 0; i < PQ_NBElmt(*Q); i++)
    {
        int currentIdx = (PQ_Head(*Q) + i) % PQ_MaxEl;
        Pengunjung P = PQ_Elmt(*Q, currentIdx);
        int timePassed = Durasi(P_StartTime(P), curTime);
        P_StartTime(PQ_Elmt(*Q, currentIdx)) = curTime;
        P_TimeLeft(PQ_Elmt(*Q, currentIdx)) -= timePassed;
    }
}

int PQ_getWahanaCount(PrioQueuePengunjung Q, Kata K)
/* Mengembalikan banyak pengunjung dalam Q yang sedang menaiki wahana bernama K */
{
    int count = 0;
    for (int i = 0; i < PQ_NBElmt(Q); i++)
    {
        int currentIdx = (PQ_Head(Q) + i) % PQ_MaxEl;
        Pengunjung P = PQ_Elmt(Q, currentIdx);
        if (MK_isKataSama(K, P_CurrentWahana(P)))
        {
            count++;
        }        
    }
    return count;
}

void PQ_WahanaRusak(PrioQueuePengunjung * Q, PrioQueuePengunjung * QW, Kata K)
/* Mengeluarkan semua pengunjung yang sedang menaiki wahana K dari QW ke Q saat wahana rusak */
{
    PrioQueuePengunjung PQTemp;
    Pengunjung PTemp;
    PQ_MakeEmpty(&PQTemp);
    int count = PQ_getWahanaCount(*QW, K);
    while (count > 0)
    {
        PQ_Dequeue(QW, &PTemp);
        if (MK_isKataSama(P_CurrentWahana(PTemp), K))
        {
            count--;
            P_Prio(PTemp)--;
            AK_AddAsLastEl(&P_Wahana(PTemp), K);
            PQ_Enqueue(Q, PTemp);
        }
        else
        {
            PQ_EnqueueTimeLeft(&PQTemp, PTemp);
        }
    }
    while (!PQ_IsEmpty(PQTemp))
    {
        PQ_Dequeue(&PQTemp, &PTemp);
        PQ_EnqueueTimeLeft(QW, PTemp);
    }
}