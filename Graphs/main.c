#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

int main () {
    // Create matrix graph
    GraphM gm1 = {
        {0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 1, 0, 0},
    };
    GraphL gl1; 
    graphMtoL (gm1, gl1, 9);

    // Prim algorithm
    GraphM gm2 = {
        {0, 2, 5},
        {2, 0, 2},
        {5, 2, 0}
    };
    GraphL gl2;
    graphMtoL (gm2, gl2, 3);
    int MST[3]; 
    PrimMST (gl2, 3, 0, MST);
    printf ("-> PRIM:\nMST: ");
    for (int i=0; i<3; ++i) printf ("%d->%d ", i, MST[i]);
    printf ("\n\n");

    // Djikstra'a algorithm
    int dist[9], parent[9];
    printf ("-> DJIKSTRA:\n");
    singleDjikstra (gl1, 9, 0, dist, parent);
    printf ("Parents: ");
    for (int i=0; i<9; ++i) printf ("%d ", parent[i]);
    printf ("\nDistances: ");
    for (int i=0; i<9; ++i) printf ("%d ", dist[i]);
    printf ("\n\n");
    GraphgraphL (gl1, 9);

    // Warshall algorithm
    GraphM r;
    printf ("-> WARSHALL:\n");
    Warshall (gm1, r, 9);
    ShowGraphM (r, 9);

    // dynDistances algorithm
    // dynDistances (gm1, r, 9);
    // ShowGraphM (r, 9);

    return 0;
}