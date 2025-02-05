#ifndef FAMILYSTRUCTURE_H
#define FAMILYSTRUCTURE_H

typedef struct Node_tag Node;//fwd declaration to deal with circular dependency

typedef enum {FALSE,TRUE} boolean;

typedef enum {RENT,UTILITY,GROCERY,STATIONARY,LEISURE} Categorytype;

//redefine structure variables in descending order of space occupied
typedef struct Family_tag
{
    int family_id;
    int no_of_users;
    char* family_name;
    float family_income;
    float family_expense;
    Node* family_members_ptr;
} Family;

typedef struct User_tag
{
    int user_id;
    int family_id;
    char* user_name;
    float user_income;
} User;

typedef struct Expense_tag
{
    int expense_id;
    int user_id;
    Categorytype category; 
    float expense_amount;
    int date; //as only 10 days in a month
} Expense;

#endif