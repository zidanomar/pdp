#include "Habitat.h"
#include "Bocek.h"

#include <stdio.h>
#include <stdlib.h>

int initialTiles[4][5] = {
    {10, 2, 5, 4, 7},
    {21, 6, 1, 25, 8},
    {11, 64, 33, 41, 47},
    {8, 1, 9, 5, 23}};

Habitat NewHabitat()
{
  Habitat this;

  this = (Habitat)malloc(sizeof(struct HABITAT));
  if (this == NULL) {
    return NULL;
  }

  this -> ROWS = 4;
  this -> COLS = 5;

  this->tiles = (species_t **)malloc(this->ROWS * sizeof(species_t *));
  if (this->tiles == NULL) {
    free(this);
    return NULL;
  }
  for (int i = 0; i < this->ROWS; ++i)
  {
    this->tiles[i] = (species_t *)malloc(this->COLS * sizeof(species_t));
    if (this->tiles[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(this->tiles[j]);
      }
      free(this->tiles);
      free(this);
      return NULL;
    }
  }

  for (int i = 0; i < this->ROWS; ++i)
  {
    for (int j = 0; j < this->COLS; ++j)
    {
      if(initialTiles[i][j] % 2 == 0){
        this->tiles[i][j].type = 0;
        this->tiles[i][j].bocek = NewBocek(initialTiles[i][j]);
      } else {
        this->tiles[i][j].type = 1;
        this->tiles[i][j].bitki = NewBitki(initialTiles[i][j]);
      }
    }
  }

  this->PrintHabitat = &PrintHabitat;
  this->DeleteHabitat = &DeleteHabitat;
  return this;
}

void PrintHabitat(const Habitat this)
{
  for (int i = 0; i < this->ROWS; i++)
  {
    for (int j = 0; j < this->COLS; j++)
    {
      if(this->tiles[i][j].type == 0){
        printf("Bocek");
        printf(" %d ", this->tiles[i][j].bocek->GetLife(this->tiles[i][j].bocek));
        printf(" %s ", this->tiles[i][j].bocek->super->type);

      } else {
        printf("Bitki");
        printf(" %d ", this->tiles[i][j].bitki->GetLife(this->tiles[i][j].bitki));
        printf(" %s ", this->tiles[i][j].bitki->super->type);
      }
    }
    printf("\n");
  }
};

void DeleteHabitat(const Habitat this) {
  printf("Deleting habitat\n");
    for (int i = 0; i < this->ROWS; ++i) {
        for (int j = 0; j < this->COLS; j++) {
            if (this->tiles[i][j].type == 0) {
                this->tiles[i][j].bocek->DeleteBocek(this->tiles[i][j].bocek);
            } else {
                this->tiles[i][j].bitki->DeleteBitki(this->tiles[i][j].bitki);
            }
        }
        free(this->tiles[i]);
    }
    free(this->tiles);

    free(this);
    printf("Habitat deleted\n");
}
