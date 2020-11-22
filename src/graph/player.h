#ifndef PLAYER_H
#define PLAYER_H

#include "../point/point.h"
#include "../string_production/mesinkata.h"
#include "../arrMaterial/arrMaterial.h"
#include "../matriks/tile.h"

typedef struct { 
    Kata nama;
    int money;
    TabMaterial materials;
	POINT pos;
    Tile surround[4];
} Player;

/* SELEKTOR */
#define Nama(P) (P).nama
#define Money(P) (P).money
#define Materials(P) (P).materials
#define Pos(P) (P).pos
#define Surround(P) (P).surround

#endif