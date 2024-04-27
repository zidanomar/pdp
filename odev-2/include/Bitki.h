#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"
#include <stdlib.h>

struct BITKI{
    Canli super;

    void (*DeleteBitki)(struct BITKI*);
};
typedef struct BITKI* Bitki;

Bitki NewBitki(int);
void DeleteBitki(const Bitki);


#endif