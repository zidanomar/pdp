// #include "Habitat.h"
// int main()
// {
//     Habitat h = NewHabitat();
//     h->PrintHabitat(h);
//     // h->DeleteHabitat(h);
//     return 0;

// }

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>

// Define the struct for type 1
struct INSECT {
    int health;
};
typedef struct INSECT *Insect;

Insect NewInsect(int health) {
    Insect this;
    this = (Insect)malloc(sizeof(struct INSECT));
    this->health = health;
    return this;
}

// Define the struct for type 2
struct PLANT {
    char *name;
    int leaf;
};

// Define the union struct
union UnionStruct {
    Insect insect;
    struct PLANT plant;
};

// Define enum to indicate type
enum Type {
    TYPE_INSECT,
    TYPE_PLANT
};

struct Tile {
    enum Type type;
    union UnionStruct data;
};

int main() {
    int row = 5;
    int col = 4;

    struct Tile **tiles = (struct Tile **)malloc(row * sizeof(struct Tile *));
    for (int i = 0; i < row; ++i) {
        tiles[i] = (struct Tile *)malloc(col * sizeof(struct Tile));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (j % 2 == 0)
            {
                tiles[i][j].type = TYPE_INSECT;
                tiles[i][j].data.insect = NewInsect(100);
            } else {
                tiles[i][j].type = TYPE_PLANT;
                tiles[i][j].data.plant.name = "Rose";
                tiles[i][j].data.plant.leaf = 10;
            }
            
        }
    }
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (tiles[i][j].type == TYPE_INSECT)
            {
                printf("Insect health: %d\n", tiles[i][j].data.insect->health);
            } else {
                printf("Plant name: %s, leaf: %d\n", tiles[i][j].data.plant.name, tiles[i][j].data.plant.leaf);
            }
        }
    }

    for (int i = 0; i < row; ++i) {
        free(tiles[i]);
    }

    free(tiles);

    return 0;
}
