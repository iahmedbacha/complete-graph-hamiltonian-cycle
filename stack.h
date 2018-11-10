#ifndef STACK_H
#define STACK_H

typedef struct{
    void* head_p;
    int size;
} stack_type;

stack_type* constructStack();
void destructStack(stack_type** stack_pp);
void push(stack_type* stack_p, void* data_p);
void* pop(stack_type* stack_p);
int isEmptyStack(stack_type *stack_p);
void printStack(stack_type* stack_p,void (*printData)(void*));
#endif

