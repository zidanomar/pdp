#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

#include <stdlib.h>

struct BOCEK{
  Canli super;
  void (*DeleteBocek)(struct BOCEK*);
};
typedef struct BOCEK* Bocek;

Bocek NewBocek(int);
void DeleteBocek(const Bocek);

#endif