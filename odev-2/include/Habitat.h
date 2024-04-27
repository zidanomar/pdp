#ifndef HABITAT_H
#define HABITAT_H

#include "Bocek.h"
#include "Bitki.h"

typedef union {
  Bocek bocek;
  Bitki bitki;
  int type;
} species_t;

struct HABITAT{
    species_t** tiles;
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