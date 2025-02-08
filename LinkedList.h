#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define FAM_MAX_SIZE 4
#define NAME_MAX_SIZE 50

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

typedef struct ExpenseNode_tag
{
    int expense_id;
    int user_id;
    Categorytype category; 
    float expense_amount;
    int date; //as only 10 days in a month

    struct ExpenseNode_tag* next;
} ExpenseNode;

typedef struct UserNode_tag
{
    int user_id;
    int family_id;
    char user_name[NAME_MAX_SIZE];
    float user_income;
    float category_expense[5];
    struct UserNode_tag* next;
} UserNode;

typedef struct FamNode_tag
{
    int family_id;
    int no_of_users;
    char family_name[NAME_MAX_SIZE];
    float family_income;
    float family_expense;
    UserNode* family_members_ptr[FAM_MAX_SIZE];

    struct FamNode_tag* next;
} FamNode;

void initFamNode(FamNode* lpptr);
void initUserNode(UserNode* lpptr);
void initExpenseNode(ExpenseNode* lpptr);

FamNode* CreateFamNode();
UserNode* CreateUserNode();
ExpenseNode* CreateExpenseNode();

status_code InsertAfter_Fam(FamNode** lpptr, FamNode* prev_ptr, FamNode* nptr);
status_code InsertAfter_User(UserNode** lpptr, UserNode* prev_ptr, UserNode* nptr);
status_code InsertAfter_Expense(ExpenseNode** lpptr, ExpenseNode* prev_ptr, ExpenseNode* nptr);

FamNode* SearchFamList(FamNode* lptr,FamNode** prev_ptr,int id);
UserNode* SearchUserList(UserNode* lptr,UserNode** prev_ptr,int id);
ExpenseNode* SearchExpenseList(ExpenseNode* lptr,ExpenseNode** prev_ptr,int id);

status_code DeleteAfter_Fam(FamNode** lpptr, FamNode* prev_ptr, FamNode* nptr);
status_code DeleteAfter_User(UserNode** lpptr, UserNode* prev_ptr, UserNode* nptr);
status_code DeleteAfter_Exp(ExpenseNode** lpptr, ExpenseNode* prev_ptr, ExpenseNode* nptr);


#endif