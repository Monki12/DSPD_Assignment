#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include "LinkedList.h"

typedef struct Node_tag{
    int data;
    struct Node_tag* next;
} Node;

typedef struct Queue_tag{
    Node* front;
    Node* rear;
} Queue;

void initialize(Queue* q_ptr);
status_code Enqueue(int data, Queue* q_ptr);
status_code Dequeue(int* data, Queue* q_ptr);
boolean isEmpty(Queue* q_ptr);

#endif