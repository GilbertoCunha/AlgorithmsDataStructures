#ifndef _HEAPS
#define _HEAPS

typedef int Elem;
typedef struct heap {
    int used;
    int size;
    int *values;
} Heap;

void ShowHeap (Heap h);
void GraphHeap (Heap h);
void initHeap (Heap *h, int size);
int insertHeap (Heap *h, int x);
int extractMin (Heap *h, int *x);
int minHeapOK (Heap h);

#endif