#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include<stdio.h>

typedef enum {FALSE,TRUE} boolean;

typedef enum {FAILURE,SUCCESS} status_code;

//typedef enum {FAMILY,USER,EXPENSE} NodeType;

typedef enum {RENT,UTILITY,GROCERY,STATIONARY,LEISURE} Categorytype;

// typedef union Node_tag{
//     FamNode fn;
//     UserNode un;
//     ExpenseNode en;
// } Node;

//redefine structure variables in descending order of space occupied
typedef struct UserNode_tag
{
    int user_id;
    int family_id;
    char* user_name;
    float user_income;
    struct UserNode_tag* next;
} UserNode;

typedef struct FamNode_tag
{
    int family_id;
    int no_of_users;
    char* family_name;
    float family_income;
    float family_expense;
    UserNode* family_members_ptr;

    struct FamNode_tag* next;
} FamNode;

typedef struct ExpenseNode_tag
{
    int expense_id;
    int user_id;
    Categorytype category; 
    float expense_amount;
    int date; //as only 10 days in a month

    struct ExpenseNode_tag* next;
} ExpenseNode;

void initFamNode(FamNode* lpptr);
void initUserNode(UserNode* lpptr);
void initExpenseNode(ExpenseNode* lpptr);

FamNode* CreateFamNode();
UserNode* CreateUserNode();
ExpenseNode* CreateNode(void* data_ptr);

status_code InsertAfter_Fam(FamNode** lpptr, FamNode* prev_ptr, FamNode* nptr);
status_code InsertAfter_User(UserNode** lpptr, UserNode* prev_ptr, UserNode* nptr);
status_code InsertAfter_Expense(ExpenseNode** lpptr, ExpenseNode* prev_ptr, ExpenseNode* nptr);




#endif