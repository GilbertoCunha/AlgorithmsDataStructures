#ifndef _LINKED_LIST
#define _LINKED_LIST

typedef struct lista {
    int value;
    struct lista *next;
} *LInt;

void ShowLInt (LInt l);
void GraphLInt (LInt l);
void insertHead (LInt *l, int x);
void insertTail (LInt *l, int x);
int removeLInt (LInt *l, int x);

#endif