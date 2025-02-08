#include "LinkedList.h"



typedef enum {EXIT,FIRSTPAGE,SIGNUP,LOGIN,FAMILYHOME} Pagetype;

Pagetype FirstPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr);
Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* numOfFams_ptr,int* numofUSers_ptr);
status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, char* fam_name , char* user_name , float user_income,int* numOfFams_ptr,int* numofUSers_ptr);
Pagetype LoginPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,UserNode** active_userNode_ptr,FamNode** active_famNode_ptr,int* numOfFams_ptr,int* numofUsers_ptr);
Pagetype FamilyHomePage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,ExpenseNode** Exps_Listpptr,UserNode* active_userNode_ptr,FamNode* active_famNode_ptr,int* numOfFams_ptr,int* numofUsers_ptr, int* numOfExp_ptr);
status_code AddUser(UserNode** User_Listpptr,UserNode** FamMember_Listpptr, UserNode* newUserNode,FamNode* active_famNode_ptr,int* numOfUsers);
status_code AddExpense(ExpenseNode** Exp_Listpptr,ExpenseNode* newExpNode,UserNode* active_userNode_ptr,int* numOfExp_ptr);
void CalculateTotalExpense(ExpenseNode* Exps_Listptr, FamNode* active_famNode_ptr, UserNode* Users_Listptr);
void Get_categorical_expense(ExpenseNode* Exps_Listptr, UserNode* Users_Listptr, FamNode* active_famNode_ptr, Categorytype category);
void AddUsertoFamily(FamNode* active_fam_ptr, UserNode* newUser_ptr);

void mergeSort(UserNode** userArray, int left, int right, int category);
void merge(UserNode** userArray, int left, int mid, int right, int category);



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

    UserNode* active_userNode_ptr = NULL;
    FamNode* active_famNode_ptr = NULL;

    Pagetype nextPage;
    nextPage = FirstPage(&Fams_List,&Users_List);
    printf("\nGoing to Page : %d ",nextPage);

    boolean exit = FALSE;

    while(!exit)
    {
         switch (nextPage)
        {
            case FIRSTPAGE:
                {
                    nextPage = FirstPage(&Fams_List,&Users_List);
                } break;

            case LOGIN: 
                {
                    nextPage = LoginPage(&Fams_List,&Users_List, &active_userNode_ptr,&active_famNode_ptr,&numOfFams,&numOfUsers);
                }
                break;
            
            case SIGNUP: 
                {
                    nextPage = SignUpPage(&Fams_List,&Users_List,&numOfFams,&numOfUsers);
                }
                break;
            
            case FAMILYHOME:
                {
                    printf("\nGoing to FAMILY HOME PAGE!");
                    nextPage = FamilyHomePage(&Fams_List,&Users_List,&Expenses_List, active_userNode_ptr,active_famNode_ptr,&numOfFams,&numOfUsers,&numOfExpenses);
                } 
                break;

            default: exit = TRUE;
                
        }
    }
       

    printf("\nExiting App. . .");
    //save all current info in file

    return 0;
}

Pagetype FirstPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr)
{
    printf("\n\nWelcome to the First Page of Family Expense Tracker App\n");
    
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
                ret_page = FIRSTPAGE;
    }
    
    return ret_page;
}

Pagetype SignUpPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,int* numOfFams_ptr,int* numofUsers_ptr)
{
    Pagetype ret_page = FIRSTPAGE;

    char fam_name[NAME_MAX_SIZE];
    char user_name[NAME_MAX_SIZE];
    float user_income = 0.0;

    printf("\nWelcome to Sign Up Page, \nPlease enter valid details to sign up\n");

    printf("\nPlease enter new Family name : ");
    getchar();
    scanf("%[^\n]s",fam_name);
    
    printf("\nPlease enter new User name : ");
    getchar();
    scanf("%[^\n]s",user_name);

    printf("\nPlease enter user income : ");
    scanf("%f",&user_income);

    status_code sc = CreateFamily(Fams_Listpptr,Users_Listpptr,fam_name,user_name,user_income,numOfFams_ptr,numofUsers_ptr);

    if(sc)
    {
        printf("\nFamily Created Successfully with 1 member.");
        printf("\nPlease use below credentials to login :");
        printf("\n\tFamily ID = %d\n\tUser ID = %d",(*Fams_Listpptr)->family_id,(*Users_Listpptr)->user_id);
        ret_page = FIRSTPAGE;
    }
    else
    {
        printf("\nFamily Creation Unsuccessful! Please try Again.");
    }
    return ret_page;
}

//family total income needs to be calculated at the time of family creation
status_code CreateFamily(FamNode** Fams_Listpptr,UserNode** Users_Listpptr, char* fam_name , char* user_name , float user_income,int* numOfFams_ptr,int* numofUsers_ptr)
{
    status_code sc = FAILURE;
    status_code InsertedUser;
    status_code InsertedFamily;
    //Create FamNode
    FamNode* newFamNode_ptr = CreateFamNode();

    if(newFamNode_ptr != NULL)
    {
        UserNode* newUserNode_ptr = CreateUserNode(); 

        if(newUserNode_ptr != NULL)
        {
            newFamNode_ptr->family_id =  ++(*numOfFams_ptr);
            strcpy(newFamNode_ptr->family_name,fam_name);

            newUserNode_ptr->user_id = ++(*numofUsers_ptr) ;
            strcpy(newUserNode_ptr->user_name,user_name);
            newUserNode_ptr->user_income = user_income;
            newUserNode_ptr->family_id = newFamNode_ptr->family_id;

            //adding user to userList
            InsertedUser = InsertAfter_User(Users_Listpptr,NULL,newUserNode_ptr);
            InsertedFamily = InsertAfter_Fam(Fams_Listpptr,NULL,newFamNode_ptr);

            if(InsertedFamily && InsertedUser)
            {
                sc = SUCCESS;
                AddUsertoFamily(newFamNode_ptr,newUserNode_ptr);
                newFamNode_ptr->no_of_users++;
                //calculate total family income
                newFamNode_ptr->family_income = user_income;
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

Pagetype LoginPage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,UserNode** active_userNode_pptr,FamNode** active_famNode_pptr,int* numOfFams_ptr,int* numofUsers_ptr)
{
    Pagetype ret_page = FIRSTPAGE;

    status_code authentication = FAILURE;
    FamNode* curr_FamNode_ptr;
    UserNode* curr_UserNode_ptr;

    int family_id;
    int user_id;
    char user_name[NAME_MAX_SIZE];

    printf("\n\nWelcome to Login Page, \nPlease enter valid details to log in\n");

    printf("\nPlease enter Family Id : ");
    scanf("%d",&family_id);
    
    printf("\nPlease enter User Id : ");
    scanf("%d",&user_id);

    printf("\nPlease enter User name : ");
    getchar();
    scanf("%[^\n]s",user_name);// can use fgets(user_name,MAX_NAME_SIZE,stdin)

    //Search User list
    //creating dummy prev pointers
    FamNode* dummyFam = NULL;
    UserNode* dummyUser =NULL;

    curr_UserNode_ptr = SearchUserList(*Users_Listpptr,&dummyUser,user_id);
    if(curr_UserNode_ptr != NULL)
    {
        if(user_id == curr_UserNode_ptr->user_id && family_id == curr_UserNode_ptr->family_id)
        {
            curr_FamNode_ptr = SearchFamList(*Fams_Listpptr,&dummyFam,family_id);
            if(curr_FamNode_ptr != NULL)
            {
                authentication = SUCCESS;
                printf("\nFamily User Login Successful!\nLoading FamilyHomePage...");
                *active_famNode_pptr = curr_FamNode_ptr;
                *active_userNode_pptr = curr_UserNode_ptr;
                ret_page = FAMILYHOME;
            }
            else
            {
                printf("\nFamily not found. Error!");
                printf("\nFamily User Login NOT Successful!\nLoading Page...");
                //ret_page = LOGIN;
            }
        }
        else
        {
            printf("\nFamily ID and User ID mismatch!");
            printf("\nFamily User Login NOT Successful!\nLoading Page...");
            //ret_page = LOGIN;
        }
    }
    else
    {
        printf("\nFamily User Login NOT Successful!\nLoading Page...");
        //ret_page = LOGIN;
    }

    return ret_page;
}

Pagetype FamilyHomePage(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,ExpenseNode** Exps_Listpptr,UserNode* active_userNode_ptr,FamNode* active_famNode_ptr,int* numOfFams_ptr,int* numofUsers_ptr, int* numOfExp_ptr)
{
    Pagetype ret_page = FIRSTPAGE;
    if(active_famNode_ptr != NULL && active_userNode_ptr != NULL)
    {
        boolean logout = FALSE;
        while(!logout)
        {
            printf("\n\nWelcome to the %s Family's Home Page\n", active_famNode_ptr->family_name);
            printf("\nFamily ID - %d", active_famNode_ptr->family_id);

            int choice;

            printf("\nPlease choose an option from the menu:");

            // --- VIEWING OPTIONS ---
            printf("\n\n--- View Information ---");
            printf("\n\t1. View Total Monthly Income");
            printf("\n\t2. View Total Monthly Expense");
            printf("\n\t3. View User Expenses");
            printf("\n\t4. Get Total Categorical Expense");
            printf("\n\t5. Get Highest Expense Day");
            printf("\n\t6. View Family Details");
            printf("\n\t7. View User Details");

            // --- DATA MANAGEMENT OPTIONS ---
            printf("\n\n--- Manage Data ---");
            printf("\n\t8. Add Expense");
            printf("\n\t9. Add New User");
            printf("\n\t10. Update User or Family Details");

            // --- DELETE OPTIONS ---
            printf("\n\n--- Delete Data ---");
            printf("\n\t11. Delete Expense");
            printf("\n\t12. Delete User");
            printf("\n\t13. Delete Family");

            // --- OTHER OPTIONS ---
            printf("\n\n--- Other ---");
            printf("\n\t14. Log Out\n");

            scanf("%d", &choice);

            switch (choice)
            {
                // --- VIEWING OPTIONS ---
                case 1:
                    printf("\nTotal Family Monthly Income = Rs.%0.2f", active_famNode_ptr->family_income);
                    break;

                case 2:
                    //void CalculateTotalExpense(Exps_Listpptr,active_famNode_ptr);
                    CalculateTotalExpense(*Exps_Listpptr,active_famNode_ptr,*Users_Listpptr);
                    break;

                case 3:
                    // Search and display user-specific expenses in a tabular format
                    printf("\nDisplaying Expenses for User ID: %d\n", active_userNode_ptr->user_id);
                    printf("----------------------------------------------------\n");
                    printf("| %-10s | %-10s | %-12s | %-10s |\n", "Exp. ID", "Category", "Amount (Rs.)", "Date");
                    printf("----------------------------------------------------\n");
                
                    ExpenseNode* temp = *Exps_Listpptr;
                    int found = 0;
                    float total_expense = 0.0;
                
                    while (temp != NULL) {
                        if (temp->user_id == active_userNode_ptr->user_id) {
                            found = 1;
                            printf("| %-10d | %-10d | %-12.2f | %-10d |\n", 
                                temp->expense_id, temp->category, temp->expense_amount, temp->date);
                            total_expense += temp->expense_amount;
                        }
                        temp = temp->next;
                    }
                
                    if (!found) {
                        printf("| %-44s |\n", "No expenses found.");
                    }
                
                    printf("----------------------------------------------------\n");
                    printf("Total User Expense: Rs. %.2f\n", total_expense);
                    printf("----------------------------------------------------\n");
                    break;
                
                    // void DisplayUserExpenses(Exps_pptr,active_userNode_ptr)
                    break;

                case 4:
                    printf("\nSelect Expense Category (0: RENT, 1: UTILITY, 2: GROCERY, 3: STATIONARY, 4: LEISURE): ");
                    Categorytype category_input;
                    Get_categorical_expense(*Exps_Listpptr,*Users_Listpptr,active_famNode_ptr,category_input);

                    // Display expense categories and corresponding totals
                    // void CAtegoricalExpense
                    break;

                case 5:
                    printf("\nFinding the day with the highest expenses...");
                    // Identify and display the highest spending day
                    break;

                case 6:
                    printf("\nFamily Details:");
                    printf("\nFamily ID: %d", active_famNode_ptr->family_id);
                    printf("\nFamily Name: %s", active_famNode_ptr->family_name);
                    printf("\nNumber of Members: %d", active_famNode_ptr->no_of_users);
                    break;

                case 7:
                    printf("\nUser Details:");
                    printf("\nUser ID: %d", active_userNode_ptr->user_id);
                    printf("\nUser Name: %s", active_userNode_ptr->user_name);
                    printf("\nUser Income: Rs.%0.2f", active_userNode_ptr->user_income);
                    break;

                // --- DATA MANAGEMENT OPTIONS ---
                case 8:
                    // Gather details and add an expense to the list
                    {
                        ExpenseNode* newExp = CreateExpenseNode();
                        status_code sc = AddExpense(Exps_Listpptr,newExp,active_userNode_ptr,numOfExp_ptr);
                        if(sc == SUCCESS)
                        {
                            printf("\nNew Expense added!");
                        }
                        else
                        {
                            printf("\nError occured while adding new expense.\nGoing back to Family Home Page...");
                        }
                    }

                    break;

                case 9:
                {
                    UserNode* newUser = CreateUserNode();
                    status_code sc = AddUser(Users_Listpptr,active_famNode_ptr->family_members_ptr,newUser,active_famNode_ptr,numofUsers_ptr);
                    if(sc == SUCCESS)
                    {
                        printf("\nNew User added!");
                        printf("\nNew User ID = %d",newUser->user_id);
                    }
                    else
                    {
                        printf("\nError occured while adding new User6.\nGoing back to Family Home Page...");
                    }
                }
                    // Create a new user, collect details, and add to user and family lists
                    break;

                case 10:
                    printf("\nUpdating user or family details...");
                    // Allow changes to names, incomes, etc.
                    break;

                // --- DELETE OPTIONS ---
                case 11:
                    printf("\nEnter Expense ID to delete: ");
                    int expID;
                    scanf("%d",&expID);

                    status_code sc = FAILURE;
                    ExpenseNode* prev_Exp_ptr = NULL;
                    ExpenseNode* Exp_ptr = SearchExpenseList(*Exps_Listpptr,&prev_Exp_ptr,expID);
                    if(Exp_ptr != NULL && Exp_ptr->user_id == active_userNode_ptr->user_id)
                    {
                        printf("\nExpense found. Deleting Expense...");
                        Categorytype category = Exp_ptr->category;
                        float amount = Exp_ptr->expense_amount;
                        sc = DeleteAfter_Exp(Exps_Listpptr,prev_Exp_ptr,Exp_ptr);
                        if(sc == SUCCESS)
                        {
                            //delete from user category expense
                            active_userNode_ptr->category_expense[category]-=amount;
                            //delete from family total expense -- managed by function
                        }
                    }
                    else
                    {
                        printf("\nExpense not found. Returning to FamilyHomepage...");
                    }
                    // Get input, find expense, and remove it from the list

                    break;

                case 12:
                    printf("\nEnter User ID to delete: ");
                    int userID;
                    scanf("%d",&userID);
                    //check if userID == Active...if so return to Homepage
                    //check if user is the last user, if so Delete FAmily too
                    if (userID == active_userNode_ptr->user_id)
                    {
                        printf("\nDo you want to Delete Current user? (Enter 1 to confirm deletion)");
                        int confirmation;
                        scanf("%d",&confirmation);
                        //Delete user - activeUserNode
                        //Redirect to FirstPage
                    }
                    else
                    {
                        status_code sc = FAILURE;
                        UserNode* prev_User_ptr;
                        UserNode* User_ptr = SearchUserList(*Users_Listpptr,&prev_User_ptr,userID);
                        if(User_ptr != NULL && User_ptr->family_id == active_famNode_ptr->family_id)
                        {
                            //Deleting all expense with userID
                            ExpenseNode* exp = *Exps_Listpptr;
                            ExpenseNode* prev_Exp_ptr = NULL;
                            while(exp != NULL)
                            {
                                if(exp->user_id == userID)
                                {
                                    DeleteAfter_Exp(Exps_Listpptr,prev_Exp_ptr,exp);
                                    exp = prev_Exp_ptr->next;
                                }
                                else
                                {
                                    prev_Exp_ptr = exp;
                                    exp = exp->next;
                                }
                            }

                            // removing user from family member list
                            boolean flag = FALSE;
                            for(int i=0;i<FAM_MAX_SIZE && !flag ;i++)
                            {
                                if(active_famNode_ptr->family_members_ptr[i] == User_ptr)
                                {
                                    active_famNode_ptr->family_members_ptr[i] = NULL;
                                    flag = TRUE;
                                }
                            }

                            //Deleting user from users list
                            sc = DeleteAfter_User(Users_Listpptr,prev_User_ptr,User_ptr);
                        }
                        if(sc == SUCCESS)
                        {
                            printf("\nUser Successfully Deleted");
                        }
                    }
                    break;

                case 13:
                    printf("\nWARNING: Deleting a family will remove all associated users and expenses.");
                    printf("\nEnter current Family ID to delete: ");
                    //check if family id is correct
                    // Get input, validate, and delete the family along with its users and expenses
                    //return to Firstpage

                    break;

                // --- OTHER OPTIONS ---
                case 14:
                    printf("\nLogging Out...");
                    logout = TRUE;
                    ret_page = FIRSTPAGE;
                    break;

                default:
                    printf("\nInvalid Input, Please Try Again...");
                    ret_page = FAMILYHOME;
                    break;
            }

        }
    }
    else
    {
        printf("\nError Occured while logging in! returning to FirstPage...");
        ret_page = FIRSTPAGE;
    }
    return ret_page;
}

status_code AddUser(UserNode** User_Listpptr,UserNode** FamMember_arr, UserNode* newUserNode,FamNode* active_famNode_ptr,int* numOfUsers)
{
    status_code sc = FAILURE;
    if(active_famNode_ptr->no_of_users < FAM_MAX_SIZE)
    {
        if(newUserNode != NULL)
        {
            printf("\nPlease enter New User details");
            printf("\nNew Username :");
            getchar();
            fgets(newUserNode->user_name,NAME_MAX_SIZE,stdin);
    
            printf("\nUser's Monthly Income :");
            scanf("%f",&(newUserNode->user_income));
    
            newUserNode->family_id = active_famNode_ptr->family_id;
            newUserNode->user_id = ++(*numOfUsers);
    
            sc = InsertAfter_User(User_Listpptr,NULL,newUserNode);
            if(sc)
            {
                AddUsertoFamily(active_famNode_ptr,newUserNode);
                active_famNode_ptr->no_of_users++;
            }
            
        }
        if(sc == SUCCESS)
        {
            active_famNode_ptr->family_income += newUserNode->user_income;
        }
    }
    else
    {
        printf("\nMaximum Family Size Reached!\nCannot Add more users.");
    }

    return sc;
}

status_code AddExpense(ExpenseNode** Exp_Listpptr,ExpenseNode* newExpNode,UserNode* active_userNode_ptr,int* numOfExp_ptr)
{
    status_code sc = FAILURE;
    if(newExpNode != NULL)
    {
        printf("\nPlease enter New Expense details");
        printf("\nSelect Expense Category (0: RENT, 1: UTILITY, 2: GROCERY, 3: STATIONARY, 4: LEISURE): ");
        int category_input;
        scanf("%d", &category_input);
        if (category_input < 0 || category_input > 4) 
        {
            printf("Invalid category! Defaulting to LEISURE.\n");
            newExpNode->category = LEISURE;
        } else
        {
            newExpNode->category = (Categorytype)category_input;
        }
    
        printf("Enter Expense Amount: ");
        scanf("%f", &newExpNode->expense_amount);
    
        printf("Enter Date (1-10): ");
        scanf("%d", &newExpNode->date);
        if (newExpNode->date < 1 || newExpNode->date > 10) 
        {
            printf("Invalid date! Defaulting to 1.\n");
            newExpNode->date = 1;
        }

        newExpNode->user_id = active_userNode_ptr->user_id;
        newExpNode->expense_id = ++(*numOfExp_ptr);

        //add node expenseList
        sc = InsertAfter_Expense(Exp_Listpptr,NULL,newExpNode);
    }
    if(sc == SUCCESS)
    {
        active_userNode_ptr->category_expense[newExpNode->category] += newExpNode->expense_amount;
    }

    return sc;
}

void CalculateTotalExpense(ExpenseNode* Exps_Listptr, FamNode* active_famNode_ptr, UserNode* Users_Listptr) 
{
    if (active_famNode_ptr == NULL || Exps_Listptr == NULL || Users_Listptr == NULL) 
    {
        printf("\nNo expenses recorded for this family.\n");
    }
    else
    {
        float total_expense = 0.0;
        ExpenseNode* temp = Exps_Listptr;
    
        // Display header
        printf("\nTotal Monthly Expense Breakdown (Date-wise):\n");
        printf("--------------------------------------------------------------\n");
        printf("| %-5s | %-15s | %-10s | %-10s | %-5s |\n", "Date", "User", "Amount (Rs.)", "Category", "Date");
        printf("--------------------------------------------------------------\n");
    
        // Iterate through expense list
        while (temp != NULL) {
            // Find user name from user list
            UserNode* userTemp = Users_Listptr;
            char* userName = "Unknown";
            while (userTemp != NULL) {
                if (userTemp->user_id == temp->user_id) {
                    userName = userTemp->user_name;
                    break;
                }
                userTemp = userTemp->next;
            }
    
            // Print expense details
            printf("| %-5d | %-15s | %-10.2f | %-10d | %-5d |\n",
                   temp->date, userName, temp->expense_amount, temp->category, temp->date);
    
            total_expense += temp->expense_amount;
            temp = temp->next;
        }
    
        printf("--------------------------------------------------------------\n");
        printf("Total Family Monthly Expense: Rs. %.2f\n", total_expense);
        printf("--------------------------------------------------------------\n");
    
        // Update the family's total expense value
        active_famNode_ptr->family_expense = total_expense;
    }
}

void Get_categorical_expense(ExpenseNode* Exps_Listptr, UserNode* active_userNode_ptr, FamNode* active_famNode_ptr, Categorytype category) 
{
    // // Sort users in descending order based on their expense in this category
    // mergeSort(userArray, 0, user_count - 1, category);

    // // Display results
    // printf("\nTotal Family Expense for Category %d: Rs. %.2f\n", category, total_category_expense);
    // printf("------------------------------------------------------\n");
    // printf("| %-10s | %-15s | %-15s |\n", "User ID", "User Name", "Amount Spent (Rs.)");
    // printf("------------------------------------------------------\n");

    // for (int i = 0; i < user_count; i++) {
    //     if (userArray[i]->category_expense[category] > 0) {
    //         printf("| %-10d | %-15s | %-15.2f |\n",
    //                userArray[i]->user_id, userArray[i]->user_name, userArray[i]->category_expense[category]);
    //     }
    // }

    // printf("------------------------------------------------------\n");
}

// Function to merge two subarrays in descending order based on category expense
void merge(UserNode** userArray, int left, int mid, int right, int category) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays to hold the divided sections
    UserNode* leftArray[n1], *rightArray[n2];

    for (int i = 0; i < n1; i++) {
        leftArray[i] = userArray[left + i];
    }
    for (int i = 0; i < n2; i++) {
        rightArray[i] = userArray[mid + 1 + i];
    }

    // Merge the temporary arrays back into userArray[] in descending order
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArray[i]->category_expense[category] > rightArray[j]->category_expense[category]) {
            userArray[k++] = leftArray[i++];
        } else {
            userArray[k++] = rightArray[j++];
        }
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < n1) {
        userArray[k++] = leftArray[i++];
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2) {
        userArray[k++] = rightArray[j++];
    }
}

// Function to implement Merge Sort
void mergeSort(UserNode** userArray, int left, int right, int category) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively divide the array into two halves
        mergeSort(userArray, left, mid, category);
        mergeSort(userArray, mid + 1, right, category);

        // Merge the sorted halves
        merge(userArray, left, mid, right, category);
    }
}

status_code FindnDeleteUser(FamNode** Fams_Listpptr,UserNode** Users_Listpptr,ExpenseNode** Exps_Listpptr,UserNode* active_userNode_ptr,FamNode* active_famNode_ptr,int* numOfFams_ptr,int* numofUsers_ptr, int* numOfExp_ptr, int userId)
{
    //check if user is the last user, if so Delete FAmily too
    
}

void AddUsertoFamily(FamNode* active_fam_ptr, UserNode* newUser_ptr)
{
    int i = 0;
    while(i<FAM_MAX_SIZE)
    {
        if(active_fam_ptr->family_members_ptr[i] == NULL)
        {
            active_fam_ptr->family_members_ptr[i] = newUser_ptr;
            i=4;//exit loop
        }
        i++;
    }
}