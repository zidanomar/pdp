#include "Bitki.h"

Bitki NewBitki(int life, char* typeID) {
  Canli super;
  Bitki this;

  this = (Bitki)malloc(sizeof(struct BITKI));

  this->super = NewCanli(life, typeID);

  this->PrintBitki = &PrintBitki;
  this->DeleteBitki = &DeleteBitki;
  
  return this;
};

void PrintBitki(const Bitki this) {
  printf("%s", this->super->GetCanli(this->super));
};

void DeleteBitki(const Bitki this) {
  if(this != NULL){
    this->super->DeleteCanli(this->super);
    free(this);
  }
};