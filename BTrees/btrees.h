#ifndef _BTREES
#define _BTREES

typedef struct node {
    int root;
    struct node *left;
    struct node *right;
} *BTree;

void GraphBTree (BTree a);
void ShowBTree (BTree a);
void insertBTree (BTree *a, int x);
int remBTree (BTree *a, int x);

#endif