#include "arrays.h"

void ShowArray (int v[], int n) {
    printf ("Array: ");
    for (int i=0; i<n; ++i) printf ("%d ", v[i]);
    printf ("\n");
}

void swap (int v[], int i, int j) {
    int aux = v[i];
    v[i] = v[j]; 
    v[j] = aux;
}

void bubblesort (int v[], int n) {
    int go = 1;
    while (go) {
        go = 0;
        for (int i=1; i<n; ++i) {
            if (v[i-1] > v[i]) {
                swap (v, i-1, i);
                go = 1;
            }
        }
    }
}

void selectionsort (int v[], int n) {
    int aux;
    for (int i=0; i<n; ++i) {
        aux = i;
        for (int j=i+1; j<n; ++j)
            if (v[j] < v[aux]) aux = j;
        swap (v, i, aux);
    }
}

void insertionsort (int v[], int n) {
    for (int i=1; i<n; ++i)
        for (int j=i; j>0 && v[j]<v[j-1]; --j)
            swap (v, j, j-1);
}

int partition (int v[], int n) {
    int pivot = 0;
    int low = pivot + 1;
    int high = n - 1;

    while (low < high) {
        while (v[low] < v[pivot] && low<n) low++;
        while (v[high] >= v[pivot] && high>=pivot) high--;
        if (low < high) swap (v, low, high);
    } 

    swap (v, pivot, high);
    return high;
}

void quicksort (int v[], int n) {
    // Conquer
    int p = partition (v, n);
    // Divide
    if (p > 1) quicksort (v, p);
    if (n-p-1 > 1) quicksort (v+p+1, n-p-1);
}

void merge (int v[], int n, int mid) {
    int a[mid], b[n-mid];

    // Subdivide array
    for (int i=0; i<mid; ++i) a[i] = v[i];
    for (int i=0; i<n-mid; ++i) b[i] = v[mid+i];

    // Insert elements of arrays a and b into v in sorted manner
    int i=0, j=0, k=0;
    while (j<mid && k<n-mid) {
        if (a[j] < b[k]) v[i++] = a[j++];
        else v[i++] = b[k++];
    }

    // Insert leftover elements
    while (j<mid) v[i++] = a[j++];
    while (k<n-mid) v[i++] = b[k++];
}

void mergesort (int v[], int n) {
    if (n > 1) {
        int mid = n / 2;
        // Divide
        mergesort (v, mid);
        mergesort (v + mid, n - mid);
        // Conquer
        merge (v, n, mid);
    }
}

