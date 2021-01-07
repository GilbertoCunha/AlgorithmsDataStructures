#include <stdio.h>
#include <stdlib.h>
#include "btrees.h"

void GraphBTreeAux (BTree a, FILE *f) {
    if (a != NULL) {
        fprintf (f, "\t%d [label=\"%d\"];\n", a->root, a->root);
        if (a->left != NULL) fprintf (f, "%d -> %d;\n", a->root, a->left->root);
        else if (a->right != NULL) {
            fprintf (f, "\t%d [shape=point];\n", (int) &(a->left));
            fprintf (f, "\t%d -> %d;\n", a->root, (int) &(a->left));
        }
        if (a->right != NULL) fprintf (f, "%d -> %d;\n", a->root, a->right->root);
        else if (a->left != NULL){
            fprintf (f, "\t%d [shape=point];\n", (int) &(a->right));
            fprintf (f, "\t%d -> %d;\n", a->root, (int) &(a->right));
        }
        GraphBTreeAux (a->left, f);
        GraphBTreeAux (a->right, f);
    }
}

void GraphBTree (BTree a) {
    if (a != NULL) {
        FILE *f = fopen ("btree.dot", "w");
        fprintf (f, "digraph G {\n");
        fprintf (f, "\tlabelloc=\"t\";\n");
        fprintf (f, "\tlabel=\"BTree\";\n");
        GraphBTreeAux (a, f);
        fprintf (f, "}\n");
        fclose (f);
        system ("dot -Tpng btree.dot > btree.png");
        system ("open btree.png");
    }
}

void ShowBTreeAux (BTree a) {
    if (a != NULL) {
        printf ("%d ", a->root);
        ShowBTreeAux (a->left);
        ShowBTreeAux (a->right);
    }
}

void ShowBTree (BTree a) {
    printf ("BTree: ");
    ShowBTreeAux (a);
    printf ("\n");
}

void insertBTree (BTree *a, int x) {
    if (*a == NULL) {
        *a = malloc (sizeof (struct node));
        (*a)->root = x;
        (*a)->left = NULL;
        (*a)->right = NULL;
    }
    else if (x < (*a)->root) insertBTree (&((*a)->left), x);
    else if (x > (*a)->root) insertBTree (&((*a)->right), x);
}

int remBTree (BTree *a, int x) {
    int r;
    if (*a == NULL) r = 0;
    else if (x < (*a)->root) r = remBTree (&((*a)->left), x);
    else if (x > (*a)->root) r = remBTree (&((*a)->right), x);
    else {
        r = 1;
        free (*a);
        *a = NULL;
    }
    return r;
}