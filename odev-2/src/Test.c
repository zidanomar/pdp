#include "Bitki.h"
#include "Bocek.h"
#include "Canli.h"
#include "Habitat.h"
#include "Pire.h"
#include "Sinek.h"

#include "stdio.h"

int main() {
  Canli canli = NewCanli(10);
  printf("Canli: %s\n", canli->GetCanli(canli));
  DeleteCanli(canli);

  return 0;
}