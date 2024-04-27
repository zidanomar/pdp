#include "Bitki.h"

Bitki NewBitki(int life, char* typeID) {
  Canli super;
  Bitki this;

  this = (Bitki)malloc(sizeof(struct BITKI));

  this->super = NewCanli(life, typeID);

  this->PrintHello = &PrintHello;
  this->DeleteBitki = &DeleteBitki;
  
  return this;
};

void PrintHello() {
  printf("Hello from Bitki\n");
};

void DeleteBitki(const Bitki this) {
  if(this != NULL){
    this->super->DeleteCanli(this->super);
    free(this);
  }
};