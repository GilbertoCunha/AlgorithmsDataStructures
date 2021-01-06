#include <stdio.h>
#include <stdlib.h>
#include "heaps.h"

int main () {
    Heap h;
    initHeap(&h, 5);

    int v[10] = {10, -2, 4, 8, 3, -5, 7, 9, 0};
    printf ("Input array: ");
    for (int i=0; i<10; ++i) {
        printf ("%d ", v[i]);
        insertHeap(&h, v[i]);
    }
    printf ("\n");
    ShowHeap (h);
    GraphHeap (h);
    
    int minimum;
    extractMin (&h, &minimum);
    printf ("The minimum of the heap was %d\n", minimum);
    ShowHeap (h);

    if (minHeapOK (h)) printf ("The resulting array is a Heap\n");
    else printf ("The resulting array is not a heap\n");

    return 0;
}