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
    ShowGraphL (gl1, 9);
    // GraphgraphL (gl1, 9);

    // Convert adj list graph back to matrix graph
    graphLtoM (gl1, gm1, 9);
    ShowGraphM (gm1, 9);
    GraphgraphM (gm1, 9);

    return 0;
}