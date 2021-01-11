#include "hash.h"

void ShowHash (HashT h) {
    printf ("HashTable:\n");
    for (int i=0; i<h.size; ++i)
        printf ("%d: %s -> %d\n", i, h.pairs[i].key, h.pairs[i].value);
    printf ("\n");
}

int initHash (HashT *h, float load_factor) {
    h->size = MAX; 
    h->used = 0; 
    h->lf = load_factor; 
    h->pairs = malloc (h->size * (sizeof (struct entry)));
    for (int i=0; i<h->size; ++i) h->pairs[i].key = strdup (EMPTY);
}

int djb2hash (HashT h, char *key) {
    int c, hash = 5381;
    while (c = *key++) hash = ((hash << 5) + hash) + c;
    return hash % h.size;
}

int freeEntry (char *str) {
    int r;
    if (strcmp (str, EMPTY) == 0) r = 1;
    else if (strcmp (str, REMOVED) == 0) r = 1;
    else r = 0;
    return r;
}

void reHash (HashT *h) {
    HashT aux;
    int hash;
    // Copiar para uma hashtable auxiliar
    aux.used = h->used; aux.size = h->size; aux.lf = h->lf;
    aux.pairs = malloc (aux.size * sizeof (struct entry));
    for (int i=0; i<aux.size; ++i) {
        aux.pairs[i].key = strdup (h->pairs[i].key);
        aux.pairs[i].value = h->pairs[i].value;
    }

    // Reinicializar a hash
    free (h->pairs); h->size *= 2; h->used = 0; 
    h->pairs = malloc (h->size * sizeof (struct entry));
    for (int i=0; i<h->size; ++i) h->pairs[i].key = strdup (EMPTY);

    // Rehashing
    for (int i=0; i<aux.size; ++i)
        if (!freeEntry (aux.pairs[i].key))
            insertHash (h, aux.pairs[i].key, aux.pairs[i].value);
}

int insertHash (HashT *h, char *key, int value) {
    float lf = h->used / h->size;
    if (lf >= h->lf) reHash (h);

    int i, r = 1, hash = djb2hash (*h, key);
    for (i=hash; !freeEntry (h->pairs[i].key); i=(i+1)%h->size);
    h->pairs[i].key = strdup (key);
    h->pairs[i].value = value;
    h->used++;

    return i;
}

int searchHash (HashT h, char *key, int *value) {
    int r, hash = djb2hash (h, key);
    int i = hash;
    while (strcmp (h.pairs[i].key, key) != 0) {
        if (strcmp (h.pairs[i].key, EMPTY) == 0) break;
        i = (i+1) % h.size;
        if (i == hash) break;
    }
    if (strcmp (h.pairs[i].key, key) == 0) { r = 1; *value = h.pairs[i].value; }
    else r = 0;
    return r;
}

int removeHash (HashT *h, char *key, int *value) {
    int r, hash = djb2hash (*h, key);
    int i = hash;
    while (strcmp (h->pairs[i].key, key) != 0) {
        if (strcmp (h->pairs[i].key, EMPTY) == 0) break;
        i = (i+1) % h->size;
        if (i == hash) break;
    }
    if (strcmp (h->pairs[i].key, key) == 0) { 
        *value = h->pairs[i].value; 
        r = 1;
        h->pairs[i].key = strdup (REMOVED);
        h->used--;
    }
    else r = 0;
    return r;
}