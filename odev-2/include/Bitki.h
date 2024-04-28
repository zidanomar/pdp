#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"
#include <stdio.h>

struct BITKI{
    Canli super;

    void (*PrintBitki)(struct BITKI*);
    void (*DeleteBitki)(struct BITKI*);
};
typedef struct BITKI* Bitki;

Bitki NewBitki(int, char*);
void PrintBitki(const Bitki);
void DeleteBitki(const Bitki);


#endif