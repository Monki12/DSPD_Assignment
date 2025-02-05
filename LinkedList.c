#include "LinkedList.h"

void initFamNode(FamNode* fptr)
{
    fptr->family_id = 0;
    fptr->family_name = NULL;
    fptr->no_of_users = 0;
    fptr->family_income = 0.0;
    fptr->family_expense = 0.0;
    fptr->family_members_ptr = NULL;
    fptr->next = NULL;
}

void initUserNode(UserNode* uptr)
{
    uptr->user_id = 0;
    uptr->family_id = 0;
    uptr->user_name = NULL;
    uptr->user_income = 0.0;
    uptr->next = NULL;
}

void initExpenseNode(ExpenseNode* eptr)
{
    eptr->expense_id = 0;
    eptr->user_id = 0;
    eptr->category = 0;
    eptr->expense_amount = 0.0;
    eptr->date = 0;
    eptr->next = NULL;
}

FamNode* CreateFamNode()
{
    FamNode* fptr = (FamNode*)malloc(sizeof(FamNode));
    if(fptr != NULL)
    {
        fptr->family_id = 0;
        fptr->family_name = NULL;
        fptr->no_of_users = 0;
        fptr->family_income = 0.0;
        fptr->family_expense = 0.0;
        fptr->family_members_ptr = NULL;
        fptr->next = NULL;
    }
   return fptr;
}

UserNode* CreateUserNode()
{
    UserNode* uptr = (UserNode*)malloc(sizeof(UserNode));
    if(uptr != NULL)
    {
        uptr->user_id = 0;
        uptr->family_id = 0;
        uptr->user_name = NULL;
        uptr->user_income = 0.0;
        uptr->next = NULL;
    }
   return uptr;
}

ExpenseNode* CreateNode(void* data_ptr)
{
   ExpenseNode* eptr = (ExpenseNode*)malloc(sizeof(ExpenseNode));
   if(eptr != NULL)
   {
        eptr->expense_id = 0;
        eptr->user_id = 0;
        eptr->category = 0;
        eptr->expense_amount = 0.0;
        eptr->date = 0;
        eptr->next = NULL;
   }
   return eptr;
}

status_code InsertAfter_Fam(FamNode** lpptr, FamNode* prev_ptr, FamNode* nptr)
{
    status_code sc = SUCCESS;
    if(nptr == NULL)
    {
        printf("\nMemory Allocation Failed for new FamNode!");
        sc = FAILURE;
    }
    else
    {
        if(*lpptr == NULL) 
        {
            if(prev_ptr == NULL)
            {
                *lpptr = nptr;
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
                nptr->next = *lpptr;
                *lpptr = nptr;
            }
            else
            {
                nptr->next = prev_ptr->next;
                prev_ptr->next = nptr;
            }
        }
    }

    return sc;
}

status_code InsertAfter_User(UserNode** lpptr, UserNode* prev_ptr, UserNode* nptr)
{
    status_code sc = SUCCESS;
    if(nptr == NULL)
    {
        printf("\nMemory Allocation Failed for new UserNode!");
        sc = FAILURE;
    }
    else
    {
        if(*lpptr == NULL) 
        {
            if(prev_ptr == NULL)
            {
                *lpptr = nptr;
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
                nptr->next = *lpptr;
                *lpptr = nptr;
            }
            else
            {
                nptr->next = prev_ptr->next;
                prev_ptr->next = nptr;
            }
        }
    }

    return sc;
}

status_code InsertAfter_Expense(ExpenseNode** lpptr, ExpenseNode* prev_ptr, ExpenseNode* nptr)
{
    status_code sc = SUCCESS;
    if(nptr == NULL)
    {
        printf("\nMemory Allocation Failed for new ExpenseNode!");
        sc = FAILURE;
    }
    else
    {
        if(*lpptr == NULL) 
        {
            if(prev_ptr == NULL)
            {
                *lpptr = nptr;
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
                nptr->next = *lpptr;
                *lpptr = nptr;
            }
            else
            {
                nptr->next = prev_ptr->next;
                prev_ptr->next = nptr;
            }
        }
    }

    return sc;
}


// Node* CreateNode(void* data_ptr)
// {
//    Node* new_ptr = (Node*)malloc(sizeof(Node));
//    if(new_ptr != NULL)
//    {
//         new_ptr->data_ptr = data_ptr;
//         new_ptr->next = NULL;
//    }
//    return new_ptr;
// }

// status_code InsertAfter(Node** lpptr, Node* prev_ptr , void* data_ptr)
// {
//     status_code sc = SUCCESS;
//     Node* new_ptr = CreateNode(data_ptr);
//     if(new_ptr == NULL)
//     {
//         printf("\nMemory Allocation Failed for new Node!");
//         sc = FAILURE;
//     }
//     else
//     {
//         if(*lpptr == NULL) 
//         {
//             if(prev_ptr == NULL)
//             {
//                 *lpptr = new_ptr;
//             }
//             else
//             {
//                 printf("\nMismatch Error");
//                 sc = FAILURE;
//             }
//         }
//         else
//         {
//             if(prev_ptr == NULL)
//             {
//                 new_ptr->next = *lpptr;
//                 *lpptr = new_ptr;
//             }
//             else
//             {
//                 new_ptr->next = prev_ptr->next;
//                 prev_ptr->next = new_ptr;
//             }
//         }
//     }

//     return sc;
// }

// status_code DeleteAfter(Node** lpptr, Node* prev_ptr, Node* node_ptr, void** data_pptr)
// {
//     status_code sc = SUCCESS;
//     if(*lpptr == NULL || node_ptr == NULL)
//     {
//         printf("\nError : Node to delete is NULL!");
//         sc=FAILURE;
//     }
//     else
//     {
//         if(prev_ptr == NULL)
//         {
//             if(*lpptr == node_ptr)
//             {
//                 *lpptr = node_ptr->next;
//                 *data_pptr = node_ptr->data_ptr;
//                 free(node_ptr);
//             }
//             else
//             {
//                 sc = FAILURE;
//             }
//         }
//         else
//         {
//             prev_ptr->next = node_ptr->next;
//             *data_pptr = node_ptr->data_ptr;
//             free(node_ptr);
//         }
//     }
//     return sc;
// }

// // Function to print the linked list (assuming integer data for simplicity)
// void printList(Node* head)
// {
//     Node* current = head;
//     printf("\nLinked List: ");
//     while (current != NULL) {
//         printf("%d -> ", *(int*)(current->data_ptr));
//         current = current->next;
//     }
//     printf("NULL\n");
// }

// void printTypeList(Node* head, NodeType type) {
//     Node* current = head;
//     printf("\nLinked List:\n");

//     while (current != NULL) {
//         switch (type) {
//             case FAMILY: {
//                 Family* fam = (Family*)(current->data_ptr);
//                 printf("Family ID: %s -> ", fam->family_name);
//                 break;
//             }
//             case USER: {
//                 User* user = (User*)(current->data_ptr);
//                 printf("User ID: %s -> ", user->user_name);
//                 break;
//             }
//             case EXPENSE: {
//                 Expense* expense = (Expense*)(current->data_ptr);
//                 printf("Expense ID: %d -> ", expense->expense_id);
//                 break;
//             }
//             default:
//                 printf("Unknown NodeType -> ");
//         }
//         current = current->next;
//     }
//     printf("NULL\n");
// }


// // int main() {
// //     Node* head = NULL;
// //     int data1 = 10, data2 = 20, data3 = 30, data4 = 40;
// //     void* data_ptr;

// //     // 1. Initialize the list
// //     initList(&head);

// //     // 2. Insert nodes
// //     printf("Inserting %d at the beginning...\n", data1);
// //     InsertAfter(&head, NULL, &data1);  // Insert first node
// //     printList(head);

// //     printf("Inserting %d after the first node...\n", data2);
// //     InsertAfter(&head, head, &data2);  // Insert after first node
// //     printList(head);

// //     printf("Inserting %d at the beginning...\n", data3);
// //     InsertAfter(&head, NULL, &data3);  // Insert at the head
// //     printList(head);

// //     printf("Inserting %d after second node...\n", data4);
// //     InsertAfter(&head, head->next, &data4);  // Insert after second node
// //     printList(head);

// //     // 3. Delete nodes
// //     printf("Deleting the head node...\n");
// //     DeleteAfter(&head, NULL, head, &data_ptr);
// //     printf("Deleted data: %d\n", *(int*)data_ptr);
// //     printList(head);

// //     printf("Deleting node after the first node...\n");
// //     DeleteAfter(&head, head, head->next, &data_ptr);
// //     printf("Deleted data: %d\n", *(int*)data_ptr);
// //     printList(head);

// //     return 0;
// // }
