#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main () {
    int v[5] = {1, 3, 4, 5, 2};
    LInt l = NULL;
    printf ("Array: ");
    for (int i=0; i<5; ++i) {
        printf ("%d ", v[i]);
        insertHead (&l, v[i]);
    }
    printf ("\n");
    ShowLInt (l);
    GraphLInt (l);

    printf ("\nRemoving element 5\n");
    removeLInt (&l, 5);
    ShowLInt (l);
}