
#include<stdio.h>
#include<string.h>

#include "LinkedList.h"
#include "FamilyStructure.h"

#define NAME_MAX_SIZE 50

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

    //Defining and Initializing 
    int active_user_id = 0;
    int active_family_id = 0;
    
    Pagetype nextPage;
    nextPage = FirstPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
    
    printf("\nGoing to Page : %d ",nextPage);

    switch (nextPage)
    {
    case LOGIN: 
        {
            //nextPage = LoginPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
        }
        break;
    
    case SIGNUP: 
        {
            nextPage = SignUpPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
        }
        break;
    
    default:
        break;
    }

    printf("\nExiting App. . .");
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

Pagetype SignUpPage(Node** Fams_Listpptr,Node** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr)
{
    Pagetype ret_page;

    char fam_name[NAME_MAX_SIZE];
    char user_name[NAME_MAX_SIZE];
    float user_income = 0.0;

    printf("\nWelcome, \nPlease enter valid details to sign up\n");

    printf("\nPlease enter new Family name : ");
    scanf("%[^\n]s",fam_name);
    
    printf("\nPlease enter new User name : ");
    scanf("%[^\n]s",user_name);

    printf("\nPlease enter user income : ");
    scanf("%f",&user_income);

    //Family* newfamdata_ptr = CreateFamilyStruct(fam_name,user_name,user_income);
    //status_code sc = AddFamtoList(Fams_Listpptr,Users_Listpptr,newfamdata_ptr)

    //status_code sc = CreateFamily(all parameters)

    Pagetype ret_page;
}
