#ifndef PIRE_H
#define PIRE_H

#include "Bocek.h"

struct PIRE{
  Bocek super;
  void (*DeletePire)(struct PIRE*);
};
typedef struct PIRE* Pire;

Pire NewPire(int, char*);
void DeletePire(const Pire);


#endif