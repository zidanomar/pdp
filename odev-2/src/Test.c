#include "Habitat.h"
int main()
{
    Habitat h = NewHabitat();
    h->PrintHabitat(h);
    h->DeleteHabitat(h);
    return 0;
}