#include<stdio.h>
#include<string.h>

#include "LinkedList.h"
#include "FamilyStructure.h"

#define NAME_MAX_SIZE 50

typedef enum {EXIT,FIRSTPAGE,SIGNUP,LOGIN,FAMILYHOME} Pagetype;

Pagetype FirstPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);
Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr,int* numOfFams_ptr,int* numofUSers_ptr);
status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income,int* numOfFams_ptr,int* numofUSers_ptr);

Pagetype LoginPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr,int* numOfFams_ptr,int* numofUsers_ptr);

int main()
{
    //Declaring LLists
    FamNode* Fams_List = NULL;
    UserNode* Users_List = NULL;
    ExpenseNode* Expenses_List = NULL;

    //Load data
    int numOfFams = 0;
    int numOfUsers = 0;
    int numOfExpenses = 0;

    int active_user_id = 0;
    int active_family_id = 0;

    Pagetype nextPage;
    nextPage = FirstPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
    printf("\nGoing to Page : %d ",nextPage);

    boolean exit = FALSE;

    while(!exit)
    {
         switch (nextPage)
        {
            case FIRSTPAGE:
                {
                    nextPage = FirstPage(&Fams_List,&Users_List, &active_user_id,&active_family_id);
                }

            case LOGIN: 
                {
                    nextPage = LoginPage(&Fams_List,&Users_List, &active_user_id,&active_family_id,&numOfFams,&numOfUsers);
                }
                break;
            
            case SIGNUP: 
                {
                    nextPage = SignUpPage(&Fams_List,&Users_List, &active_user_id,&active_family_id,&numOfFams,&numOfUsers);
                }
                break;
            
            case FAMILYHOME:
                {
                    printf("\nGoing to FAMILY HOME PAGE!");
                }

            default: exit = TRUE;
                break;
        }
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

Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr,int* numOfFams_ptr,int* numofUsers_ptr)
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

    status_code sc = CreateFamily(Fams_Listpptr,Users_Listpptr, active_userid_ptr,active_familyid_ptr,fam_name,user_name,user_income,numOfFams_ptr,numofUsers_ptr);

    if(sc)
    {
        printf("Family Created Successfully with 1 member.");
        printf("Please use below credentials to login");
        printf("\n\tFamily ID = %d\n\tUser ID = %d",(*Fams_Listpptr)->family_id,(*Users_Listpptr)->user_id);
        ret_page = LOGIN;
    }
    else
    {
        printf("\nFamily Creation Unsuccessful! Please try Again.");
    }
    return ret_page;
}

status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income,int* numOfFams_ptr,int* numofUsers_ptr)
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
            newFamNode_ptr->family_id =  ++(*numOfFams_ptr);
            newFamNode_ptr->family_name = fam_name;

            newUserNode_ptr->user_id = ++(*numofUsers_ptr) ;
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
                newFamNode_ptr->no_of_users++;

                *active_familyid_ptr = newFamNode_ptr->family_id;
                *active_userid_ptr = newUserNode_ptr->user_id;

            }
            else
            {
                //free user node
                //free family node
                //remove from all lists
            }
        }
        else
        {
            printf("\nMemory Allocation Error for User Node!");
            // free family node
        }
    }
    return sc;
}

Pagetype LoginPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr,int* numOfFams_ptr,int* numofUsers_ptr)
{
    Pagetype ret_page = FIRSTPAGE;

    status_code authentication = FAILURE;
    FamNode* curr_FamNode_ptr;
    UserNode* curr_UserNode_ptr;

    int family_id;
    int user_id;
    char user_name[NAME_MAX_SIZE];

    printf("\nWelcome, \nPlease enter valid details to log in\n");

    printf("\nPlease enter new Family Id : ");
    scanf("%d",&family_id);
    
    printf("\nPlease enter new User Id : ");
    scanf("%d",&user_id);

    printf("\nPlease enter User name : ");
    getchar();
    scanf("%[^\n]s",user_name);

    printf("\nSearching Family");
    curr_FamNode_ptr = SearchFamList(*Fams_Listpptr,family_id);
    if(curr_FamNode_ptr != NULL)
    {
        curr_UserNode_ptr = SearchUserList(*Users_Listpptr,user_id);
        if(curr_UserNode_ptr != NULL /*&& curr_UserNode_ptr->user_name == user_name*/ )
        {
            authentication = SUCCESS;
            printf("\nFamily User Login Successful!\nLoading FamilyHomePage...");
            ret_page = FAMILYHOME;
        }
        else
        {
            printf("\nFamily User Login NOT Successful!\nLoading Page...");
            ret_page = LOGIN;
        }
    }
    else
    {
        printf("\nFamily not found!");
    }
    return ret_page;
}