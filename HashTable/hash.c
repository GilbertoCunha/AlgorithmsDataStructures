#include "hash.h"

void ShowHash (HashT h) {
    printf ("HashTable:\n");
    for (int i=0; i<h.size; ++i)
        printf ("%d: %s -> %d\n", i, h.pairs[i].key, h.pairs[i].value);
    printf ("\n");
}

int initHash (HashT *h, int load_factor) {
    h->size = MAX; h->used = 0; h->lf = load_factor;
    h->pairs = malloc (h->size * (sizeof (struct entry)));
    for (int i=0; i<h->size; ++i) h->pairs[i].key = strdup (EMPTY);
}

int djb2hash (HashT h, char *key) {
    /*int c, hash = 5381;
    while (c = *key++) hash = ((hash << 5) + hash) + c;
    return hash % h.size;*/
    return key[0] % h.size;
}

int freeEntry (char *str) {
    int r;
    if (strcmp (str, EMPTY) == 0) r = 1;
    else if (strcmp (str, REMOVED) == 0) r = 1;
    else r = 0;
    return r;
}

int insertHash (HashT *h, char *key, int value) {
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