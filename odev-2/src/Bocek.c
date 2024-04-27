#include "Bocek.h"

// Bitki: B
// Böcek: C
// Sinek: S
// Pire: P
Bocek NewBocek(int life) {
  Canli super;
  Bocek this;

  this = (Bocek)malloc(sizeof(struct BOCEK));

  this->super = NewCanli(life);
  this->super->type = "C";

  this->DeleteBocek = &DeleteBocek;
  return this;
};
typedef struct BOCEK* Bocek;

void DeleteBocek(const Bocek this){
  if(this != NULL){
    this->super->DeleteCanli(this->super);
    free(this);
  }
};