#include "Habitat.h"
int main()
{
    Habitat h = NewHabitat();
    h->PrintHabitat(h);
    printf("\n");
    
    int rows = h->ROWS;
    int cols = h->COLS;

    int tryCount = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (col == cols - 1) {
                if (row == rows - 1) {
                    break;;
                } else {
                    tryCount++;
                    h->Clash(h, row + 1, 0);
                    printf("Try Count: %d\n", tryCount);
                    h->PrintHabitat(h);
                }
            } else {
                tryCount++;
                h->Clash(h, row, col + 1);
                printf("Try Count: %d\n", tryCount);
                h->PrintHabitat(h);
            }
        }
        printf("\n");
    }

    // h->PrintHabitat(h);
    // printf("Try Count: %d\n", tryCount);

    h->DeleteHabitat(h);
    
    return 0;

}