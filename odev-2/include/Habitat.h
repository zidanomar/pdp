#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"

#include <stdio.h>

typedef union {
  Bitki bitki;
  Bocek bocek;
  Sinek sinek;
  Pire pire;
  int speciesID;
} SpeciesUnion;

struct HABITAT{
    SpeciesUnion **tiles;
    int ROWS;
    int COLS;
    
    void (*PrintHabitat)(struct HABITAT*);  
    void (*DeleteHabitat)(struct HABITAT*);
};
typedef struct HABITAT* Habitat;

Habitat NewHabitat();
void PrintHabitat(const Habitat);
void DeleteHabitat(const Habitat);

#endif