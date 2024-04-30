#ifndef SINEK_H
#define SINEK_H

#include "Bocek.h"

#include <stdio.h>

struct SINEK
{
  Bocek super;
  void (*PrintSinek)(struct SINEK *);
  void (*KillSinek)(struct SINEK *);
  void (*DeleteSinek)(struct SINEK *);
};
typedef struct SINEK *Sinek;

Sinek NewSinek(int, char *);
void PrintSinek(const Sinek);
void KillSinek(const Sinek);
void DeleteSinek(const Sinek);
#endif