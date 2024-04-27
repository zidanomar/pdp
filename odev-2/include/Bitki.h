#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"
#include <stdio.h>

struct BITKI{
    Canli super;

    void (*PrintHello)();
    void (*DeleteBitki)(struct BITKI*);
};
typedef struct BITKI* Bitki;

Bitki NewBitki(int, char*);
void PrintHello();
void DeleteBitki(const Bitki);


#endif