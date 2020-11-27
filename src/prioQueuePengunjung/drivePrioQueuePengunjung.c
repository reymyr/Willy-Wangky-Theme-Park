#include <stdio.h>
#include "prioQueuePengunjung.h"

/* gcc .\drivePrioQueuePengunjung.c .\prioQueuePengunjung.c .\arrKata.c ..\string_production\mesinkata.c ..\string_production\mesinkar.c ..\point\point.c -o driveQ -lm */

int main()
{
    int input, nWahana, prio, sabar;
    PrioQueuePengunjung PQ;
    Pengunjung P;

    PQ_MakeEmpty(&PQ);

    do
    {
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Full/Empty\n");
        printf("4. Exit\n");

        PQ_PrintQueuePengunjung(PQ);

        printf("Pilihan: ");
        scanf("%d", &input);
        printf("\n");
        if (input == 4)
        {
            break;
        }

        switch (input)
        {
        case 1:

            printf("Masukkan banyak wahana pengungjung: ");
            scanf("%d", &nWahana);

            
            for (size_t i = 0; i < nWahana; i++)
            {
                printf("Nama wahana ke-%d: ", i+1);
                MK_STARTKATAINPUT();
                AK_AddAsLastEl(&P_Wahana(P), MK_CKata);
            }

            printf("Prioritas pengunjung: ");
            scanf("%d", &prio);          
            P_Prio(P) = prio; 

            printf("Kesabaran pengunjung: ");
            scanf("%d", &sabar);
            P_Kesabaran(P) = sabar;

            PQ_Enqueue(&PQ, P);

            break;
        case 2:
            if (PQ_IsEmpty(PQ))
            {
                printf("Queue sudah kosong\n");
            }
            else
            {
                PQ_Dequeue(&PQ, &P);

                printf("Wahana pengunjung: "); AK_TulisIsiTab(P_Wahana(P)); printf("\n");
                printf("Prioritas pengunjung (lebih kecil lebih tinggi): %d\n", P_Prio(P));
                printf("Kesabaran pengunjung: %d\n", P_Kesabaran(P));
            }

            break;
        case 3:

            (PQ_IsEmpty(PQ) ? printf("Queue kosong\n") : printf("Queue tidak kosong\n"));
            (PQ_IsFull(PQ) ? printf("Queue penuh\n") : printf("Queue tidak penuh\n")); 

            break;
        default:
            printf("Input tidak valid\n");
            break;
        }
        printf("\n");
    } while (true);   

    return 0;
}
