#include <stdio.h>

#include "graph.h"
#include "player.h"

int main()
{
    Graph G;
    Player P;
    int input;
    CreateEmptyGraph(&G);
    address P1 = AlokasiNodeGraph("../../files/map1.txt");
    address P2 = AlokasiNodeGraph("../../files/map2.txt");
    address P3 = AlokasiNodeGraph("../../files/map3.txt");
    address P4 = AlokasiNodeGraph("../../files/map4.txt");
    InsertLastGraph(&G, P1);
    InsertLastGraph(&G, P2);
    InsertLastGraph(&G, P3);
    InsertLastGraph(&G, P4);
    setPlayer(GetMap(G, G_CurrentArea(G)), &P, 3, 3);

    printCurrentMap(G, P);

    char moveInput;
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
        move(&G, &P, moveCode);
        printf("\n");
        printCurrentMap(G, P);

    } while (true);


    // do
    // {
    //     printf("1. Input/Output\n");
    //     printf("2. Index\n");
    //     printf("3. Elemen\n");
    //     printf("4. Exit\n");
    //     printf("Pilihan: ");
    //     scanf("%d", &input);

    //     switch (input)
    //     {
    //     case 1:
    //         /* code */
    //         break;
        
    //     default:
    //         break;
    //     }
        


    // } while (input != 4);
    
    
    return 0;
}
