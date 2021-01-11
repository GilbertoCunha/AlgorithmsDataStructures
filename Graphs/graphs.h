#ifndef _GRAPHS
#define _GRAPHS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX/2
#define MAX 100
#define NE 0

typedef int WEIGHT;
typedef struct edge {
    int dest;
    int weight;
    struct edge *next;
} *Edge;

typedef Edge GraphL[MAX];
typedef WEIGHT GraphM[MAX][MAX];

void GraphgraphL (GraphL g, int V);
void GraphgraphM (GraphM g, int V);
void graphMtoL (GraphM gm, GraphL gl, int V);
void graphLtoM (GraphL gl, GraphM gm, int V);
void ShowGraphM (GraphM g, int V);
void ShowGraphL (GraphL g, int V);
void dfs_visit (GraphL g, int s);
void dfs (GraphL g, int V);
void bfs_visit (GraphL g, int s);
void bfs (GraphL g, int V);
int PrimMST (GraphL g, int V, int u, int mst[V]);
void singleDjikstra (GraphL g, int V, int u, int dist[V], int parent[V]);
void Warshall (GraphM g, GraphM r, int V);
void dynDistances (GraphM g, GraphM r, int V);

#endif