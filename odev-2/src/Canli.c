#include "Canli.h"

Canli NewCanli(int life, char* typeID) {
  Canli this;
  this = (Canli)malloc(sizeof(struct CANLI));
  
  this->typeID = typeID;
  this->isAlive = true;
  this->life = life;

  this->GetLife = &GetLife;
  this->GetTypeID = &GetTypeID;
  this->DeleteCanli = &DeleteCanli;

  return this;
};

int GetLife(const Canli this) {
  return this->life;
};

char* GetTypeID(const Canli this) {
  return this->typeID;
};

void DeleteCanli(const Canli this){
  if(this != NULL){
    free(this);
  }
};