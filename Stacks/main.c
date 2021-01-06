#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main () {
    Stack s;
    initStack (&s, 5);
    int v[10] = {1, 4, 7, 2, 3, 5, 8, 6, 9, 0};
    printf ("Array: ");
    for (int i=0; i<10; ++i) {
        printf ("%d ", v[i]);
        push (&s, v[i]);
    }
    printf ("\n");
    ShowStack (s);

    printf ("\nPopping last 3 elements:\n");
    int value;
    for (int i=0; i<3; ++i) pop (&s, &value);
    ShowStack (s);
    GraphStack (s);

    return 0;
}