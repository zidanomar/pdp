#include "Bitki.h"

// Bitki: B
// Böcek: C
// Sinek: S
// Pire: P

Bitki NewBitki(int life) {
  Canli super;
  Bitki this;

  this = (Bitki)malloc(sizeof(struct BITKI));

  this->super = NewCanli(life);
  this->super->type = "B";

  this->DeleteBitki = &DeleteBitki;
  
  return this;
};

void DeleteBitki(const Bitki this) {
  if(this != NULL){
    this->super->DeleteCanli(this->super);
    free(this);
  }
};