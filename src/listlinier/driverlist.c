#include "listlinier.h"
#include <stdio.h>


int main(){
    /* Inisialisasi list kosong*/
    List HistoryUpgradeWahana;
    LL_CreateEmpty(&HistoryUpgradeWahana);

    /* Membuat data wahana yg akan disimpan ke list */
    Wahana W;
    W_BaseId(W) = 0;
    W_WahanaId(W) = 0;
    W_Name(W) = MK_MakeKata("Halolintar",10);
    W_Type(W) = MK_MakeKata("Tipe 1",6);
    W_Area(W) = 1;
    W_Location(W) = MK_KataToPoint(MK_MakeKata("1,1",3));
    W_Desc(W) = MK_MakeKata("Ini Halilintar",14);
    W_Duration(W) = 15;
    W_Capacity(W) = 20;
    W_MoneyCost(W) = 5000;
    W_UseCount(W) = 0;
    W_Price(W) = 400;
    W_Penghasilan(W) = 0;
    W_TodayUseCount(W) = 0;
    W_TodayPenghasilan(W) = 0;
    W_IsBroken(W) = false;

    Wahana W1;
    W_BaseId(W1) = 0;
    W_WahanaId(W1) = 1;
    W_Name(W1) = MK_MakeKata("Halilintar",10);
    W_Type(W1) = MK_MakeKata("Tipe 1",6);
    W_Area(W1) = 1;
    W_Location(W1) = MK_KataToPoint(MK_MakeKata("1,1",3));
    W_Desc(W1) = MK_MakeKata("Ini Halilintar",14);
    W_Duration(W1) = 15;
    W_Capacity(W1) = 20;
    W_MoneyCost(W1) = 5000;
    W_UseCount(W1) = 0;
    W_Price(W1) = 400;
    W_Penghasilan(W1) = 0;
    W_TodayUseCount(W1) = 0;
    W_TodayPenghasilan(W1) = 0;
    W_IsBroken(W1) = false;

    /*Menambahkan W dan W1 pada elemen list dan menampilkan nama wahana yang sudah terdapat di dalam list*/
    LL_InsVFirst(&HistoryUpgradeWahana,W);
    LL_PrintInfoNamaWahana(HistoryUpgradeWahana);printf("\n");
    LL_InsVLast(&HistoryUpgradeWahana,W1);
    LL_PrintInfoNamaWahana(HistoryUpgradeWahana);printf("\n");


    return 0;
}

// gcc -o driverlist driverlist.c listlinier.c ../string_production/mesinkar.c ../string_production/mesinkata.c ../point/point.c -lm