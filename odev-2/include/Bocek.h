#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

struct BOCEK{
  Canli super;
  void (*DeleteBocek)(struct BOCEK*);
};
typedef struct BOCEK* Bocek;

Bocek NewBocek(int, char*);
void DeleteBocek(const Bocek);

#endif