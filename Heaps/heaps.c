#include <stdio.h>
#include <stdlib.h>
#include "heaps.h"

void ShowHeap (Heap h) {
    printf ("Heap: ");
    for (int i=0; i<h.used; ++i) printf ("%d ", h.values[i]);
    printf ("\n");
}

void GraphHeapInd (Heap h, FILE *f, int index) {
    if (index < h.used) {
        int lchild = 2 * index + 1;
        int rchild = lchild + 1;
        fprintf (f, "\t%d [label=\"%d\"];\n", index, h.values[index]);
        if (lchild < h.used)
            fprintf (f, "\t%d -> %d;\n", index, lchild);
        if (rchild < h.used)
            fprintf (f, "\t%d -> %d;\n", index, rchild);
        GraphHeapInd (h, f, lchild);
        GraphHeapInd (h, f, rchild);
    }
}

void GraphHeap (Heap h) {
    if (h.used != 0) {
        FILE *f = fopen ("heap.dot", "w");
        fprintf (f, "digraph G {\n");
        fprintf (f, "\tlabelloc=\"t\";\n");
        fprintf (f, "\tlabel=\"MIN HEAP\";\n");
        GraphHeapInd (h, f, 0);
        fprintf (f, "}");
        fclose (f);
        system ("dot -Tpng heap.dot > heap.png");
    }
}

void initHeap (Heap *h, int size) {
    h->values = malloc (size * sizeof (int));
    h->size = size;
    h->used = 0;
}

int insertHeap (Heap *h, int x) {
    int r = 1;
    if (h == NULL) r = 0;
    else if (h->used == h->size) {
        int *tmp = malloc (2 * h->size * sizeof (int));
        if (tmp == NULL) r = 0;
        else {
            for (int i=0; i<h->used; ++i) tmp[i] = h->values[i];
            h->values = tmp;
            h->size *= 2;
        }
    }
    
    if (r == 1) {
        int index = h->used++;
        h->values[index] = x;
        while (index > 0 && h->values[index] < h->values[(index-1)/2]) {
            int aux = h->values[index];
            h->values[index] = h->values[(index-1)/2];
            index = (index-1)/2;
            h->values[index] = aux;
        }
    }

    return r;
}

int min (int a, int b) {
    int r;
    if (a < b) r = a;
    else r = b;
    return r;
}

void heapify (Heap *h, int index) {
    int left = 2 * index + 1;
    int right = left + 1;

    if (left >= h->used || left < 0) left = -1;
    if (right >= h->used || left < 0) right = -1;

    if (left == -1);
    else if (right == -1 && h->values[index] > h->values[left]) {
        int aux = h->values[index];
        h->values[index] = h->values[left];
        h->values[left] = aux;
        heapify (h, left);
    }
    else if (h->values[index] > min(h->values[left], h->values[right])) {
        int child;
        if (h->values[left] < h->values[right]) child = left;
        else child = right;
        int aux = h->values[index];
        h->values[index] = h->values[child];
        h->values[child] = aux;
        heapify (h, child);
    }
}

int extractMin (Heap *h, int *x) {
    int r = 1;

    if (h == NULL || h->used == 0) r = 0;
    else {
        *x = h->values[0];
        h->values[0] = h->values[--h->used];
        heapify (h, 0);
    }

    return r;
}

int minHeapOKind (Heap h, int index) {
    int r;
    int left = 2 * index + 1;
    int right = left + 1;

    if (left >= h.used) left = -1;
    if (right >= h.used) right = -1;

    if (left == -1) r = 1;
    else if (right == -1 && h.values[index] > h.values[left]) r = 0;
    else if (right == -1) r = minHeapOKind (h, left);
    else if (h.values[index] <= h.values[left] && h.values[index] <= h.values[right]) 
        r = min(minHeapOKind (h, left), minHeapOKind (h, right));
    else r = 0;

    return r;
}

int minHeapOK (Heap h) {
    return minHeapOKind (h, 0);
}