#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include<stdio.h>
#include "FamilyStructure.h"

typedef enum {FAILURE,SUCCESS} status_code;

typedef enum {FAMILY,USER,EXPENSE} NodeType;

typedef struct Node_tag{
    struct Node_tag* next;
    void* data_ptr;
} Node;

void initList(Node** head);
Node* CreateNode(Node** lpptr, void* data_ptr);
status_code InsertAfter(Node** lpptr, Node* prev_ptr , void* data_ptr);
status_code DeleteAfter(Node** lpptr, Node* prev_ptr, Node* node_ptr, void** data_pptr);

#endif