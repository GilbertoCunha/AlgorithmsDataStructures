#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

int color[MAX];

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

void GraphgraphM (GraphM g, int V) {
    FILE *f = fopen("graph.dot", "w");

    fprintf (f, "digraph G {\n");
    fprintf (f, "\tlabelloc=\"t\";\n");
    fprintf (f, "\tlabel=\"Graph\";\n");
    for (int u=0; u<V; ++u) {
        fprintf (f, "\t%d [label=\"%d\"];\n", u, u);
        for (int v=0; v<V; ++v) 
            if (g[u][v] != NE)
                fprintf (f, "\t%d->%d [label=\"%d\"];\n", u, v, g[u][v]);
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

void dfs_visit (GraphL g, int s) {
    Edge p;

    color[s] = GRAY;

    for (p=g[s]; p; p=p->next)
        if (color[p->dest] == WHITE)
            dfs_visit (g, p->dest);

    color[s] = BLACK;
}

void dfs (GraphL g, int V) {
    int u;
    printf ("Depth Traversal:\n");
    for (u=0; u<V; ++u) color[u] = WHITE;
    for (u=0; u<V; ++u)
        if (color[u] == WHITE)
            dfs_visit (g, u);
    for (u=0; u<V; ++u) printf ("V: %d | C: %d\n", u, color[u]);
    printf ("\n");
}

void bfs_visit (GraphL g, int s) {
    Edge p;
    int u, queue[MAX], first=0, last=0;

    color[s] = GRAY;
    queue[last++] = s;

    while (first < last) {
        u = queue[first++];
        
        for (p=g[u]; p; p=p->next)
            if (color[p->dest] == WHITE) {
                color[p->dest] = GRAY;
                queue[last++] = p->dest;
            }

        color[u] = BLACK;
    }
}

void bfs (GraphL g, int V) {
    int u;
    printf ("Breadth Traversal:\n");
    for (u=0; u<V; ++u) color[u] = WHITE;
    for (u=0; u<V; ++u)
        if (color[u] == WHITE)
            bfs_visit (g, u);
    for (u=0; u<V; ++u) printf ("V: %d | C: %d\n", u, color[u]);
    printf ("\n");
}

int getEdgeFringe (int f[], int cost[], int size) {
    int r, index=0;
    for (int i=0; i<size; ++i)
        if (cost[f[i]] < cost[f[index]])
            index = i;
    r = f[index];
    f[index] = f[size-1];
    return r;
}

int PrimMST (GraphL g, int V, int s, int mst[V]) {
    int r=0, u, cost[V], fringe[V], fringesize=0;
    Edge p;

    for (u=0; u<V; ++u) color[u] = WHITE;

    cost[s] = 0;
    color[s] = GRAY;
    fringe[fringesize++] = s;

    while (fringesize > 0) {
        u = getEdgeFringe (fringe, cost, fringesize);
        fringesize--;
        r += cost[u];
        color[u] = BLACK;
        for (p=g[u]; p; p=p->next)
            if (color[p->dest]==WHITE || (color[p->dest]==GRAY && p->weight<cost[p->dest])) {
                mst[p->dest] = u;
                cost[p->dest] = p->weight;
                if (color[p->dest]==WHITE) fringe[fringesize++] = p->dest;
            }
    }
    return r;
}

void Warshall (GraphM g, GraphM r, int V) {
    int i, j, k;

    for (i=0; i<V; ++i)
        for (j=0; j<V; ++j)
            r[i][j] = g[i][j];

    for (k=0; k<V; ++k)
        for (i=0; i<V; ++i)
            for (j=0; j<V; ++j)
                if (r[i][k] && r[k][j]) 
                    r[i][j] = 1;
}

int min (int a, int b) {
    int r;
    if (a < b) r = a;
    else r = b;
    return r; 
}

void dynDistances (GraphM g, GraphM r, int V) {
    int i, j, k;
    
    for (i=0; i<V; ++i)
        for (j=0; j<V; ++j)
            r[i][j] = g[i][j];

    for (k=0; k<V; ++k)
        for (i=0; i<V; ++i)
            for (j=0; j<V; ++j)
                if (r[i][j] == 0) r[i][j] = r[i][k]+r[k][j];
                else r[i][j] = min (r[i][j], r[i][k]+r[k][j]);
}