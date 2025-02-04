#include "LinkedList.h"

void initList(Node** lpptr)
{
    lpptr = NULL;
}

Node* CreateNode(Node** lpptr, void* data_ptr)
{
   Node* new_ptr = (Node*)malloc(sizeof(Node));
   if(new_ptr != NULL)
   {
        new_ptr->data_ptr = data_ptr;
        new_ptr->next = NULL;
   }
   return new_ptr;
}

status_code InsertAfter(Node** lpptr, Node* prev_ptr , void* data_ptr)
{
    status_code sc = SUCCESS;
    Node* new_ptr = CreateNode(lpptr,data_ptr);
    if(new_ptr == NULL)
    {
        printf("\nMemory Allocation Failed for new Node!");
        sc = FAILURE;
    }
    else
    {
        if(*lpptr == NULL) 
        {
            if(prev_ptr == NULL)
            {
                *lpptr = new_ptr;
            }
            else
            {
                printf("\nMismatch Error");
                sc = FAILURE;
            }
        }
        else
        {
            if(prev_ptr == NULL)
            {
                new_ptr->next = *lpptr;
                *lpptr = new_ptr;
            }
            else
            {
                new_ptr->next = prev_ptr->next;
                prev_ptr->next = new_ptr;
            }
        }
    }

    return sc;
}

status_code DeleteAfter(Node** lpptr, Node* prev_ptr, Node* node_ptr, void** data_pptr)
{
    status_code sc = SUCCESS;
    if(*lpptr == NULL || node_ptr == NULL)
    {
        printf("\nError : Node to delete is NULL!");
        sc=FAILURE;
    }
    else
    {
        if(prev_ptr == NULL)
        {
            if(*lpptr == node_ptr)
            {
                *lpptr = node_ptr->next;
                *data_pptr = node_ptr->data_ptr;
                free(node_ptr);
            }
            else
            {
                sc = FAILURE;
            }
        }
        else
        {
            prev_ptr->next = node_ptr->next;
            *data_pptr = node_ptr->data_ptr;
            free(node_ptr);
        }
    }
    return sc;
}

// Function to print the linked list (assuming integer data for simplicity)
void printList(Node* head) {
    Node* current = head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d -> ", *(int*)(current->data_ptr));
        current = current->next;
    }
    printf("NULL\n");
}

// int main() {
//     Node* head = NULL;
//     int data1 = 10, data2 = 20, data3 = 30, data4 = 40;
//     void* data_ptr;

//     // 1. Initialize the list
//     initList(&head);

//     // 2. Insert nodes
//     printf("Inserting %d at the beginning...\n", data1);
//     InsertAfter(&head, NULL, &data1);  // Insert first node
//     printList(head);

//     printf("Inserting %d after the first node...\n", data2);
//     InsertAfter(&head, head, &data2);  // Insert after first node
//     printList(head);

//     printf("Inserting %d at the beginning...\n", data3);
//     InsertAfter(&head, NULL, &data3);  // Insert at the head
//     printList(head);

//     printf("Inserting %d after second node...\n", data4);
//     InsertAfter(&head, head->next, &data4);  // Insert after second node
//     printList(head);

//     // 3. Delete nodes
//     printf("Deleting the head node...\n");
//     DeleteAfter(&head, NULL, head, &data_ptr);
//     printf("Deleted data: %d\n", *(int*)data_ptr);
//     printList(head);

//     printf("Deleting node after the first node...\n");
//     DeleteAfter(&head, head, head->next, &data_ptr);
//     printf("Deleted data: %d\n", *(int*)data_ptr);
//     printList(head);

//     return 0;
// }
