#include "Habitat.h"

#include <stdio.h>

int main()
{
    Habitat h = NewHabitat();
    h->PrintHabitat(h);
    printf("===== STARTING FIGHT =====\n");
    h->Fight(h);

    h->DeleteHabitat(h);
    return 0;
}