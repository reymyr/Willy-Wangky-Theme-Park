#include <stdio.h>

#include "graph.h"
#include "player.h"

/* gcc driverGraph.c graph.c ../point/point.c ../matriks/matriks.c ../string_production/mesinkata.c ../string_production/mesinkar.c -o driverG -lm */

int main()
{
    Graph G;
    Player P;
    int input;
    CreateEmptyGraph(&G);
    Gaddress P1 = AlokasiNodeGraph("../../files/map1.txt");
    Gaddress P2 = AlokasiNodeGraph("../../files/map2.txt");
    Gaddress P3 = AlokasiNodeGraph("../../files/map3.txt");
    Gaddress P4 = AlokasiNodeGraph("../../files/map4.txt");
    InsertLastGraph(&G, P1);
    InsertLastGraph(&G, P2);
    InsertLastGraph(&G, P3);
    InsertLastGraph(&G, P4);
    setPlayer(GetMap(G, G_CurrentArea(G)), &P, 3, 3);

    printCurrentMap(G, P);

    char moveInput;
    int status;
    int moveCode = -1;
    do
    {
        do
        {
            scanf("%c", &moveInput);
        } while ((moveInput != 'w') && (moveInput != 'a') && (moveInput != 's') && (moveInput != 'd'));
        
        switch (moveInput)
        {
        case 'w':
            moveCode = 0;
            break;
        case 'd':
            moveCode = 1;
            break;
        case 's':
            moveCode = 2;
            break;
        case 'a':
            moveCode = 3;
            break;        
        default:
            break;
        }
        move(&G, &P, moveCode, &status);
        printf("\n");
        printCurrentMap(G, P);

    } while (true);
    return 0;
}
