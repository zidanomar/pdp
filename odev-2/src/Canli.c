#include "Canli.h"

Canli NewCanli(int life) {
  Canli this;
  this = (Canli)malloc(sizeof(struct CANLI));
  
  this->isAlive = true;
  this->life = life;

  this->GetLife = &GetLife;
  this->GetType = &GetType;
  this->DeleteCanli = &DeleteCanli;

  return this;
};

int GetLife(const Canli this) {
  return this->life;
};

char* GetType(const Canli this) {
  return this->type;
};

void DeleteCanli(const Canli this){
  if(this != NULL){
    free(this);
  }
};