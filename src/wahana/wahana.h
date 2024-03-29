#ifndef WAHANA_H
#define WAHANA_H

#include "../string_production/mesinkata.h"
#include "../point/point.h"
#include "../arrMaterial/arrMaterial.h"

#define IdxMax 50   // indeks maksimum array
#define IdxMin 0    // indeks minimum array
#define IdxUndef -1 // indeks tak terdefinisi

typedef int IdxType;

typedef struct{ 
    int baseId;
    int id;
    Kata name;
    Kata type;
    int harga;
    int area;
    POINT lokasi;
    Kata deskripsi;
    int kapasitas;
    int durasi;
    int moneyCost;
    TabMaterial materialCost;
    int useCount;
    int totalPenghasilan;
    int todayUseCount;
    int todayPenghasilan;
    boolean isBroken;
} Wahana;

/* SELEKTOR */
/* Misal W adalah variabel bertipe Wahana */
#define W_BaseId(W) (W).baseId
#define W_WahanaId(W) (W).id
#define W_Name(W) (W).name
#define W_Type(W) (W).type
#define W_Price(W) (W).harga
#define W_Area(W) (W).area
#define W_Location(W) (W).lokasi
#define W_Desc(W) (W).deskripsi
#define W_Capacity(W) (W).kapasitas
#define W_Duration(W) (W).durasi
#define W_MoneyCost(W) (W).moneyCost
#define W_MaterialCost(W) (W).materialCost
#define W_UseCount(W) (W).useCount
#define W_Penghasilan(W) (W).totalPenghasilan
#define W_TodayUseCount(W) (W).todayUseCount
#define W_TodayPenghasilan(W) (W).todayPenghasilan
#define W_IsBroken(W) (W).isBroken


#endif