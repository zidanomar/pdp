#ifndef HABITAT_H
#define HABITAT_H

#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"

#include <stdio.h>

 enum SpeciesType {
  TYPE_BITKI,
  TYPE_BOCEK,
  TYPE_SINEK,
  TYPE_PIRE,
};

 union SpeciesUnion {
  Bitki bitki;
  Bocek bocek;
  Sinek sinek;
  Pire pire;
};

struct Tile {
  enum SpeciesType type;
  union SpeciesUnion data;
};

struct HABITAT{
    struct Tile **tiles;
    int ROWS;
    int COLS;
    int currSurvivor[2];
    
    void (*PrintHabitat)(struct HABITAT*);
    void (*Clash)(struct HABITAT*, int, int, int, int);
    void (*SetCurrSurvivor)(struct HABITAT*, int, int);  
    void (*DeleteHabitat)(struct HABITAT*);
};
typedef struct HABITAT* Habitat;

Habitat NewHabitat();
void PrintHabitat(const Habitat);
void Clash(const Habitat, int, int, int, int);
void SetCurrSurvivor(const Habitat, int, int);
void DeleteHabitat(const Habitat);

#endif