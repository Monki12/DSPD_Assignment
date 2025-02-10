#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FAM_MAX_SIZE 4
#define NAME_MAX_SIZE 50
#define MAX_FAMILIES 100
#define MAX_USERS 1000
#define MAX_EXPENSES 1000
#define MAX_ID 1000

typedef enum
{
    FALSE,
    TRUE
} boolean;

typedef enum
{
    FAILURE,
    SUCCESS
} status_code;

// typedef enum {FAMILY,USER,EXPENSE} NodeType;

typedef enum
{
    RENT,
    UTILITY,
    GROCERY,
    STATIONARY,
    LEISURE
} Categorytype;

// !redefine structure variables in descending order of space occupied
typedef struct ExpenseNode_tag
{
    float expense_amount;
    int expense_id;
    int user_id;
    int date;
    Categorytype category;

    struct ExpenseNode_tag *next;
} ExpenseNode;

typedef struct UserNode_tag
{
    float user_income;
    float category_expense[5];

    int user_id;
    int family_id;

    char user_name[NAME_MAX_SIZE];

    struct UserNode_tag *next;
} UserNode;

typedef struct FamNode_tag
{
    float family_income;
    float family_expense;

    int family_id;
    int no_of_users;

    char family_name[NAME_MAX_SIZE];

    UserNode *family_members_ptr[FAM_MAX_SIZE];

    struct FamNode_tag *next;
} FamNode;

void initFamNode(FamNode *lpptr);
void initUserNode(UserNode *lpptr);
void initExpenseNode(ExpenseNode *lpptr);

FamNode *CreateFamNode();
UserNode *CreateUserNode();
ExpenseNode *CreateExpenseNode();

status_code InsertAfter_Fam(FamNode **lpptr, FamNode *prev_ptr, FamNode *nptr);
status_code InsertAfter_User(UserNode **lpptr, UserNode *prev_ptr, UserNode *nptr);
status_code InsertAfter_Expense(ExpenseNode **lpptr, ExpenseNode *prev_ptr, ExpenseNode *nptr);

FamNode *SearchFamList(FamNode *lptr, FamNode **prev_ptr, int id);
UserNode *SearchUserList(UserNode *lptr, UserNode **prev_ptr, int id);
ExpenseNode *SearchExpenseList(ExpenseNode *lptr, ExpenseNode **prev_ptr, int id);

status_code DeleteAfter_Fam(FamNode **lpptr, FamNode *prev_ptr, FamNode *nptr);
status_code DeleteAfter_User(UserNode **lpptr, UserNode *prev_ptr, UserNode *nptr);
status_code DeleteAfter_Exp(ExpenseNode **lpptr, ExpenseNode *prev_ptr, ExpenseNode *nptr);

// Family List Sorting
void mergeSortFamilies(FamNode **headRef);
FamNode *mergeSortedFamilies(FamNode *a, FamNode *b);
void splitFamilyList(FamNode *source, FamNode **front, FamNode **back);

// User List Sorting
void mergeSortUsers(UserNode **headRef);
UserNode *mergeSortedUsers(UserNode *a, UserNode *b);
void splitUserList(UserNode *source, UserNode **front, UserNode **back);

// Expense List Sorting (Sort by user_id first, then expense_id)
void mergeSortExpenses(ExpenseNode **headRef);
ExpenseNode *mergeSortedExpenses(ExpenseNode *a, ExpenseNode *b);
void splitExpenseList(ExpenseNode *source, ExpenseNode **front, ExpenseNode **back);

// Display Family List
void displayFamilies(FamNode *Fams_List);
// Display User List
void displayUsers(UserNode *Users_List);
// Display Expense List
void displayExpenses(ExpenseNode *Expenses_List);

status_code UpdateFamilyDetails(FamNode *active_famNode);
status_code UpdateUserDetails(UserNode *active_userNode);
status_code UpdateExpenseDetails(ExpenseNode **Exps_Listpptr, int user_id);
#endif