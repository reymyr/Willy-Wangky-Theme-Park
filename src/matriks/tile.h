#ifndef TILE_H
#define TILE_H

typedef struct { 
    char type;
    int id; /* berisi id wahana jika type='W', -1 jiak bukan */
} Tile;

/* SELEKTOR */
#define T_Type(T) (T).type
#define T_ID(T) (T).id

#endif
