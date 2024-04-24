// #include "Bitki.h"
// #include "Bocek.h"
// #include "Canli.h"
#include "Habitat.h"
// #include "Pire.h"
// #include "Sinek.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int main() {
    Habitat habitat = NewHabitat("Veri.txt");
    if(habitat == NULL){
        fprintf(stderr, "Error creating habitat.\n");
        return 1;
    }
    habitat->PrintHabitat(habitat);
    habitat->DeleteHabitat(habitat);

    return 0;
}
