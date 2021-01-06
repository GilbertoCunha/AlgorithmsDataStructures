#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void ShowLInt (LInt l) {
    printf ("Linked List: ");
    while (l != NULL && l->next != NULL) {
        printf ("%d->", l->value);
        l = l->next;
    }
    if (l != NULL) printf ("%d\n", l->value);
}

void GraphLIntAux (LInt l, FILE *f, int index) {
    if (l != NULL) {
        fprintf (f, "\t%d [label=\"%d\"];\n", index, l->value);
        if (l->next == NULL) fprintf (f, "\t%d [shape=point];\n", index+1);
        fprintf (f, "\t%d -> %d;\n", index, index+1);
        GraphLIntAux (l->next, f, index+1);
    }
}

void GraphLInt (LInt l) {
    if (l != NULL) {
        FILE *f = fopen ("list.dot", "w");
        fprintf (f, "digraph G {\n");
        fprintf (f, "\tlabelloc=\"t\";\n");
        fprintf (f, "\tlabel=\"LINKED LIST\"\n");
        GraphLIntAux (l, f, 0);
        fprintf (f, "}");
        fclose (f);
        system ("dot -Tpng list.dot > list.png");
    }
}

void insertHead (LInt *l, int x) {
    LInt new = (LInt) malloc (sizeof (struct lista));
    new->value = x;
    new->next = *l;
    *l = new;
}

int removeLInt (LInt *l, int x) {
    int r = 1;
    if (*l == NULL) r = 0;
    else if ((*l)->value == x) (*l) = (*l)->next;
    else r = removeLInt (&((*l)->next), x);
    return r;
}