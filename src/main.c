#include <stdio.h>
#include "adt.h"

int main()
{
    Kata NEW = MK_MakeKata("new", 3);
    Kata LOAD = MK_MakeKata("load", 4);
    Kata EXIT = MK_MakeKata("exit", 4);

    printf("Welcome to Willy Wangky's\n");
    printf("Commands:\n");
    printf("new - New game\n");
    printf("load - Load game\n");
    printf("exit - Exit game\n\n");

    MK_STARTKATAINPUT();
    while (!MK_EndKata)
    {
        if (MK_isKataSama(MK_CKata, NEW))
        {
            printf("New game\n");
        }
        else if (MK_isKataSama(MK_CKata, LOAD))
        {
            printf("Load game\n");
        }
        else if (MK_isKataSama(MK_CKata, EXIT))
        {
            printf("Thank you for playing!!!\n");
            break;
        }
        else
        {
            printf("Input tidak valid\n");
            MK_ADVKATAINPUT();
            continue;
        }
        printf("\n");

        MK_ADVKATAINPUT();
    }

    return 0;
}
