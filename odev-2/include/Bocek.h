#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

#include <stdio.h>

struct BOCEK
{
  Canli super;
  void (*PrintBocek)(struct BOCEK *);
  void (*KillBocek)(struct BOCEK *);
  void (*DeleteBocek)(struct BOCEK *);
};
typedef struct BOCEK *Bocek;

Bocek NewBocek(int, char *);
void PrintBocek(const Bocek);
void KillBocek(const Bocek);
void DeleteBocek(const Bocek);

#endif