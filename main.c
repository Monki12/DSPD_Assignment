
#include<stdio.h>
#include<string.h>

#include "LinkedList.h"
#include "FamilyStructure.h"

typedef enum {EXIT,FIRSTPAGE,SIGNUP,LOGIN} Pagetype;

Pagetype FirstPage(Node** Fams_Listpptr,Node** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);

int main()
{
    //Declaring LLists
    Node* Fams_List;
    Node* Users_List;
    Node* Expenses_List;
    
    //Initialize Lists
    initList(&Fams_List);
    initList(&Users_List);
    initList(&Expenses_List);

    //Call Method to Load Data from files
    int active_user_id;
    int active_family_id;
    
    Pagetype nextPage;
    nextPage = FirstPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
    
    printf("\nGoing to Page : %d ",nextPage);

    return 0;
}

Pagetype FirstPage(Node** Fams_Listpptr,Node** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr)
{
    printf("\nWelcome to the First Page of Family Expense Tracker App\n");
    
    Pagetype ret_page;
    int choice;
    printf("\nPlease choose an option from the menu:");
    printf("\n\t1.Login - to an exsisting user account");
    printf("\n\t2.SignUp - Create a new Family");
    printf("\n\t3.Exit - Halt Program\n");

    scanf("%d",&choice);

    switch(choice)
    {
        case 1: ret_page = LOGIN;
                break;
        case 2: ret_page = SIGNUP;
                break;
        case 3: ret_page = EXIT; 
                break; 
        default: printf("\nInvalid Input, Please Try Again...");
                ret_page = FirstPage(Fams_Listpptr,Users_Listpptr, active_userid_ptr,active_familyid_ptr);
    }
    
    return ret_page;
}