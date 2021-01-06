#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void ShowStack (Stack s) {
    printf ("Stack: ");
    for (int i=0; i<s.sp; ++i)
        printf ("%d ", s.values[i]);
    printf ("\n");
}

void GraphStackAux (Stack s, FILE *f) {
    fprintf (f, "\t0 [shape=\"record\", label=\"");
    for (int i=s.size; i>0; --i) {
        if (i == s.size) fprintf (f, " <top> | ");
        else if (i < s.sp) fprintf (f, " %d |", s.values[i]);
        else fprintf (f, " <%d> |", i);
    }
    fprintf (f, "%d\"];\n", s.values[0]);
    fprintf (f, "\t1 [shape=plaintext, label=\"sp\"];\n");
    if (s.sp != s.size) fprintf (f, "\t1 -> 0:\"%d\";\n", s.sp);
    else fprintf (f, "\t1 -> 0:\"top\";\n");
}

void GraphStack (Stack s) {
    if (s.size > 0) {
        FILE *f = fopen ("stack.dot", "w");
        fprintf (f, "digraph G {\n");
        fprintf (f, "\tgraph [rankdir = \"LR\"];\n");
        fprintf (f, "\tlabelloc=\"t\";\n");
        fprintf (f, "\tlabel=\"STACK\";\n");
        GraphStackAux (s, f);
        fprintf (f, "}");
        fclose (f);
        system ("dot -Tpng stack.dot > stack.png");
    }
}

int initStack (Stack *s, int size) {
    int r = 1;
    s->values = malloc (size * sizeof (int));
    if (s->values == NULL) r = 0;
    else {
        s->size = size;
        s->sp = 0;
    }
    return r;
}

int push (Stack *s, int x) {
    int r = 1;
    if (s->sp == s->size) {
        int *tmp = malloc (2 * s->size * sizeof (int));
        if (tmp != NULL) {
            for (int i=0; i<s->size; ++i) tmp[i] = s->values[i];
            s->values = tmp;
            s->size *= 2;
        }
        else r = 0;
    }
    if (r != 0) s->values[s->sp++] = x;
    return r;
}

int pop (Stack *s, int *x) {
    int r = 1;
    if (s->sp == 0) r = 0;
    else *x = s->values[--s->sp];
    return r;
}