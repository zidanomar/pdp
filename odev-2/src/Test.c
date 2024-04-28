#include "Habitat.h"
int main()
{
    Habitat h = NewHabitat();
    h->PrintHabitat(h);
    printf("\n");
    
    int rows = h->ROWS;
    int cols = h->COLS;

    for (int row = 0; row < rows; row++)
    {
        for (int col = 0; col < cols; col++)
        {
            h->Clash(h, row, col, row, col+1);
            h->PrintHabitat(h);
        }
    }

    h->DeleteHabitat(h);
    
    return 0;

}