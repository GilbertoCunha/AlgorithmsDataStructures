#include <stdio.h>
#include <stdlib.h>
#include "btrees.h"

int main () {
    BTree a = NULL;

    for (int i=-13; i<10; ++i) insertBTree (&a, 10*(i^2)-1);
    int r = remBTree (&a, -1);

    if (r) printf ("Integer -1 removed from tree\n");
    else printf ("Integer -1 not removed from tree\n");

    ShowBTree (a);
    GraphBTree (a);

    return 0;
}