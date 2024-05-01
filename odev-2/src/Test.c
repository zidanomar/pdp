#include "Habitat.h"

#include <stdio.h>

int main()
{
    Habitat h = NewHabitat();

    printf("\nCurrent Habitat:\n");
    h->PrintHabitat(h);
    // wait until user presses any key
    printf("Press any key to continue...\n");
    getchar();

    h->Fight(h);

    h->DeleteHabitat(h);
    return 0;
}