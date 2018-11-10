#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct node_type{
    void* data_p;
    struct node_type* previous_p;
} node_type;

queue_type* constructQueue(){
    queue_type* queue_p = malloc(sizeof(queue_type));
    if(queue_p!=NULL){
        queue_p->head_p = NULL;
        queue_p->tail_p = NULL;
        queue_p->size = 0;
    }
    return queue_p;
}

void destructQueue(queue_type** queue_pp){
    while (!isEmptyQueue(*queue_pp)){
        node_type* previous_p = ((node_type*)(*queue_pp)->head_p)->previous_p;
        free(((node_type*)(*queue_pp)->head_p)->data_p);
        free((*queue_pp)->head_p);
        (*queue_pp)->head_p = previous_p;
        (*queue_pp)->size--;
    }
    free(*queue_pp);
    *queue_pp=NULL;
}

node_type* createNodeQP(void *data_p){
    node_type* node_p = malloc(sizeof(node_type));
    if (node_p!=NULL){
        node_p->data_p = data_p;
        node_p->previous_p = NULL;
    }
    return node_p;
}

void enQueue(queue_type* queue_p, void* data_p){
    if (queue_p==NULL){
        return;
    }
    node_type* node_p= createNodeQP(data_p);
    if (node_p!=NULL){
        if (!isEmptyQueue(queue_p)){
            ((node_type*)queue_p->tail_p)->previous_p = node_p;
        } else {
            queue_p->head_p = node_p;
        }
        queue_p->tail_p = node_p;
        queue_p->size++;
    }
}

void* deQueue(queue_type* queue_p){
    if  (!isEmptyQueue(queue_p)){
        node_type* previous_head = queue_p->head_p;
        if (queue_p->head_p == queue_p->tail_p){
            queue_p->tail_p = previous_head->previous_p;
        }
        queue_p->head_p = previous_head->previous_p;
        void* data_p= previous_head->data_p;
        free(previous_head);
        queue_p->size--;
        return data_p;
    } else{
        return NULL;
    }
}

int isEmptyQueue(queue_type *queue_p){
    return queue_p==NULL || queue_p->size == 0;
}

void printQueue(queue_type* queue_p,void (*printData)(void*)){
    if(queue_p == NULL){
        printf("-Queue: NULL (Queue not constructed).\n");
    } else{
        printf("-Queue: (%d)\n",queue_p->size);
        node_type* head_p = queue_p->head_p;
        while (head_p != NULL){
            printData(head_p->data_p);
            head_p=head_p->previous_p;
        }
    }
}