#ifndef CANLI_H
#define CANLI_H

#include <stdlib.h>

typedef enum Bool{false, true}boolean;

struct CANLI{
  char* typeID;
  int life;
  boolean isAlive;
  
  char* (*GetCanli)(struct CANLI*);
  void (*KillCanli)(struct CANLI*);
  void (*DeleteCanli)(struct CANLI*);
};
typedef struct CANLI* Canli;

Canli NewCanli(int, char*);
char* GetCanli(const Canli); // Görünüm fonksiyonu
void KillCanli(const Canli);
void DeleteCanli(const Canli);

#endif