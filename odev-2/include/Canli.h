#ifndef CANLI_H
#define CANLI_H

#include "stdlib.h"

typedef enum Bool{false, true}boolean;

struct CANLI{
  boolean isAlive;
  
  int life;
  int (*GetLife)();

  char* type;
  char* (*GetType)();
  
  void (*DeleteCanli)(struct CANLI*);
};
typedef struct CANLI* Canli;

Canli NewCanli(int);
int GetLife(const Canli);
char* GetType(const Canli); // Görünüm fonksiyonu
void DeleteCanli(const Canli);

#endif