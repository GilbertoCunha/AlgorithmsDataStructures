#include "arrays.h"

int main () {
    int v[10] = {14, 10, -4, 21, 17, 6, 32, 0, -21, 10};
    ShowArray (v, 10);
    // mergesort (v, 10);
    bubblesort (v, 10);
    printf ("Bubblesort ");
    ShowArray (v, 10);
}