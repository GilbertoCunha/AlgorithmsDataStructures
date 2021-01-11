#include "hash.h"

int main () {
    HashT h;
    initHash (&h, 0.8);
    insertHash (&h, "Gilli", 20);
    insertHash (&h, "Marta", 21);
    insertHash (&h, "Mauro", 420);
    
    int g, m;
    ShowHash (h);
    if (searchHash (h, "Marta", &m) == 1) printf ("Marta has value %d\n", m);
    if (removeHash (&h, "Marta", &g) == 1) printf ("Marta had value %d\n", g);
    if (searchHash (h, "Gilli", &g) == 1) printf ("Gilli has value %d\n", g);
    if (searchHash (h, "Mauro", &m) == 1) printf ("Mauro has value %d\n", m);

    return 0;
}