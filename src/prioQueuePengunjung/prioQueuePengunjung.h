/* File : prioQueuePengunjung.h */
/* Definisi ADT Priority Queue pengunjung dengan representasi array secara eksplisit dan alokasi statik */
/* Model Implementasi Versi III dengan circular buffer */
/* Elemen queue terurut tidak mengecil berdasarkan elemen prio */

#ifndef PRIOQUEUEPENGUNJUNG_H
#define PRIOQUEUEPENGUNJUNG_H

#include "arrKata.h"
#include "../boolean.h"
#include "../string_production/mesinkata.h"

#define PQ_Nil -1
/* Konstanta untuk mendefinisikan address tak terdefinisi */

#define PQ_MaxEl 10
/* Konstanta untuk mendefinisikan elemen maksimal queue */

/* Definisi elemen dan address */
typedef struct {
    int prio;  /* (1 adalah prioritas tertinggi) */
    ArrKata wahana;  /* nama dari wahana yang ingin dinaiki pengunjung */
    int kesabaran; /* 10-0 (kesabaran 0 berarti sudah habis) */
} Pengunjung; 

typedef int PQaddress;   /* indeks tabel */

/* Contoh deklarasi variabel bertype PrioQueuePengunjung : */
typedef struct {
    Pengunjung T[PQ_MaxEl+1];   /* tabel penyimpan elemen */
    PQaddress HEAD;               /* alamat penghapusan */
    PQaddress TAIL;               /* alamat penambahan */
} PrioQueuePengunjung;
/* Definisi PrioQueuePengunjung kosong: HEAD=PQ_Nil; TAIL=PQ_Nil. */

/* ********* AKSES (Selektor) ********* */
/* Jika P adalah Pengunjung dan Q adalah PrioQueuePengunjung, maka akses elemen : */
#define P_Prio(P)      (P).prio
#define P_Wahana(P)    (P).wahana
#define P_Kesabaran(P) (P).kesabaran

#define PQ_Head(Q)     (Q).HEAD
#define PQ_Tail(Q)     (Q).TAIL
#define PQ_InfoHead(Q) (Q).T[(Q).HEAD]
#define PQ_InfoTail(Q) (Q).T[(Q).TAIL]
#define PQ_Elmt(Q,i)   (Q).T[(i)]


/* ********* Prototype ********* */
boolean PQ_IsEmpty (PrioQueuePengunjung Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean PQ_IsFull (PrioQueuePengunjung Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak PQ_MaxEl */
int PQ_NBElmt (PrioQueuePengunjung Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void PQ_MakeEmpty (PrioQueuePengunjung * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */

/* *** Destruktor *** */
void PQ_DeAlokasi(PrioQueuePengunjung * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, PQ_MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void PQ_Enqueue (PrioQueuePengunjung * Q, Pengunjung X);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X disisipkan pada posisi yang tepat sesuai dengan prioritas,
        TAIL "maju" dengan mekanisme circular buffer; */
void PQ_Dequeue (PrioQueuePengunjung * Q, Pengunjung * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer;
        Q mungkin kosong */

/* Operasi Tambahan */
void PQ_PrintQueuePengunjung (PrioQueuePengunjung Q);
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
Antrian[NbElmt/MaxEl] :
(List_Wahana-1), kesabaran: kesabaran-1
...
(List_Wahana-n), kesabaran: kesabaran-n
*/


#endif
