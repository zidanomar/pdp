#include "Habitat.h"

#define INITIAL_SIZE 100

struct Tile **generateTiles(Habitat this)
{
  FILE *file = fopen("Veri.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    exit(1);
  }

  int rows = 0;
  int capacity = INITIAL_SIZE;
  struct Tile **tiles = malloc(capacity * sizeof(struct Tile *));
  int *cols = malloc(capacity * sizeof(int));

  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, file) != -1)
  {
    if (rows >= capacity)
    {
      capacity *= 2;
      tiles = realloc(tiles, capacity * sizeof(struct Tile *));
      cols = realloc(cols, capacity * sizeof(int));
      if (tiles == NULL || cols == NULL)
      {
        printf("Memory allocation failed.\n");
        exit(1);
      }
    }

    int tiles_count = 0;
    struct Tile *tile = malloc(INITIAL_SIZE * sizeof(struct Tile));

    char *token = strtok(line, " ");
    while (token != NULL)
    {
      if (tiles_count >= INITIAL_SIZE)
      {
        tile = realloc(tile, 2 * INITIAL_SIZE * sizeof(struct Tile));
        if (tile == NULL)
        {
          printf("Memory allocation failed.\n");
          exit(1);
        }
      }

      int val = atoi(token);
      struct Tile new_tile;

      if (val <= 9)
      {
        new_tile.type = TYPE_BITKI;
        new_tile.data.bitki = NewBitki(val, "B");
      }
      else if (val <= 20)
      {
        new_tile.type = TYPE_BOCEK;
        new_tile.data.bocek = NewBocek(val, "C");
      }
      else if (val <= 50)
      {
        new_tile.type = TYPE_SINEK;
        new_tile.data.sinek = NewSinek(val, "S");
      }
      else
      {
        new_tile.type = TYPE_PIRE;
        new_tile.data.pire = NewPire(val, "P");
      }

      tile[tiles_count++] = new_tile;
      token = strtok(NULL, " ");
    }

    tiles[rows] = tile;
    cols[rows++] = tiles_count;
  }

  fclose(file);
  free(line);

  this->ROWS = rows;
  this->COL_IDX = cols;

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

  this->currSurvivor[0] = 0;
  this->currSurvivor[1] = 0;

  char *filename = "Veri.txt";
  this->tiles = generateTiles(this);

  this->PrintHabitat = &PrintHabitat;
  this->Clash = &Clash;
  this->SetCurrSurvivor = &SetCurrSurvivor;
  this->PrintWinner = &PrintWinner;
  this->Fight = &Fight;
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
      if (tile1.data.pire->super->super->life > tile2.data.pire->super->super->life || tile1.data.pire->super->super->life == tile2.data.pire->super->super->life)
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
    for (int j = 0; j < this->COL_IDX[i]; j++)
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

// Aktif olarak linux kullandığım için
// windows için cls ekledim
#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void clearScreen()
{
  system(CLEAR_COMMAND);
}

void Fight(const Habitat this)
{
  for (int row = 0; row < this->ROWS; row++)
  {
    for (int col = 0; col < this->COL_IDX[row]; col++)
    {
      if (col == this->COL_IDX[row] - 1)
      {
        if (row == this->ROWS - 1)
        {
          break;
        }
        else
        {
          this->Clash(this, row + 1, 0);
          clearScreen();
          this->PrintHabitat(this);
        }
      }
      else
      {
        this->Clash(this, row, col + 1);
        clearScreen();
        this->PrintHabitat(this);
      }
    }
  }
  this->PrintWinner(this);
}

void DeleteHabitat(const Habitat this)
{
  if (this != NULL)
  {
    for (int i = 0; i < this->ROWS; i++)
    {
      for (int j = 0; j < this->COL_IDX[i]; j++)
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
    free(this->COL_IDX);
    free(this);
  }
}
