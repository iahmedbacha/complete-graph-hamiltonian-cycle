#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node_type{
    void* data_p;
    struct node_type* previous_p;
} node_type;

stack_type* constructStack(){
    stack_type* stack_p = malloc(sizeof(stack_p));
    if (stack_p!=NULL){
        stack_p->head_p = NULL;
        stack_p->size = 0;
    }
    return stack_p;
}
void destructStack(stack_type** stack_pp){
    while (!isEmptyStack(*stack_pp)){
        node_type* previous_p = ((node_type*)(*stack_pp)->head_p)->previous_p;
        free(((node_type*)(*stack_pp)->head_p)->data_p);
        free((*stack_pp)->head_p);
        (*stack_pp)->head_p = previous_p;
        (*stack_pp)->size--;
    }
    free(*stack_pp);
    *stack_pp=NULL;
}
node_type* createNodeSP(void *data_p){
    node_type* node_p = malloc(sizeof(node_type));
    if(node_p!=NULL){
        node_p->data_p = data_p;
        node_p->previous_p = NULL;
    }
    return node_p;
}
void push(stack_type* stack_p, void* data_p){
    node_type* node_p= createNodeSP(data_p);
    if (node_p!=NULL){
        if (stack_p!=NULL){
            node_p->previous_p = stack_p->head_p;
            stack_p->head_p = node_p;
            stack_p->size++;
        }
    }
}
void* pop(stack_type* stack_p){
    if (isEmptyStack(stack_p)){
        return NULL;
    }{
        node_type* previous_head = stack_p->head_p;
        void* data_p = previous_head->data_p;
        stack_p->head_p = previous_head->previous_p;
        free(previous_head);
        stack_p->size--;
        return data_p;
    }
}

int isEmptyStack(stack_type *stack_p){
    return stack_p==NULL || stack_p->size == 0;
}

void printStack(stack_type* stack_p,void (*printData)(void*)){
    if(stack_p == NULL){
        printf("-Stack: NULL (Stack not constructed).\n");
    } else{
        printf("-Stack: (%d)\n",stack_p->size);
        node_type* head_p = stack_p->head_p;
        while (head_p != NULL){
            printData(head_p->data_p);
            head_p=head_p->previous_p;
        }
    }
}