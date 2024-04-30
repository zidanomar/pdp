#include "Habitat.h"

int initialTiles[4][5] = {
    {10, 2, 5, 4, 7},
    {21, 6, 1, 25, 8},
    {11, 64, 33, 41, 47},
    {8, 1, 9, 5, 23}};

struct Tile **generateTiles(int rows, int cols)
{
  struct Tile **tiles = (struct Tile **)malloc(rows * sizeof(struct Tile *));
  for (int i = 0; i < rows; ++i)
  {
    tiles[i] = (struct Tile *)malloc(cols * sizeof(struct Tile));
  }

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      // Bitki: 1-9
      // Böcek: 10-20
      // Sinek: 21-50
      // Pire: 51-99
      if (initialTiles[i][j] <= 9)
      {
        tiles[i][j].type = TYPE_BITKI;
        tiles[i][j].data.bitki = NewBitki(initialTiles[i][j], "B");
      }
      else if (initialTiles[i][j] <= 20)
      {
        tiles[i][j].type = TYPE_BOCEK;
        tiles[i][j].data.bocek = NewBocek(initialTiles[i][j], "C");
      }
      else if (initialTiles[i][j] <= 50)
      {
        tiles[i][j].type = TYPE_SINEK;
        tiles[i][j].data.sinek = NewSinek(initialTiles[i][j], "S");
      }
      else if (initialTiles[i][j] <= 99)
      {
        tiles[i][j].type = TYPE_PIRE;
        tiles[i][j].data.pire = NewPire(initialTiles[i][j], "P");
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
  this->currSurvivor[0] = 0;
  this->currSurvivor[1] = 0;

  this->tiles = generateTiles(rows, cols);

  this->PrintHabitat = &PrintHabitat;
  this->Clash = &Clash;
  this->SetCurrSurvivor = &SetCurrSurvivor;
  this->PrintWinner = &PrintWinner;
  this->DeleteHabitat = &DeleteHabitat;
  return this;
}

void Clash(Habitat habitat, int nextRow, int nextCol)
{
  struct Tile tile1 = habitat->tiles[habitat->currSurvivor[0]][habitat->currSurvivor[1]];
  struct Tile tile2 = habitat->tiles[nextRow][nextCol];

  // Bitki → Pire w
  // Böcek → Bitki x
  // Sinek → Pire
  // Bitki → Sinek w
  // Sinek → Böcek
  // Böcek →Pire
  switch (tile1.type)
  {
  case TYPE_BITKI:
    switch (tile2.type)
    {
    case TYPE_BITKI:
      // get bigger life
      if (tile1.data.bitki->super->life > tile2.data.bitki->super->life || tile1.data.bitki->super->life == tile2.data.bitki->super->life)
      {
        // tile2.data.bitki->super->KillCanli(tile2.data.bitki->super);
        tile2.data.bitki->KillBitki(tile2.data.bitki);
      }
      else
      {
        // tile1.data.bitki->super->KillCanli(tile1.data.bitki->super);
        tile1.data.bitki->KillBitki(tile1.data.bitki);
        habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      }
      break;
    case TYPE_BOCEK:
      // bitki loses life
      // tile1.data.bitki->super->KillCanli(tile1.data.bitki->super);
      tile1.data.bitki->KillBitki(tile1.data.bitki);
      habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      break;
    case TYPE_SINEK:
      // bitki eats sinek
      // tile2.data.sinek->super->super->KillCanli(tile2.data.sinek->super->super);
      tile2.data.sinek->KillSinek(tile2.data.sinek);
      break;
    case TYPE_PIRE:
      // bitki eats pire
      // tile2.data.pire->super->super->KillCanli(tile2.data.pire->super->super);
      tile2.data.pire->KillPire(tile2.data.pire);
      break;
    default:
      break;
    }
    break;

  // Bitki → Pire
  // Böcek → Bitki w
  // Sinek → Pire
  // Bitki → Sinek
  // Sinek → Böcek x
  // Böcek →Pire w
  case TYPE_BOCEK:
    switch (tile2.type)
    {
    case TYPE_BITKI:
      // Böcek eats bitki
      // tile2.data.bitki->super->KillCanli(tile2.data.bitki->super);
      tile2.data.bitki->KillBitki(tile2.data.bitki);
      break;
    case TYPE_BOCEK:
      // get bigger life
      if (tile1.data.bocek->super->life > tile2.data.bocek->super->life || tile1.data.bocek->super->life == tile2.data.bocek->super->life)
      {
        tile2.data.bocek->super->KillCanli(tile2.data.bocek->super);
        tile2.data.bocek->KillBocek(tile2.data.bocek);
      }
      else
      {
        // tile1.data.bocek->super->KillCanli(tile1.data.bocek->super);
        tile1.data.bocek->KillBocek(tile1.data.bocek);
        habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      }
      break;
    case TYPE_SINEK:
      // Böcek loses life
      // tile1.data.bocek->super->KillCanli(tile1.data.bocek->super);
      tile1.data.bocek->KillBocek(tile1.data.bocek);
      habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      break;
    case TYPE_PIRE:
      // Böcek eats pire
      // tile2.data.pire->super->super->KillCanli(tile2.data.pire->super->super);
      tile2.data.pire->KillPire(tile2.data.pire);
      break;
    default:
      break;
    }
    break;

  // Bitki → Pire
  // Böcek → Bitki
  // Sinek → Pire w
  // Bitki → Sinek x
  // Sinek → Böcek w
  // Böcek →Pire
  case TYPE_SINEK:
    switch (tile2.type)
    {
    case TYPE_BITKI:
      // sinek loses life
      // tile1.data.sinek->super->super->KillCanli(tile1.data.sinek->super->super);
      tile1.data.sinek->KillSinek(tile1.data.sinek);
      habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      break;
    case TYPE_BOCEK:
      // sinek eats bocek
      // tile2.data.bocek->super->KillCanli(tile2.data.bocek->super);
      tile2.data.bocek->KillBocek(tile2.data.bocek);
      break;
    case TYPE_SINEK:
      // get bigger life
      if (tile1.data.sinek->super->super->life > tile2.data.sinek->super->super->life || tile1.data.sinek->super->super->life == tile2.data.sinek->super->super->life)
      {
        // tile2.data.sinek->super->super->KillCanli(tile2.data.sinek->super->super);
        tile2.data.sinek->KillSinek(tile2.data.sinek);
      }
      else
      {
        // tile1.data.sinek->super->super->KillCanli(tile1.data.sinek->super->super);
        tile1.data.sinek->KillSinek(tile1.data.sinek);
        habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      }
      break;
    case TYPE_PIRE:
      // sinek eats pire
      // tile2.data.pire->super->super->KillCanli(tile2.data.pire->super->super);
      tile2.data.pire->KillPire(tile2.data.pire);
      break;
    default:
      break;
    }
    break;

  // Bitki → Pire x
  // Böcek → Bitki
  // Sinek → Pire x
  // Bitki → Sinek
  // Sinek → Böcek
  // Böcek → Pire x
  case TYPE_PIRE:
    switch (tile2.type)
    {
    case TYPE_BITKI:
    case TYPE_BOCEK:
    case TYPE_SINEK:
      // pire loses life
      // tile1.data.pire->super->super->KillCanli(tile1.data.pire->super->super);
      tile1.data.pire->KillPire(tile1.data.pire);
      habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
    case TYPE_PIRE:
      if(tile1.data.pire->super->super->life > tile2.data.pire->super->super->life || tile1.data.pire->super->super->life == tile2.data.pire->super->super->life)
      {
        // tile2.data.pire->super->super->KillCanli(tile2.data.pire->super->super);
        tile2.data.pire->KillPire(tile2.data.pire);
      }
      else
      {
        // tile1.data.pire->super->super->KillCanli(tile1.data.pire->super->super);
        tile1.data.pire->KillPire(tile1.data.pire);
        habitat->SetCurrSurvivor(habitat, nextRow, nextCol);
      }
      break;
    default:
      break;
    }
    break;

  default:
    break;
  }
}

void SetCurrSurvivor(Habitat this, int x, int y)
{
  this->currSurvivor[0] = x;
  this->currSurvivor[1] = y;
}

void PrintHabitat(const Habitat this)
{
  for (int i = 0; i < this->ROWS; i++)
  {
    for (int j = 0; j < this->COLS; j++)
    {
      switch (this->tiles[i][j].type)
      {
      case TYPE_BITKI:
        this->tiles[i][j].data.bitki->PrintBitki(this->tiles[i][j].data.bitki);
        break;
      case TYPE_BOCEK:
        this->tiles[i][j].data.bocek->PrintBocek(this->tiles[i][j].data.bocek);
        break;
      case TYPE_SINEK:
        this->tiles[i][j].data.sinek->PrintSinek(this->tiles[i][j].data.sinek);
        break;
      case TYPE_PIRE:
        this->tiles[i][j].data.pire->PrintPire(this->tiles[i][j].data.pire);
        break;
      default:
        break;
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
};

#include <stdio.h>
#include <string.h>

void PrintWinner(const Habitat this)
{
  int row = this->currSurvivor[0];
  int col = this->currSurvivor[1];
  struct Tile winner = this->tiles[row][col];
  char *winnerID = malloc(2 * sizeof(char));
  switch (winner.type)
  {
  case TYPE_BITKI:
    winnerID = winner.data.bitki->super->typeID;
    break;
  case TYPE_BOCEK:
    winnerID = winner.data.bocek->super->typeID;
    break;
  case TYPE_SINEK:
    winnerID = winner.data.sinek->super->super->typeID;
    break;
  case TYPE_PIRE:
    winnerID = winner.data.pire->super->super->typeID;
    break;
  default:
    break;
  }

  printf("Kazanan: %s : (%d,%d)\n", winnerID, row, col);
}

void DeleteHabitat(const Habitat this)
{
  if (this != NULL)
  {
    for (int i = 0; i < this->ROWS; i++)
    {
      for (int j = 0; j < this->COLS; j++)
      {
        switch (this->tiles[i][j].type)
        {
        case TYPE_BITKI:
          this->tiles[i][j].data.bitki->DeleteBitki(this->tiles[i][j].data.bitki);
          break;
        case TYPE_BOCEK:
          this->tiles[i][j].data.bocek->DeleteBocek(this->tiles[i][j].data.bocek);
          break;
        case TYPE_SINEK:
          this->tiles[i][j].data.sinek->DeleteSinek(this->tiles[i][j].data.sinek);
          break;
        case TYPE_PIRE:
          this->tiles[i][j].data.pire->DeletePire(this->tiles[i][j].data.pire);
          break;
        default:
          break;
        }
      }
      free(this->tiles[i]);
    }
    free(this->tiles);
    free(this);
  }
}
