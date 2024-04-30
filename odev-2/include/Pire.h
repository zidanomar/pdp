#ifndef PIRE_H
#define PIRE_H

#include "Bocek.h"

#include <stdio.h>

struct PIRE
{
  Bocek super;
  void (*PrintPire)(struct PIRE *);
  void (*KillPire)(struct PIRE *);
  void (*DeletePire)(struct PIRE *);
};
typedef struct PIRE *Pire;

Pire NewPire(int, char *);
void PrintPire(const Pire);
void KillPire(const Pire);
void DeletePire(const Pire);

#endif