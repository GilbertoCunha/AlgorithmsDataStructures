#include "hash.h"

int main () {
    HashT h;
    initHash (&h, 0.8);
    printf ("%f\n", h.lf);
    insertHash (&h, "Gilli", 20);
    insertHash (&h, "Marta", 21);
    insertHash (&h, "Mauro", 420);
    insertHash (&h, "Vic", 20);
    insertHash (&h, "Drumás", 21);
    insertHash (&h, "INEM", 420);
    ShowHash (h);
    
    int g;
    printf ("Searching and removing elements:\n");
    if (searchHash (h, "Marta", &g) == 1) printf ("-> Marta has value %d\n", g);
    if (removeHash (&h, "Marta", &g) == 1) printf ("-> Marta had value %d\n", g);
    if (searchHash (h, "Gilli", &g) == 1) printf ("-> Gilli has value %d\n", g);
    if (removeHash (&h, "Mauro", &g) == 1) printf ("-> Mauro had value %d\n", g);
    if (searchHash (h, "Vic", &g) == 1) printf ("-> Vic has value %d\n", g);
    if (searchHash (h, "Drumás", &g) == 1) printf ("-> Drumás has value %d\n", g);
    if (removeHash (&h, "INEM", &g) == 1) printf ("-> INEM had value %d\n", g);
    printf ("\n");
    ShowHash (h);

    return 0;
}