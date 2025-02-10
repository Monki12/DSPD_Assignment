#include<stdlib.h>
#include "Linked_Queue.h"


void initialize(Queue* q_ptr)
{
    q_ptr->front = NULL;
    q_ptr->rear = NULL;
}

status_code Enqueue(int data, Queue* q_ptr)
{
    status_code sc = SUCCESS;
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        sc= FAILURE;
    }
    new_node->data = data;
    new_node->next = NULL;
    if(q_ptr->front == NULL)
    {
        q_ptr->front = new_node;
        q_ptr->rear = new_node;
    }
    else
    {
        q_ptr->rear->next = new_node;
        q_ptr->rear = new_node;
    }
    sc= SUCCESS;
    return sc;
}

status_code Dequeue(int* data, Queue* q_ptr)
{
    status_code sc = SUCCESS;
    if(isEmpty(q_ptr))
    {
        sc = FAILURE;
    }
    else
    {
        Node* temp = q_ptr->front;
        *data = temp->data;
        q_ptr->front = q_ptr->front->next;
        free(temp);
    }
    return sc;
}

boolean isEmpty(Queue* q_ptr)
{
    return (q_ptr->front == NULL);
}