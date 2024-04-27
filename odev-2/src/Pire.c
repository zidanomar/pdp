#include "Pire.h"

Pire NewPire(int life, char* typeID) {
  Bocek super;
  Pire this;

  this = (Pire)malloc(sizeof(struct PIRE));

  this->super = NewBocek(life, typeID);

  this->DeletePire = &DeletePire;
  return this;
};

void DeletePire(const Pire this){
  if(this != NULL){
    this->super->DeleteBocek(this->super);
    free(this);
  }
};