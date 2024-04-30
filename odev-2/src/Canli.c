#include "Canli.h"

Canli NewCanli(int life, char *typeID)
{
  Canli this;

  this = (Canli)malloc(sizeof(struct CANLI));

  this->typeID = typeID;
  this->isAlive = true;
  this->life = life;
  this->GetCanli = &GetCanli;
  this->KillCanli = &KillCanli;
  this->DeleteCanli = &DeleteCanli;

  return this;
};

char *GetCanli(const Canli this)
{
  if (this->isAlive)
  {
    return this->typeID;
  }
  else
  {
    char *dead = malloc(sizeof(char) * 2);
    dead = "X";
    return dead;
  }
};

void KillCanli(const Canli this)
{
  this->isAlive = false;
};

void DeleteCanli(const Canli this)
{
  if (this != NULL)
  {
    free(this);
  }
};