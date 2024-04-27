#ifndef SINEK_H
#define SINEK_H

#include "Bocek.h"

struct SINEK{
  Bocek super;
  void (*DeleteSinek)(struct SINEK*);
};
typedef struct SINEK* Sinek;

Sinek NewSinek(int, char*);
void DeleteSinek(const Sinek);
#endif