#include <stdio.h>
#include <stdlib.h>
#include "AVLTrees.h"

int main () {
    AVLTree a = NULL;

    int i, v[10] = {1, 10, 14, 21, 7, 8, 15};
    for (i=0; i<10; ++i) insertAVL (&a, i, v[i]);

    if (isBSTree(a)==1) printf ("The tree is a search tree\n");
    else printf ("The tree is not a search tree\n");
    printf ("Height: %d\n", height(a));
    printf ("Tree: ");
    ShowAVLTree (a);
    GraphAVLTree (a);

    return 0;
}