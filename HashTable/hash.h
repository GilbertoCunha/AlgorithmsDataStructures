#ifndef _HASH
#define _HASH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY   "-"
#define REMOVED "+"
#define MAX 20

typedef struct entry {
    char *key;
    int value;
} *Entry;

typedef struct hash {
    Entry pairs;
    int size, used;
    float lf;
} HashT;

void ShowHash (HashT h);
int initHash (HashT *h, int load_factor);
int djb2hash (HashT h, char *key);
int insertHash (HashT *h, char *key, int value);
int searchHash (HashT h, char *key, int *value);
int removeHash (HashT *h, char *key, int *value);

#endif