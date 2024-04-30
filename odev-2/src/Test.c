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
            if (col == cols - 1)
            {
                if (row == rows - 1)
                {
                    break;
                }
                else
                {
                    h->Clash(h, row + 1, 0);
                    h->PrintHabitat(h);
                }
            }
            else
            {
                h->Clash(h, row, col + 1);
                h->PrintHabitat(h);
            }
        }
    }
    h->PrintWinner(h);
    h->DeleteHabitat(h);

    return 0;
}