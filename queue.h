#ifndef QUEUE_H
#define QUEUE_H

typedef struct {
    void* head_p;
    void* tail_p;
    int size;
} queue_type;

queue_type* constructQueue();
void destructQueue(queue_type** queue_pp);
void enQueue(queue_type* queue_p, void* data_p);
void* deQueue(queue_type* queue_p);
int isEmptyQueue(queue_type *queue_p);
void printQueue(queue_type* queue_p,void (*printData)(void*));
#endif


