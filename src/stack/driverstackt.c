#include "stackt.h"

/* gcc driverstackt.c stackt.c ../string_production/mesinkata.c ../string_production/mesinkar.c ../jam/jam.c ../point/point.c ../arrMaterial/arrMaterial.c -o driverStack -lm */

int main()
{
    Stack S;
    CreateEmptyStack(&S);
    int input;
    int money, time;
    S_infotype StackElmt;
    do
    {
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Total\n");
        printf("4. Full/Empty\n");
        printf("5. Exit\n\n");

        if (!IsEmptyStack(S))
        {
            printf("Top Stack: ");
            MK_printKata(S_Name(InfoTop(S)));
            printf("\n");
        }
        printf("Jumlah elemen Stack: %d\n\n", NbElmtStack(S));

        printf("Pilihan: ");
        scanf("%d", &input);
        if (input == 5)
        {
            break;
        }
        switch (input)
        {
        case 1:

            printf("Nama aksi: ");
            MK_STARTKATAINPUT();

            printf("Uang yang dibutuhkan: ");
            scanf("%d", &money);           

            printf("Waktu yang dibutuhkan (menit): ");
            scanf("%d", &time);

            Push(&S, CreateStackInfo(MK_CKata, MenitToJAM(time), money, MakePOINT(-1,-1)));

            break;
        case 2:
            if (IsEmptyStack(S))
            {
                printf("Stack kosong\n");
            }
            else
            {
                Pop(&S, &StackElmt);
                printf("Nama aksi: "); MK_printKata(S_Name(StackElmt)); printf("\n");
                printf("Uang yang dibutuhkan: %d\n", S_MoneyNeeded(StackElmt));        
                printf("Waktu yang dibutuhkan: "); TulisJamMenit(S_TimeNeeded(StackElmt)); printf("\n");
            }            
            break;
        case 3:
                printf("Total uang yang dibutuhkan: %d\n", TotalMoney(S));        
                printf("Total waktu yang dibutuhkan: "); TulisJamMenit(TotalTime(S)); printf("\n");
            break;
        case 4:

            (IsEmptyStack(S) ? printf("Stack kosong\n") : printf("Stack tidak kosong\n"));
            (IsFull(S) ? printf("Stack penuh\n") : printf("Stack tidak penuh\n"));

            break;
        default:
            printf("Input tidak valid\n");
            scanf("%d", &input);
            break;
        }
        printf("\n");
    } while (true);    
    return 0;
}
