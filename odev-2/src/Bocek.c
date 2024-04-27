#include "Bocek.h"

Bocek NewBocek(int life, char* typeID) {
  Canli super;
  Bocek this;

  this = (Bocek)malloc(sizeof(struct BOCEK));

  this->super = NewCanli(life, typeID);

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