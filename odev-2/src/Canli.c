#include "Canli.h"

char* IdentifyCanli(int num) {
    if (num <= 9) {
        return "B";
    }
    else if (num <= 20) {
        return "C";
    }
    else if (num <= 50) {
        return "S";
    }
    else if (num <= 99) {
        return "P";
    }
    else {
        return NULL; 
    }
}


Canli NewCanli(int life) {
  Canli this;
  this = (Canli)malloc(sizeof(struct CANLI));
  this->life = life;
  this->GetCanli = &GetCanli;
  this->delete = &DeleteCanli;
};

char* GetCanli(const Canli this) {
  return IdentifyCanli(this->life);
};

void DeleteCanli(const Canli this){
  if(this != NULL){
    free(this);
  }
};