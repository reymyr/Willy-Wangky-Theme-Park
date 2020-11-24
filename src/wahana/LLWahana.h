
#ifndef LLWAHANA_H
#define LLWAHANA_H

#include "wahana.h"
#include "../listlinier/listlinier.h"

#define MaxWahana 50

typedef struct{
    List Tab[MaxWahana];
    int Neff;
} ArrAddressBaseWahana;

void loadwahanahistory(char *filename, ArrAddressBaseWahana * A);

void PrintWahanaHistory(Wahana W, ArrAddressBaseWahana A);

#endif