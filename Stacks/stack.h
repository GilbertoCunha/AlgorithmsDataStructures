#ifndef _STACK
#define _STACK

typedef struct stack {
    int *values;
    int size;
    int sp;
} Stack;

void ShowStack (Stack s);
void GraphStack (Stack s);
int initStack (Stack *s, int size);
int push (Stack *s, int x);
int pop (Stack *s, int *x);

#endif