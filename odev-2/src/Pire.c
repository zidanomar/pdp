#include "Pire.h"

Pire NewPire(int life, char* typeID) {
  Bocek super;
  Pire this;

  this = (Pire)malloc(sizeof(struct PIRE));

  this->super = NewBocek(life, typeID);
  this->PrintPire = &PrintPire;
  this->DeletePire = &DeletePire;
  return this;
};

void PrintPire(const Pire this) {
  printf("%s", this->super->super->GetCanli(this->super->super));
};

void DeletePire(const Pire this){
  if(this != NULL){
    this->super->DeleteBocek(this->super);
    free(this);
  }
};