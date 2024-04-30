#include "Sinek.h"

Sinek NewSinek(int life, char *typeID)
{
  Bocek super;
  Sinek this;

  this = (Sinek)malloc(sizeof(struct SINEK));

  this->super = NewBocek(life, typeID);
  this->PrintSinek = &PrintSinek;
  this->KillSinek = &KillSinek;
  this->DeleteSinek = &DeleteSinek;
  return this;
};

void PrintSinek(const Sinek this)
{
  printf("%s", this->super->super->GetCanli(this->super->super));
};

void KillSinek(const Sinek this)
{
  this->super->super->KillCanli(this->super->super);
};

void DeleteSinek(const Sinek this)
{
  if (this != NULL)
  {
    this->super->DeleteBocek(this->super);
    free(this);
  }
};