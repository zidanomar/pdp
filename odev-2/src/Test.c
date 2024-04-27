#include "Habitat.h"
#include "Bitki.h"
int main()
{
    Bitki b = NewBitki(1, "Bitki");
    b->PrintHello();
    b->DeleteBitki(b);
    // Habitat h = NewHabitat();
    // h->PrintHabitat(h);
    // h->DeleteHabitat(h);
    return 0;

}

// #include <stdio.h>

// // Define the struct for type 1
// struct Type1 {
//     int value1;
// };

// // Define the struct for type 2
// struct Type2 {
//     float value2;
// };

// // Define the union struct
// union UnionStruct {
//     struct Type1 type1;
//     struct Type2 type2;
//     char flag;
// };

// int main() {
//     int rows, cols = 5;
//     // create a 2D array of union structs with malloc
//     union UnionStruct **tiles;
//     tiles = (union UnionStruct **)malloc(rows * sizeof(union UnionStruct*));
//     if (tiles == NULL) {
//         free(tiles);
//         return NULL;
//     }
//     for (int i = 0; i < rows; ++i)
//     {
//         tiles[i] = (union UnionStruct *)malloc(cols * sizeof(union UnionStruct*));
//         if (tiles[i] == NULL) {
//             for (int j = 0; j < i; j++) {
//                 free(tiles[j]);
//             }
//             free(tiles);
//             free(tiles);
//             return NULL;
//         }
//     }

//     // Initialize the union structs with values and flags
//     for (int i = 0; i < rows; ++i)
//     {
//         for (int j = 0; j < cols; ++j)
//         {
//             if (i % 2 == 0) {
//                 tiles[i][j].type1.value1 = 10;
//                 tiles[i][j].flag = 'A';
//             }
//             else {
//                 tiles[i][j].type2.value2 = 3.14;
//                 tiles[i][j].flag = 'B';
//             }
//         }
//     }

//     // Print different output based on the flag inside the union struct
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < cols; j++) {
//             printf("Flag: %c\n", tiles[i][j].flag);
//             switch (tiles[i][j].flag)
//             {
//             case 'A':
//                 printf("Value a: %d\n", tiles[i][j].type1.value1);
//                 break;
//             case 'B':
//                 printf("Value b: %f\n", tiles[i][j].type2.value2);
//                 break;
//             default:
//                 break;
//             }
//         }
//     }

//     // clear the memory
//     for (int i = 0; i < rows; ++i)
//     {
//         free(tiles[i]);
//     }

//     free(tiles);

//     return 0;
// }
