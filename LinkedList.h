#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>

typedef enum {FAILURE,SUCCESS} status_code;

typedef struct Node_tag{
    struct Node_tag* next;
    void* data_ptr;
} Node;

void initList(Node** head);

#endif