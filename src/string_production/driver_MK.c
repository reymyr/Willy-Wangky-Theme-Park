#include <stdio.h>
#include "../boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include "../point/point.h"

/* How to compile:*/
/* gcc driver_MK.c mesinkata.c mesinkar.c ../point/point.c -o test -lm */

int input;
boolean flag_start;

int main(){
    printf("From where you want to input,Sir?\n");
    printf("1. Keyboard\n");
    printf("2. File\n");
    printf("(1-2)?: ");
    scanf("%d",&input);
    flag_start = false;
    if(input==1){
        MK_EndKata = false;
        printf("Masukkan input: ");
        MK_STARTKATAINPUT();
        printf("Kata yang baru saja anda input adalah: "); MK_printKata(MK_CKata);
    }
    else{
        MK_EndKata = false;
        printf("The file we referring to is test_text.txt\n");
        printf("It's on the same directory as this driver\n\n");
        while(true){
            printf("What do you want to do?\n");
            printf("1. START KATA\n");
            printf("2. ADV_KATA\n");
            printf("3. printKata\n");
            printf("4. Exit\n");
            printf("(1-4)?: ");
            scanf("%d",&input);
            if(input==4){
                break;
            }
            else if(MK_EndKata==true){
                printf("The file is on the end and now it's closed\n");
            }
            else if(input==1){
                if(flag_start){
                    printf("The file is being read now\n");
                }
                else{
                    printf("Loading File...\n");
                    MK_STARTKATA("test_text.txt");
                    printf("Mesin Kata is now ready to use\n");
                    flag_start = true;
                }
            }
            else if(input==2){
                if(flag_start){
                    MK_ADVKATA();
                    printf("Advancing...\n");
                }
                else{
                    printf("Mesin Kata is not started yet\n");
                }
            }
            else if(input==3){
                if(flag_start){
                    MK_printKata(MK_CKata);
                }
                else{
                    printf("Mesin Kata is not started yet.\n");
                }
            }
            else{
                printf("your input is invalid\n");
            }
        }
    }
}