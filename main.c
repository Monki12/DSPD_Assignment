
#include<stdio.h>
#include<string.h>

#include "LinkedList.h"
#include "FamilyStructure.h"

#define NAME_MAX_SIZE 50

typedef enum {EXIT,FIRSTPAGE,SIGNUP,LOGIN} Pagetype;

Pagetype FirstPage(Node** Fams_Listpptr,Node** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);
Pagetype SignUpPage(Node** Fams_Listpptr,Node** Users_Listpptr,int* active_userid_ptr,int* active_familyid_ptr);


Node* Create_and_AddUser(Node** User_Listpptr, int* active_familyid_ptr, int* active_userid_ptr, char* user_name,float user_income);
status_code CreateFamily(Node** Fams_Listpptr, Node** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income );



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

    //Family* newfamdata_ptr = CreateFamilyStruct(fam_name,user_name,user_income);
    //status_code sc = AddFamtoList(Fams_Listpptr,Users_Listpptr,newfamdata_ptr)

    //status_code sc = CreateFamily(all parameters)
    status_code sc = CreateFamily(Fams_Listpptr,Users_Listpptr, active_userid_ptr,active_familyid_ptr,fam_name,user_name,user_income);

    if(sc)
    {
        printf("Created new family and user successfully");
        Family* fptr =(*Fams_Listpptr)->data_ptr;
        printf("\n%s - %d  vs  %d",fptr->family_name,fptr->family_id, *active_familyid_ptr);

        Family* fam_data = NULL;
        // Print Family List if it's not empty
        if (*Fams_Listpptr != NULL) {
            printf("\nFamily List:\n");
            printTypeList(*Fams_Listpptr, FAMILY);
            fam_data = (*Fams_Listpptr)->data_ptr;
        } else {
            printf("\nFamily List is empty.\n");
        }

        // Print User List if it's not empty
        if (*Users_Listpptr != NULL) {
            printf("\nUser List:\n");
            printTypeList(*Users_Listpptr, USER);
        } else {
            printf("\nUser List is empty.\n");
        }
        
        // Print Family Members List if it's not empty
        if (fam_data != NULL && fam_data->family_members_ptr != NULL) {
            printf("\nFamily Members List:\n");
            printTypeList(fam_data->family_members_ptr, USER);
        } else {
            printf("\nFamily Members List is empty.\n");
        }

    }

    return ret_page;
}

status_code CreateFamily(Node** Fams_Listpptr, Node** Users_Listpptr, int* active_userid_ptr, int* active_familyid_ptr, char* fam_name , char* user_name , float user_income )
{
    //get newFamdata_ptr for data_ptr
    //create fam node and  values
    status_code sc = FAILURE;
    Family* newFamData_ptr = (Family*)malloc(sizeof(Family));

    Node* newFamNode = NULL;
    Node* newUserNode = NULL;

    if(newFamData_ptr != NULL)
    {
        printf("\n\tMemory Allocated for new Family...");
        newFamData_ptr->family_id = 1;//find a way
        printf("Reached string...");
        newFamData_ptr->family_name = fam_name;
        printf("Family name is %s",newFamData_ptr->family_name);
        newFamData_ptr->family_income=0.0;
        newFamData_ptr->family_expense=0.0;
        newFamData_ptr->no_of_users = 0;
        newFamData_ptr->family_members_ptr = NULL;

        newFamNode = CreateNode(newFamData_ptr);//add null case condn
        if(newFamNode == NULL)
        {
            printf("\nFailed to create new Family Node");
        }
        else
        {
            printf("\n\tNew Family node is ready...");
            sc = InsertAfter(Fams_Listpptr,NULL,newFamNode);
            if(sc == FAILURE)
            {
                printf("\nFailed to insert Family node to List");
            }
            //new Family Node initialized and inserted

            //get newUserdata_ptr for data_ptr
            //create user node and assign values 
            //Add new user to family member list

            if(sc != FAILURE)
            {
                newUserNode = Create_and_AddUser(Users_Listpptr,active_userid_ptr,active_familyid_ptr,user_name,user_income);
                if(newUserNode != NULL)
                {
                    printf("\n\tAdding user to family...");
                    sc = InsertAfter(&(newFamData_ptr->family_members_ptr), NULL, newUserNode);
                    newFamData_ptr->no_of_users++;
                    if(sc == FAILURE)
                    {
                        printf("\nFailed to insert User node to member List");
                    }
                }
                else
                {
                    sc = FAILURE;
                }
            }
        }
    }
     else
    {
        printf("\nMemory Allocation Error!");
    }

    if(newFamNode != NULL)
    {
        *active_familyid_ptr = newFamData_ptr->family_id;
    }

    return sc;
}

Node* Create_and_AddUser(Node** User_Listpptr, int* active_familyid_ptr, int* active_userid_ptr, char* user_name,float user_income)
{
    Node* newUserNode = NULL;
    status_code sc;
    User* newUserData_ptr = (User*)malloc(sizeof(User));

    if(newUserData_ptr != NULL)
    {
        newUserData_ptr->family_id = *active_familyid_ptr;
        newUserData_ptr->user_id = 1; //find a way
        printf("Reached string2...");
        newUserData_ptr->user_name = user_name;
        printf("Family name is %s",newUserData_ptr->user_name);
        newUserData_ptr->user_income = user_income;

        newUserNode = CreateNode(newUserData_ptr);
        if(newUserNode == NULL )
        {
            printf("Failed to create User Node!");
        }
        else
        {
            sc = InsertAfter(User_Listpptr,NULL,newUserNode);
            if(sc == FAILURE)
            {
                printf("Failed to insert new user to userList");
                newUserNode = NULL;
            }
        }

    }
    else
    {
        printf("\nMemory Allocation Error!");
    }

    if(newUserNode !=  NULL)
    {
        *active_userid_ptr = newUserData_ptr->user_id;
    }

    return newUserNode;
}

