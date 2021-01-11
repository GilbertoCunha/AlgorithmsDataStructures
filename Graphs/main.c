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
    ShowGraphM (gm1, 9);

    // Convert matrix graph to adj list graph
    GraphL gl1; 
    graphMtoL (gm1, gl1, 9);
    // GraphgraphL (gl1, 9);
    dfs (gl1, 9);
    bfs (gl1, 9);

    // Convert adj list graph back to matrix graph
    graphLtoM (gl1, gm1, 9);
    ShowGraphM (gm1, 9);
    GraphgraphM (gm1, 9);

    // Prim algorithm
    GraphM gm2 = {
        {0, 2, 5},
        {2, 0, 2},
        {5, 2, 0}
    };
    GraphL gl2;
    graphMtoL (gm2, gl2, 3);
    ShowGraphL (gl2, 3);
    int MST[3]; 
    PrimMST (gl2, 3, 0, MST);
    printf ("MST: ");
    for (int i=0; i<3; ++i) printf ("%d->%d ", i, MST[i]);
    printf ("\n");

    // Warshall algorithm
    GraphM r;
    Warshall (gm1, r, 9);
    ShowGraphM (r, 9);

    // dynDistances algorithm
    dynDistances (gm1, r, 9);
    ShowGraphM (r, 9);

    return 0;
}