#include "Sinek.h"

Sinek NewSinek(int life, char* typeID) {
  Bocek super;
  Sinek this;

  this = (Sinek)malloc(sizeof(struct SINEK));

  this->super = NewBocek(life, typeID);

  this->DeleteSinek = &DeleteSinek;
  return this;
};

void DeleteSinek(const Sinek this){
  if(this != NULL){
    this->super->DeleteBocek(this->super);
    free(this);
  }
};