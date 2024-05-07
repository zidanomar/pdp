#include "Habitat.h"

#include <time.h>

int main()
{
    double time_taken;
    clock_t t1;
    Habitat h = NewHabitat();

    printf("\nCurrent Habitat:\n");

    h->PrintHabitat(h);

    printf("Press any key to continue...\n");
    getchar();

    t1 = clock();
    h->Fight(h);
    t1 = clock() - t1;

    h->DeleteHabitat(h);

    printf("Time taken: %f\n",
           ((double)t1) / CLOCKS_PER_SEC);

    return 0;
}