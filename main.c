#include<stdio.h>
#include<string.h>

#include "LinkedList.h"
#include "FamilyStructure.h"

#define NAME_MAX_SIZE 50

typedef enum {EXIT,FIRSTPAGE,SIGNUP,LOGIN} Pagetype;

Pagetype FirstPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);
Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);
status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income );

int main()
{
    //Declaring LLists
    FamNode* Fams_List = NULL;
    UserNode* Users_List = NULL;
    ExpenseNode* Expenses_List = NULL;

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

Pagetype FirstPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr)
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

Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr)
{
    Pagetype ret_page = FIRSTPAGE;

    char fam_name[NAME_MAX_SIZE];
    char user_name[NAME_MAX_SIZE];
    float user_income = 0.0;

    printf("\nWelcome, \nPlease enter valid details to sign up\n");

    printf("\nPlease enter new Family name : ");
    getchar();
    scanf("%[^\n]s",fam_name);
    
    printf("\nPlease enter new User name : ");
    getchar();
    scanf("%[^\n]s",user_name);

    printf("\nPlease enter user income : ");
    scanf("%f",&user_income);

    status_code sc = CreateFamily(Fams_Listpptr,Users_Listpptr, active_userid_ptr,active_familyid_ptr,fam_name,user_name,user_income);

    if(sc)
    {
        printf("Family Created Successfully with 1 member.");
        printf("\n\tFamily ID = %d\n\tUser ID=%d",(*Fams_Listpptr)->family_id,(*Users_Listpptr)->user_id);
    }
}

status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income )
{
    status_code sc = FAILURE;
    status_code InsertedUser;
    status_code InsertedFamily;
    status_code InsertedUserAsMember;
    //Create FamNode
    FamNode* newFamNode_ptr = CreateFamNode();

    if(newFamNode_ptr != NULL)
    {
        UserNode* newUserNode_ptr = CreateUserNode(); 

        if(newUserNode_ptr != NULL)
        {
            newUserNode_ptr->user_id = 1;
            newUserNode_ptr->user_name = user_name;
            newUserNode_ptr->user_income = user_income;
            newUserNode_ptr->family_id = newFamNode_ptr->family_id;

            //adding user to userList
            InsertedUserAsMember = InsertAfter_User(&(newFamNode_ptr->family_members_ptr), NULL , newUserNode_ptr);
            InsertedUser = InsertAfter_User(Users_Listpptr,NULL,newUserNode_ptr);
            InsertedFamily = InsertAfter_Fam(Fams_Listpptr,NULL,newFamNode_ptr);

            if(InsertedFamily && InsertedUser && InsertedUserAsMember)
            {
                sc = SUCCESS;
                *active_familyid_ptr = newFamNode_ptr->family_id;
                *active_userid_ptr = newUserNode_ptr->user_id;
            }
        }
    }
    return sc;
}