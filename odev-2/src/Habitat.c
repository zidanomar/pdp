#include "Habitat.h"

int initialTiles[4][5] = {
    {10, 2, 5, 4, 7},
    {21, 6, 1, 25, 8},
    {11, 64, 33, 41, 47},
    {8, 1, 9, 5, 23}};

SpeciesUnion **generateTiles(int rows, int cols)
{
  // Allocate memory for the tiles array
  SpeciesUnion **tiles = (SpeciesUnion **)malloc(rows * sizeof(SpeciesUnion *));
  if (tiles == NULL)
  {
    return NULL; // Return NULL if memory allocation fails
  }

  // Allocate memory for each row of the tiles array
  for (int i = 0; i < rows; ++i)
  {
    tiles[i] = (SpeciesUnion *)malloc(cols * sizeof(SpeciesUnion));
    if (tiles[i] == NULL)
    {
      // Free memory for previously allocated rows if allocation fails for the current row
      for (int j = 0; j < i; j++)
      {
        free(tiles[j]);
      }
      free(tiles);
      return NULL; // Return NULL if memory allocation fails
    }
  }

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      char *id;
      if (initialTiles[i][j] <= 9)
      {
        id = "B";
        tiles[i][j].bitki = NewBitki(initialTiles[i][j], id);
        tiles[i][j].speciesID = 0;
      }
      else if (initialTiles[i][j] <= 20)
      {
        id = "C";
        tiles[i][j].bocek = NewBocek(initialTiles[i][j], id);
        tiles[i][j].speciesID = 1;
      }
      else if (initialTiles[i][j] <= 50)
      {
        id = "S";
        tiles[i][j].sinek = NewSinek(initialTiles[i][j], id);
        tiles[i][j].speciesID = 2;
      }
      else if (initialTiles[i][j] <= 99)
      {
        id = "P";
        tiles[i][j].pire = NewPire(initialTiles[i][j], id);
        tiles[i][j].speciesID = 3;
      }
    }
  }

  return tiles;
}


Habitat NewHabitat()
{
  Habitat this;

  this = (Habitat)malloc(sizeof(struct HABITAT));
  if (this == NULL)
  {
    return NULL;
  }

  int rows = 4;
  int cols = 5;
  this->ROWS = rows;
  this->COLS = cols;

  this->tiles = generateTiles(this->ROWS, this->COLS);

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
      switch (this->tiles[i][j].speciesID)
      {
      case 0:
        printf("%d ", this->tiles[i][j].speciesID);
        this->tiles[i][j].bitki->PrintHello();
        break;
      // case 1:
      //   printf("%c ", this->tiles[i][j].speciesID);
      //   break;
      // case 2:
      //   printf("%c ", this->tiles[i][j].speciesID);
      //   break;
      // case 3:
      //   printf("%c ", this->tiles[i][j].speciesID);
      //   break;
      default:
        break;
      }
    }
    printf("\n");
  }
};

void DeleteHabitat(const Habitat this)
{
  if (this != NULL)
  {
    for (int i = 0; i < this->ROWS; i++)
    {
      // todo: clean canli
      free(this->tiles[i]);
    }
    free(this->tiles);
    free(this);
  }
}
