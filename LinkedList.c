#include "LinkedList.h"

void initFamNode(FamNode* fptr)
{
    fptr->family_id = 0;
    strcpy(fptr->family_name,"");
    fptr->no_of_users = 0;
    fptr->family_income = 0.0;
    fptr->family_expense = 0.0;
    memset(fptr->family_members_ptr, 0, sizeof(fptr->family_members_ptr));
    fptr->next = NULL;
}

void initUserNode(UserNode* uptr)
{
    uptr->user_id = 0;
    uptr->family_id = 0;
    strcpy(uptr->user_name,"");
    uptr->user_income = 0.0;
    memset(uptr->category_expense, 0, sizeof(uptr->category_expense));
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
        strcpy(fptr->family_name,"");
        fptr->no_of_users = 0;
        fptr->family_income = 0.0;
        fptr->family_expense = 0.0;
        memset(fptr->family_members_ptr, 0, sizeof(fptr->family_members_ptr));
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
        strcpy(uptr->user_name,"");
        uptr->user_income = 0.0;
        memset(uptr->category_expense, 0, sizeof(uptr->category_expense));
        uptr->next = NULL;
    }
   return uptr;
}

ExpenseNode* CreateExpenseNode()
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

FamNode* SearchFamList(FamNode* lptr,FamNode** prev_ptr,int id)
{
    FamNode* nptr = lptr;
    while(nptr != NULL && nptr->family_id != id)
    {
        *prev_ptr = nptr;
        nptr = nptr->next;
    }
    return nptr;
}

UserNode* SearchUserList(UserNode* lptr,UserNode** prev_ptr,int id)
{
    UserNode* nptr = lptr;
    while(nptr != NULL && nptr->user_id != id)
    {
        *prev_ptr = nptr;
        nptr = nptr->next;
    }
    return nptr;
}

ExpenseNode* SearchExpenseList(ExpenseNode* lptr,ExpenseNode** prev_ptr,int id)
{
    ExpenseNode* nptr = lptr;
    while(nptr != NULL && nptr->expense_id != id)
    {
        *prev_ptr = nptr;
        nptr = nptr->next;
    }
    return nptr;
}

status_code DeleteAfter_Fam(FamNode** lpptr, FamNode* prev_ptr, FamNode* nptr)
{
    status_code sc = SUCCESS;
    if(*lpptr == NULL || nptr == NULL)
    {
        printf("\nError : Node to delete is NULL!");
        sc=FAILURE;
    }
    else
    {
        if(prev_ptr == NULL)
        {
            if(*lpptr == nptr)
            {
                *lpptr = nptr->next;
                free(nptr);
            }
            else
            {
                sc = FAILURE;
            }
        }
        else
        {
            prev_ptr->next = nptr->next;
            free(nptr);
        }
    }
    return sc;
}

status_code DeleteAfter_User(UserNode** lpptr, UserNode* prev_ptr, UserNode* nptr)
{
    status_code sc = SUCCESS;
    if(*lpptr == NULL || nptr == NULL)
    {
        printf("\nError : Node to delete is NULL!");
        sc=FAILURE;
    }
    else
    {
        if(prev_ptr == NULL)
        {
            if(*lpptr == nptr)
            {
                *lpptr = nptr->next;
                free(nptr);
            }
            else
            {
                sc = FAILURE;
            }
        }
        else
        {
            prev_ptr->next = nptr->next;
            free(nptr);
        }
    }
    return sc;
}

status_code DeleteAfter_Exp(ExpenseNode** lpptr, ExpenseNode* prev_ptr, ExpenseNode* nptr)
{
    status_code sc = SUCCESS;
    if(*lpptr == NULL || nptr == NULL)
    {
        printf("\nError : Node to delete is NULL!");
        sc=FAILURE;
    }
    else
    {
        if(prev_ptr == NULL)
        {
            if(*lpptr == nptr)
            {
                *lpptr = nptr->next;
                free(nptr);
            }
            else
            {
                sc = FAILURE;
            }
        }
        else
        {
            prev_ptr->next = nptr->next;
            free(nptr);
        }
    }
    return sc;
}

// Merge Sort for Family List
FamNode* mergeSortedFamilies(FamNode* a, FamNode* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->family_id <= b->family_id) {
        a->next = mergeSortedFamilies(a->next, b);
        return a;
    } else {
        b->next = mergeSortedFamilies(a, b->next);
        return b;
    }
}

void splitFamilyList(FamNode* source, FamNode** front, FamNode** back) {
    FamNode* fast = source->next;
    FamNode* slow = source;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSortFamilies(FamNode** headRef) {
    if (!(*headRef) || !(*headRef)->next) return;

    FamNode* a;
    FamNode* b;

    splitFamilyList(*headRef, &a, &b);
    mergeSortFamilies(&a);
    mergeSortFamilies(&b);
    *headRef = mergeSortedFamilies(a, b);
}

// Merge Sort for User List
UserNode* mergeSortedUsers(UserNode* a, UserNode* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->user_id <= b->user_id) {
        a->next = mergeSortedUsers(a->next, b);
        return a;
    } else {
        b->next = mergeSortedUsers(a, b->next);
        return b;
    }
}

void splitUserList(UserNode* source, UserNode** front, UserNode** back) {
    UserNode* fast = source->next;
    UserNode* slow = source;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSortUsers(UserNode** headRef) {
    if (!(*headRef) || !(*headRef)->next) return;

    UserNode* a;
    UserNode* b;

    splitUserList(*headRef, &a, &b);
    mergeSortUsers(&a);
    mergeSortUsers(&b);
    *headRef = mergeSortedUsers(a, b);
}

// Merge Sort for Expenses (Sort by user_id first, then by expense_id)
ExpenseNode* mergeSortedExpenses(ExpenseNode* a, ExpenseNode* b) {
    if (!a) return b;
    if (!b) return a;

    if ((a->user_id < b->user_id) || 
        (a->user_id == b->user_id && a->expense_id < b->expense_id)) {
        a->next = mergeSortedExpenses(a->next, b);
        return a;
    } else {
        b->next = mergeSortedExpenses(a, b->next);
        return b;
    }
}

void splitExpenseList(ExpenseNode* source, ExpenseNode** front, ExpenseNode** back) {
    ExpenseNode* fast = source->next;
    ExpenseNode* slow = source;

    while (fast) {
        fast = fast->next;
        if (fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

void mergeSortExpenses(ExpenseNode** headRef) {
    if (!(*headRef) || !(*headRef)->next) return;

    ExpenseNode* a;
    ExpenseNode* b;

    splitExpenseList(*headRef, &a, &b);
    mergeSortExpenses(&a);
    mergeSortExpenses(&b);
    *headRef = mergeSortedExpenses(a, b);
}

// Display Family List
void displayFamilies(FamNode *Fams_List) {
    if (Fams_List == NULL) {
        printf("\nNo families recorded.\n");
        return;
    }

    printf("\nFamily List:\n");
    printf("----------------------------------------------------------\n");
    printf("| %-5s | %-15s | %-10s | %-10s | %-10s |\n", 
           "ID", "Family Name", "Users", "Income", "Expense");
    printf("----------------------------------------------------------\n");

    FamNode *temp = Fams_List;
    while (temp != NULL) {
        printf("| %-5d | %-15s | %-10d | %-10.2f | %-10.2f |\n", 
               temp->family_id, temp->family_name, temp->no_of_users, 
               temp->family_income, temp->family_expense);
        temp = temp->next;
    }

    printf("----------------------------------------------------------\n");
}

// Display User List
void displayUsers(UserNode *Users_List) {
    if (Users_List == NULL) {
        printf("\nNo users recorded.\n");
        return;
    }

    printf("\nUser List:\n");
    printf("----------------------------------------------------------\n");
    printf("| %-5s | %-5s | %-15s | %-10s |\n", 
           "ID", "FamID", "User Name", "Income");
    printf("----------------------------------------------------------\n");

    UserNode *temp = Users_List;
    while (temp != NULL) {
        printf("| %-5d | %-5d | %-15s | %-10.2f |\n", 
               temp->user_id, temp->family_id, temp->user_name, 
               temp->user_income);
        temp = temp->next;
    }

    printf("----------------------------------------------------------\n");
}

// Display Expense List
void displayExpenses(ExpenseNode *Expenses_List) {
    if (Expenses_List == NULL) {
        printf("\nNo expenses recorded.\n");
        return;
    }

    printf("\nExpense List:\n");
    printf("--------------------------------------------------------------\n");
    printf("| %-5s | %-5s | %-10s | %-10s | %-5s |\n", 
           "ExpID", "UserID", "Category", "Amount (Rs.)", "Date");
    printf("--------------------------------------------------------------\n");

    ExpenseNode *temp = Expenses_List;
    while (temp != NULL) {
        printf("| %-5d | %-5d | %-10d | %-10.2f | %-5d |\n", 
               temp->expense_id, temp->user_id, temp->category, 
               temp->expense_amount, temp->date);
        temp = temp->next;
    }

    printf("--------------------------------------------------------------\n");
}

status_code UpdateFamilyDetails(FamNode *active_famNode)
{
    status_code sc = FAILURE;
    if (active_famNode != NULL)
    {
        printf("Enter new family name: ");
        scanf("%s", active_famNode->family_name);
        sc = SUCCESS;
        printf("Family details updated successfully.\n");
    }
    return sc;
}

status_code UpdateUserDetails(UserNode *active_userNode)
{
    status_code sc = FAILURE;
    if (active_userNode != NULL)
    {
        printf("Enter new username: ");
        scanf("%s", active_userNode->user_name);
        printf("Enter new income: ");
        scanf("%f", &active_userNode->user_income);
        sc = SUCCESS;
        printf("User details updated successfully.\n");
    }
    return sc;
}
// Function to update expense details (User can update only their own expenses)
status_code UpdateExpenseDetails(ExpenseNode **Exps_Listpptr, int user_id)
{
    status_code sc = FAILURE;
    int expense_id;
    printf("\nEnter Expense ID: ");
    scanf("%d",&expense_id);
    ExpenseNode *prev = NULL;
    ExpenseNode *expNode = SearchExpenseList(*Exps_Listpptr, &prev, expense_id);

    if (expNode == NULL)
    {
        printf("Expense with ID %d not found.\n", expense_id);
    }
    else
    {
        if (expNode->user_id != user_id)
        {
            printf("You can only update your own expenses.\n");
        }
        else
        {

            printf("Enter new expense category (0-4): ");
            scanf("%d", (int *)&expNode->category);
            printf("Enter new expense amount: ");
            scanf("%f", &expNode->expense_amount);
            sc = SUCCESS;
            printf("Expense details updated successfully.\n");
        }
    }

    return sc;
}



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
