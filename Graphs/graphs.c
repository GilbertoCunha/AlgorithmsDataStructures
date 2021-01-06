#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

void GraphgraphL (GraphL g, int V) {
    FILE *f = fopen("graph.dot", "w");
    Edge p;

    fprintf (f, "digraph G {\n");
    fprintf (f, "\tlabelloc=\"t\";\n");
    fprintf (f, "\tlabel=\"Graph\";\n");
    for (int u=0; u<V; ++u) {
        fprintf (f, "\t%d [label=\"%d\"];\n", u, u);
    
        for (p=g[u]; p; p=p->next)
            fprintf (f, "\t%d->%d [label=\"%d\"];\n", u, p->dest, p->weight);
    }
    fprintf (f, "}");
    fclose (f);
    system ("dot -Kfdp -Tpng -Goverlap=false -Gsplines=true graph.dot > graph.png");
}

void graphMtoL (GraphM gm, GraphL gl, int V) {
    for (int i=0; i<V; ++i) {
        gl[i] = NULL;
        for (int j=0; j<V; ++j)
            if (gm[i][j] != NE) {
                Edge aux = malloc (sizeof (struct edge));
                aux->dest = j;
                aux->weight = gm[i][j];
                aux->next = gl[i];
                gl[i] = aux;
            }
    }
}

void graphLtoM (GraphL gl, GraphM gm, int V) {
    int i, j;
    Edge aux;
    for (i=0; i<V; ++i) {
        j = V-1;
        aux = gl[i];
        while (aux != NULL) {
            if (aux->dest == j) {
                gm[i][j] = aux->weight;
                aux = aux->next;
            }
            j--;
        }
    }
}

void ShowGraphM (GraphM g, int V) {
    printf ("GraphM:\n");
    for (int i=0; i<V; ++i) {
        for (int j=0; j<V; ++j)
            printf ("%d ", g[i][j]);
        printf ("\n");
    }
    printf ("\n");
}

void ShowGraphL (GraphL g, int V) {
    printf ("GraphL:\n");
    Edge aux;
    for (int i=0; i<V; ++i) {
        printf ("V %d: ", i);
        for (aux=g[i]; aux && aux->next; aux=aux->next)
            printf ("| V %d , W %d | -> ", aux->dest, aux->weight);
        if (aux != NULL) printf ("| V %d , W %d |", aux->dest, aux->weight);
        printf ("\n");
    } 
    printf ("\n");
}

void dfs_visit (GraphL g, int s, int color[]) {
    Edge p;

    color[s] = GRAY;

    for (p=g[s]; p; p=p->next)
        if (color[p->dest] == WHITE)
            dfs_visit (g, p->dest, color);

    color[s] = BLACK;
}

void dfs (GraphL g, int V) {
    int u, color[V];
    for (u=0; u<V; ++u) color[u] = WHITE;
    for (u=0; u<V; ++u)
        if (color[u] == WHITE)
            dfs_visit (g, u, color);
}