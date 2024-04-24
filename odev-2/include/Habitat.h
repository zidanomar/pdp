#ifndef HABITAT_H
#define HABITAT_H

struct HABITAT{
  int rows;
  int cols;

  int** jungle;

  void (*PrintHabitat)(struct HABITAT*);
  void (*DeleteHabitat)(struct HABITAT*);
};

typedef struct HABITAT* Habitat;

Habitat NewHabitat(const char*);
void PrintHabitat(const Habitat);
void DeleteHabitat(const Habitat);

#endif