#ifndef CANLI_H
#define CANLI_H

#include "stdlib.h"

typedef enum Bool{false, true}boolean;

struct CANLI{
  int life;

  char* (*GetCanli)();
  void (*delete)(struct CANLI*);
};
typedef struct CANLI* Canli;

Canli NewCanli(int);
char* GetCanli(const Canli);
void DeleteCanli(const Canli);


#endif