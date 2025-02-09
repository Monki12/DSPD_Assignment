#include "LinkedList.h"

typedef enum
{
    EXIT,
    FIRSTPAGE,
    SIGNUP,
    LOGIN,
    FAMILYHOME
} Pagetype;

Pagetype FirstPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr);
Pagetype SignUpPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, int *numOfFams_ptr, int *numofUSers_ptr, int *lastFamId, int *lastUserId);
status_code CreateFamily(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, char *fam_name, char *user_name, float user_income, int *numOfFams_ptr, int *numofUSers_ptr, int *lastFamId, int *lastUserId);
Pagetype LoginPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, UserNode **active_userNode_ptr, FamNode **active_famNode_ptr);
Pagetype FamilyHomePage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, UserNode *active_userNode_ptr, FamNode *active_famNode_ptr, int *numOfFams_ptr, int *numofUsers_ptr, int *numOfExp_ptr, int *lastFamId, int *lastUserId, int *lastExpId, boolean *deletedActiveUser, boolean *deletedActiveFamily);
status_code AddUser(UserNode **User_Listpptr, UserNode **FamMember_Listpptr, UserNode *newUserNode, FamNode *active_famNode_ptr, int *numOfUsers, int *lastUserId);
status_code AddExpense(ExpenseNode **Exp_Listpptr, ExpenseNode *newExpNode, UserNode *active_userNode_ptr, int *numOfExp_ptr, int *lastExpId);
void CalculateTotalExpense(ExpenseNode *Exps_Listptr, FamNode *active_famNode_ptr, UserNode *Users_Listptr);
void Get_categorical_expense(ExpenseNode **Exps_Listptr, UserNode *Users_Listptr, FamNode *active_famNode_ptr, Categorytype category);
void Get_highest_expense_day(ExpenseNode *Exps_Listpptr, UserNode *Users_Listpptr, FamNode *active_famNode_ptr);
void AddUsertoFamily(FamNode *active_fam_ptr, UserNode *newUser_ptr);
status_code DeleteUser(UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, FamNode *active_famNode_ptr, int userID);
status_code DeleteFamily(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, FamNode *active_famNode_ptr, UserNode *active_userNode_ptr, int *numOfFams_ptr, int *numofUsers_ptr, int *numOfExp_ptr, int famID);

// File handling
// Save Family Data to CSV
void saveFamilyData(FamNode *Fams_List)
{
    FILE *file = fopen("families.csv", "w");
    if (file == NULL)
    {
        printf("Error opening families.csv for writing.\n");
        return;
    }

    // Write header (optional)
    fprintf(file, "FamilyID,FamilyName,NoOfUsers,FamilyIncome,FamilyExpense\n");

    FamNode *temp = Fams_List;
    while (temp != NULL)
    {
        fprintf(file, "%d,%s,%d,%.2f,%.2f\n",
                temp->family_id, temp->family_name, temp->no_of_users,
                temp->family_income, temp->family_expense);
        temp = temp->next;
    }

    fclose(file);
}

// Save User Data to CSV
void saveUserData(UserNode *userList)
{
    FILE *userFile = fopen("users.csv", "w");
    if (userFile == NULL)
    {
        printf("Error opening file for saving users.\n");
        return;
    }

    // Write the header for user data
    fprintf(userFile, "UserID,FamilyID,UserName,UserIncome\n");

    UserNode *tempUser = userList;
    while (tempUser != NULL)
    {
        // Write user data in CSV format
        fprintf(userFile, "%d,%d,%s,%.2f\n", tempUser->user_id, tempUser->family_id, tempUser->user_name,
                tempUser->user_income);
        tempUser = tempUser->next;
    }

    fclose(userFile);
}

// Save Metadata (counts and last IDs) to a separate CSV
void saveMetadata(int numOfFams, int numOfUsers, int numOfExpenses, int lastFamId, int lastUserId, int lastExpId)
{
    FILE *file = fopen("metadata.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file for saving metadata.\n");
        return;
    }

    // Save the counts and last used IDs
    fprintf(file, "%d,%d,%d,%d,%d,%d\n",
            numOfFams, numOfUsers, numOfExpenses,
            lastFamId, lastUserId, lastExpId);

    fclose(file);
}

// Save Expense Data to CSV
void saveExpenseData(ExpenseNode *expenseList)
{
    FILE *expFile = fopen("expenses.csv", "w");
    if (expFile == NULL)
    {
        printf("Error opening file for saving expenses.\n");
        return;
    }

    // Write the header for expense data
    fprintf(expFile, "ExpenseID,UserID,Category,ExpenseAmount,Date\n");

    ExpenseNode *tempExp = expenseList;
    while (tempExp != NULL)
    {
        // Write expense data in CSV format
        fprintf(expFile, "%d,%d,%d,%.2f,%d\n", tempExp->expense_id, tempExp->user_id, tempExp->category,
                tempExp->expense_amount, tempExp->date);
        tempExp = tempExp->next;
    }

    fclose(expFile);
}

// Load Family Data from CSV
void loadFamilyData(FamNode **famList)
{
    FILE *famFile = fopen("families.csv", "r");
    if (famFile == NULL)
    {
        printf("Error opening file for loading families.\n");
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), famFile); // Skip header

    while (fgets(buffer, sizeof(buffer), famFile))
    {
        FamNode *newFam = (FamNode *)malloc(sizeof(FamNode));
        if (!newFam)
        {
            printf("Memory allocation failed for family node.\n");
            fclose(famFile);
            return;
        }

        if (sscanf(buffer, "%d,%49[^,],%d,%f,%f", &newFam->family_id, newFam->family_name,
                   &newFam->no_of_users, &newFam->family_income, &newFam->family_expense) != 5)
        {
            printf("Invalid data format in families.csv\n");
            free(newFam);
            continue;
        }
        memset(newFam->family_members_ptr, 0, sizeof(newFam->family_members_ptr));
        newFam->next = NULL;

        // Insert at end (to maintain order)
        if (*famList == NULL)
        {
            *famList = newFam;
        }
        else
        {
            FamNode *temp = *famList;
            while (temp->next)
                temp = temp->next;
            temp->next = newFam;
        }
    }

    fclose(famFile);
}

// Load User Data from CSV
void loadUserData(UserNode **userList)
{
    FILE *userFile = fopen("users.csv", "r");
    if (userFile == NULL)
    {
        printf("Error opening file for loading users.\n");
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), userFile); // Skip header

    while (fgets(buffer, sizeof(buffer), userFile))
    {
        UserNode *newUser = (UserNode *)malloc(sizeof(UserNode));
        if (!newUser)
        {
            printf("Memory allocation failed for user node.\n");
            fclose(userFile);
            return;
        }

        if (sscanf(buffer, "%d,%d,%49[^,],%f", &newUser->user_id, &newUser->family_id, newUser->user_name,
                   &newUser->user_income) != 4)
        {
            printf("Invalid data format in users.csv\n");
            free(newUser);
            continue;
        }

        newUser->next = NULL;

        // Insert at end
        if (*userList == NULL)
        {
            *userList = newUser;
        }
        else
        {
            UserNode *temp = *userList;
            while (temp->next)
                temp = temp->next;
            temp->next = newUser;
        }
    }

    fclose(userFile);
}

// Load Expense Data from CSV
void loadExpenseData(ExpenseNode **expenseList)
{
    FILE *expFile = fopen("expenses.csv", "r");
    if (expFile == NULL)
    {
        printf("Error opening file for loading expenses.\n");
        return;
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), expFile); // Skip header

    while (fgets(buffer, sizeof(buffer), expFile))
    {
        ExpenseNode *newExpense = (ExpenseNode *)malloc(sizeof(ExpenseNode));
        if (!newExpense)
        {
            printf("Memory allocation failed for expense node.\n");
            fclose(expFile);
            return;
        }

        if (sscanf(buffer, "%d,%d,%d,%f,%d", &newExpense->expense_id, &newExpense->user_id,
                   &newExpense->category, &newExpense->expense_amount, &newExpense->date) != 5)
        {
            printf("Invalid data format in expenses.csv\n");
            free(newExpense);
            continue;
        }

        newExpense->next = NULL;

        // Insert at end
        if (*expenseList == NULL)
        {
            *expenseList = newExpense;
        }
        else
        {
            ExpenseNode *temp = *expenseList;
            while (temp->next)
                temp = temp->next;
            temp->next = newExpense;
        }
    }

    fclose(expFile);
}

// Load Metadata (counts and last IDs) from the metadata file
void loadMetadata(int *numOfFams, int *numOfUsers, int *numOfExpenses, int *lastFamId, int *lastUserId, int *lastExpId)
{
    FILE *file = fopen("metadata.csv", "r");
    if (file == NULL)
    {
        printf("Error opening file for loading metadata.\n");
        return;
    }

    if (fscanf(file, "%d,%d,%d,%d,%d,%d",
               numOfFams, numOfUsers, numOfExpenses, lastFamId, lastUserId, lastExpId) != 6)
    {
        printf("Invalid metadata format in metadata.csv\n");
    }

    fclose(file);
}

void updateFamilyMembers(FamNode *fam_list_ptr, UserNode *user_list_ptr)
{
    UserNode *user_node_ptr = user_list_ptr;

    while (user_node_ptr)
    {
        FamNode *fam_node_ptr = fam_list_ptr;
        boolean family_found = FALSE;

        while (fam_node_ptr && family_found == FALSE)
        {
            if (fam_node_ptr->family_id == user_node_ptr->family_id)
            {
                AddUsertoFamily(fam_node_ptr, user_node_ptr);
                family_found = TRUE; // Flag to stop searching for this user
            }
            fam_node_ptr = fam_node_ptr->next;
        }

        user_node_ptr = user_node_ptr->next;
    }
}

int main()
{
    // Declaring LLists
    FamNode *Fams_List = NULL;
    UserNode *Users_List = NULL;
    ExpenseNode *Expenses_List = NULL;

    int numOfFams = 0;
    int numOfUsers = 0;
    int numOfExpenses = 0;

    // for ID generation
    int lastFamId = 0;
    int lastUserId = 0;
    int lastExpId = 0;

    //~~Load data from CSV files into the linked lists
    loadMetadata(&numOfFams, &numOfUsers, &numOfExpenses, &lastFamId, &lastUserId, &lastExpId);

    loadFamilyData(&Fams_List);
    loadUserData(&Users_List);
    loadExpenseData(&Expenses_List);

    // sort FamsList,UserList,ExpenseList
    mergeSortFamilies(&Fams_List);
    mergeSortUsers(&Users_List);
    mergeSortExpenses(&Expenses_List);

    // update members array of family
    FamNode *fam_node_ptr = Fams_List;
    updateFamilyMembers(Fams_List, Users_List);
    while (fam_node_ptr)
    {
        printf("\nFamily ID: %d, Name: %s\n", fam_node_ptr->family_id, fam_node_ptr->family_name);
        printf("Members:\n");

        for (int i = 0; i < FAM_MAX_SIZE; i++)
        {
            if (fam_node_ptr->family_members_ptr[i] != NULL)
            {
                printf("  - User ID: %d, Name: %s, Income: %.2f\n",
                       fam_node_ptr->family_members_ptr[i]->user_id,
                       fam_node_ptr->family_members_ptr[i]->user_name,
                       fam_node_ptr->family_members_ptr[i]->user_income);
            }
        }

        fam_node_ptr = fam_node_ptr->next;
    }

    // Display Family List
    displayFamilies(Fams_List);

    // Display User List
    displayUsers(Users_List);

    // Display Expense List
    displayExpenses(Expenses_List);

    UserNode *active_userNode_ptr = NULL;
    FamNode *active_famNode_ptr = NULL;

    Pagetype nextPage;
    nextPage = FirstPage(&Fams_List, &Users_List);
    printf("\nGoing to Page : %d ", nextPage);

    boolean exit = FALSE;

    while (!exit)
    {
        switch (nextPage)
        {
        case FIRSTPAGE:
        {
            nextPage = FirstPage(&Fams_List, &Users_List);
        }
        break;

        case LOGIN:
        {
            nextPage = LoginPage(&Fams_List, &Users_List, &active_userNode_ptr, &active_famNode_ptr);
        }
        break;

        case SIGNUP:
        {
            nextPage = SignUpPage(&Fams_List, &Users_List, &numOfFams, &numOfUsers, &lastFamId, &lastUserId);
        }
        break;

        case FAMILYHOME:
        {
            printf("\nGoing to FAMILY HOME PAGE!");
            boolean deletedActiveUser, deletedActiveFamily;
            nextPage = FamilyHomePage(&Fams_List, &Users_List, &Expenses_List, active_userNode_ptr, active_famNode_ptr, &numOfFams, &numOfUsers, &numOfExpenses, &lastFamId, &lastUserId, &lastExpId, &deletedActiveUser, &deletedActiveFamily);
            if (deletedActiveUser)
            {
                active_userNode_ptr = NULL;
            }
            if (deletedActiveFamily)
            {
                active_famNode_ptr = NULL;
            }
        }
        break;

        default:
            exit = TRUE;
        }
    }

    printf("\nExiting App. . .");
    // Before exiting, save all data to CSV files
    saveMetadata(numOfFams, numOfUsers, numOfExpenses, lastFamId, lastUserId, lastExpId);

    saveFamilyData(Fams_List);
    saveUserData(Users_List);
    saveExpenseData(Expenses_List);

    return 0;
}

Pagetype FirstPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr)
{
    printf("\n\nWelcome to the First Page of Family Expense Tracker App\n");

    Pagetype ret_page;
    int choice;
    printf("\nPlease choose an option from the menu:");
    printf("\n\t1.Login - to an exsisting user account");
    printf("\n\t2.SignUp - Create a new Family");
    printf("\n\t3.Exit - Halt Program\n");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        ret_page = LOGIN;
        break;
    case 2:
        ret_page = SIGNUP;
        break;
    case 3:
        ret_page = EXIT;
        break;
    default:
        printf("\nInvalid Input, Please Try Again...");
        ret_page = FIRSTPAGE;
    }

    return ret_page;
}

Pagetype SignUpPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, int *numOfFams_ptr, int *numofUsers_ptr, int *lastFamId, int *lastUserId)
{
    Pagetype ret_page = FIRSTPAGE;

    char fam_name[NAME_MAX_SIZE];
    char user_name[NAME_MAX_SIZE];
    float user_income = 0.0;

    printf("\nWelcome to Sign Up Page, \nPlease enter valid details to sign up\n");

    printf("\nPlease enter new Family name : ");
    getchar();
    scanf("%[^\n]s", fam_name);

    printf("\nPlease enter new User name : ");
    getchar();
    scanf("%[^\n]s", user_name);

    printf("\nPlease enter user income : ");
    scanf("%f", &user_income);

    status_code sc = CreateFamily(Fams_Listpptr, Users_Listpptr, fam_name, user_name, user_income, numOfFams_ptr, numofUsers_ptr, lastFamId, lastUserId);

    if (sc)
    {
        printf("\nFamily Created Successfully with 1 member.");
        printf("\nPlease use below credentials to login :");
        printf("\n\tFamily ID = %d\n\tUser ID = %d", (*Fams_Listpptr)->family_id, (*Users_Listpptr)->user_id);
        ret_page = FIRSTPAGE;
    }
    else
    {
        printf("\nFamily Creation Unsuccessful! Please try Again.");
    }
    return ret_page;
}

// family total income needs to be calculated at the time of family creation
status_code CreateFamily(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, char *fam_name, char *user_name, float user_income, int *numOfFams_ptr, int *numofUsers_ptr, int *lastFamId, int *lastUserId)
{
    status_code sc = FAILURE;
    status_code InsertedUser;
    status_code InsertedFamily;
    // Create FamNode
    FamNode *newFamNode_ptr = CreateFamNode();

    if (newFamNode_ptr != NULL)
    {
        UserNode *newUserNode_ptr = CreateUserNode();

        if (newUserNode_ptr != NULL)
        {
            newFamNode_ptr->family_id = ++(*lastFamId);
            ++(*numOfFams_ptr);
            strcpy(newFamNode_ptr->family_name, fam_name);

            newUserNode_ptr->user_id = ++(*lastUserId);
            ++(*numofUsers_ptr);
            strcpy(newUserNode_ptr->user_name, user_name);
            newUserNode_ptr->user_income = user_income;
            newUserNode_ptr->family_id = newFamNode_ptr->family_id;

            // adding user to userList
            InsertedUser = InsertAfter_User(Users_Listpptr, NULL, newUserNode_ptr);
            InsertedFamily = InsertAfter_Fam(Fams_Listpptr, NULL, newFamNode_ptr);

            if (InsertedFamily && InsertedUser)
            {
                sc = SUCCESS;
                AddUsertoFamily(newFamNode_ptr, newUserNode_ptr);
                newFamNode_ptr->no_of_users++;
                // calculate total family income
                newFamNode_ptr->family_income = user_income;
            }
            else
            {
                // free user node
                // free family node
                // remove from all lists
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

Pagetype LoginPage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, UserNode **active_userNode_pptr, FamNode **active_famNode_pptr)
{
    Pagetype ret_page = FIRSTPAGE;

    status_code authentication = FAILURE;
    FamNode *curr_FamNode_ptr;
    UserNode *curr_UserNode_ptr;

    int family_id;
    int user_id;
    char user_name[NAME_MAX_SIZE];

    printf("\n\nWelcome to Login Page, \nPlease enter valid details to log in\n");

    printf("\nPlease enter Family Id : ");
    scanf("%d", &family_id);

    printf("\nPlease enter User Id : ");
    scanf("%d", &user_id);

    printf("\nPlease enter User name : ");
    getchar();
    scanf("%[^\n]s", user_name); // can use fgets(user_name,MAX_NAME_SIZE,stdin)

    // Search User list
    // creating dummy prev pointers
    FamNode *dummyFam = NULL;
    UserNode *dummyUser = NULL;

    curr_UserNode_ptr = SearchUserList(*Users_Listpptr, &dummyUser, user_id);
    if (curr_UserNode_ptr != NULL)
    {
        if (user_id == curr_UserNode_ptr->user_id && family_id == curr_UserNode_ptr->family_id)
        {
            curr_FamNode_ptr = SearchFamList(*Fams_Listpptr, &dummyFam, family_id);
            if (curr_FamNode_ptr != NULL)
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
                // ret_page = LOGIN;
            }
        }
        else
        {
            printf("\nFamily ID and User ID mismatch!");
            printf("\nFamily User Login NOT Successful!\nLoading Page...");
            // ret_page = LOGIN;
        }
    }
    else
    {
        printf("\nFamily User Login NOT Successful!\nLoading Page...");
        // ret_page = LOGIN;
    }

    return ret_page;
}

Pagetype FamilyHomePage(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, UserNode *active_userNode_ptr, FamNode *active_famNode_ptr, int *numOfFams_ptr, int *numofUsers_ptr, int *numOfExp_ptr, int *lastFamId, int *lastUserId, int *lastExpId, boolean *deletedActiveUser, boolean *deletedActiveFamily)
{
    Pagetype ret_page = FIRSTPAGE;
    if (active_famNode_ptr != NULL && active_userNode_ptr != NULL)
    {
        boolean logout = FALSE;
        while (!logout)
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
                // void CalculateTotalExpense(Exps_Listpptr,active_famNode_ptr);
                CalculateTotalExpense(*Exps_Listpptr, active_famNode_ptr, *Users_Listpptr);
                break;

            case 3:

                ExpenseNode *temp = *Exps_Listpptr;
                boolean found = FALSE;
                float total_expense = 0.0;

                while (temp != NULL)
                {
                    if (temp->user_id == active_userNode_ptr->user_id)
                    {
                        found = TRUE;
                        printf("| %-10d | %-10d | %-12.2f | %-10d |\n",
                               temp->expense_id, temp->category, temp->expense_amount, temp->date);
                        total_expense += temp->expense_amount;
                    }
                    temp = temp->next;
                }

                if (!found)
                {
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
                scanf("%d", &category_input);
                Get_categorical_expense(Exps_Listpptr, *Users_Listpptr, active_famNode_ptr, category_input);

                // Display expense categories and corresponding totals
                // void CAtegoricalExpense
                break;

            case 5:
                printf("\nFinding the day with the highest expenses...");
                Get_highest_expense_day(*Exps_Listpptr, *Users_Listpptr, active_famNode_ptr);
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
                    ExpenseNode *newExp = CreateExpenseNode();
                    status_code sc = AddExpense(Exps_Listpptr, newExp, active_userNode_ptr, numOfExp_ptr, lastExpId);
                    if (sc == SUCCESS)
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
                UserNode *newUser = CreateUserNode();
                status_code sc = AddUser(Users_Listpptr, active_famNode_ptr->family_members_ptr, newUser, active_famNode_ptr, numofUsers_ptr, lastUserId);
                if (sc == SUCCESS)
                {
                    printf("\nNew User added!");
                    printf("\nNew User ID = %d", newUser->user_id);
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
                scanf("%d", &expID);

                status_code sc = FAILURE;
                ExpenseNode *prev_Exp_ptr = NULL;
                ExpenseNode *Exp_ptr = SearchExpenseList(*Exps_Listpptr, &prev_Exp_ptr, expID);
                if (Exp_ptr != NULL && Exp_ptr->user_id == active_userNode_ptr->user_id)
                {
                    printf("\nExpense found. Deleting Expense...");
                    Categorytype category = Exp_ptr->category;
                    float amount = Exp_ptr->expense_amount;
                    sc = DeleteAfter_Exp(Exps_Listpptr, prev_Exp_ptr, Exp_ptr);
                    if (sc == SUCCESS)
                    {
                        // delete from user category expense
                        *numOfExp_ptr--;
                        active_userNode_ptr->category_expense[category] -= amount;
                        // delete from family total expense -- managed by function
                    }
                }
                else
                {
                    printf("\nExpense not found. Returning to FamilyHomepage...");
                }
                // Get input, find expense, and remove it from the list

                break;

            case 12:
                int userID;
                boolean confirm;
                status_code sc1;
                printf("\nEnter User ID to delete: ");
                scanf("%d", &userID);
                // check if userID == Active...if so return to Homepage
                // check if user is the last user, if so Delete FAmily too
                if (userID == active_userNode_ptr->user_id)
                {
                    printf("\nDo you want to Delete Current user? (Enter 1 to confirm deletion)\n");
                    scanf("%d", &confirm);
                    if (confirm)
                    {
                        printf("\nDeletion Confirmed.");
                        sc = DeleteUser(Users_Listpptr, Exps_Listpptr, active_famNode_ptr, userID);
                        if (sc == SUCCESS)
                        {
                            printf("\nUser Deleted Successfully");
                            *deletedActiveUser = TRUE;
                            logout = TRUE;
                            ret_page = FIRSTPAGE;
                        }
                        else
                        {
                            printf("\nError occured while deleting user!");
                        }
                    }
                }
                else
                {
                    sc = DeleteUser(Users_Listpptr, Exps_Listpptr, active_famNode_ptr, userID);
                }

                if (sc == SUCCESS)
                {
                    *numofUsers_ptr--;
                    if (*numofUsers_ptr == 0)
                    {
                        // Delete family;
                        sc = DeleteFamily(Fams_Listpptr, Users_Listpptr, Exps_Listpptr, active_famNode_ptr, active_userNode_ptr, numOfFams_ptr, numofUsers_ptr, numOfExp_ptr, active_famNode_ptr->family_id);
                    }
                }

                break;

            case 13:
                printf("\nWARNING: Deleting a family will remove all associated users and expenses.");
                printf("\nEnter current Family ID to delete: ");
                int famID;
                scanf("%d", &famID);
                if (famID == active_famNode_ptr->family_id)
                {
                    status_code sc2 = DeleteFamily(Fams_Listpptr, Users_Listpptr, Exps_Listpptr, active_famNode_ptr, active_userNode_ptr, numOfFams_ptr, numofUsers_ptr, numOfExp_ptr, famID);
                    if (sc2 == SUCCESS)
                    {
                        *numOfFams_ptr--;
                        *deletedActiveFamily = TRUE;
                        *deletedActiveUser = TRUE;
                        logout = TRUE;
                        ret_page = FIRSTPAGE;
                        printf("\nFamily Deleted Successfully");
                    }
                    else
                    {
                        printf("\nError occured!!");
                    }
                }
                else
                {
                    printf("\nAuthentication Failed!");
                }

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

status_code AddUser(UserNode **User_Listpptr, UserNode **FamMember_arr, UserNode *newUserNode, FamNode *active_famNode_ptr, int *numOfUsers, int *lastUserId)
{
    status_code sc = FAILURE;
    if (active_famNode_ptr->no_of_users < FAM_MAX_SIZE)
    {
        if (newUserNode != NULL)
        {
            printf("\nPlease enter New User details");
            printf("\nNew Username :");
            getchar();
            fgets(newUserNode->user_name, NAME_MAX_SIZE, stdin);

            printf("\nUser's Monthly Income :");
            scanf("%f", &(newUserNode->user_income));

            newUserNode->family_id = active_famNode_ptr->family_id;
            newUserNode->user_id = ++(*lastUserId);
            *numOfUsers++;

            sc = InsertAfter_User(User_Listpptr, NULL, newUserNode);
            if (sc)
            {
                AddUsertoFamily(active_famNode_ptr, newUserNode);
                active_famNode_ptr->no_of_users++;
            }
        }
        if (sc == SUCCESS)
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

status_code AddExpense(ExpenseNode **Exp_Listpptr, ExpenseNode *newExpNode, UserNode *active_userNode_ptr, int *numOfExp_ptr, int *lastExpId)
{
    status_code sc = FAILURE;
    if (newExpNode != NULL)
    {
        printf("\nPlease enter New Expense details");
        printf("\nSelect Expense Category (0: RENT, 1: UTILITY, 2: GROCERY, 3: STATIONARY, 4: LEISURE): ");
        int category_input;
        scanf("%d", &category_input);
        if (category_input < 0 || category_input > 4)
        {
            printf("Invalid category! Defaulting to LEISURE.\n");
            newExpNode->category = LEISURE;
        }
        else
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
        newExpNode->expense_id = ++(*lastExpId);
        *numOfExp_ptr++;

        // add node expenseList
        sc = InsertAfter_Expense(Exp_Listpptr, NULL, newExpNode);
    }
    if (sc == SUCCESS)
    {
        active_userNode_ptr->category_expense[newExpNode->category] += newExpNode->expense_amount;
    }

    return sc;
}

void CalculateTotalExpense(ExpenseNode *Exps_Listptr, FamNode *active_famNode_ptr, UserNode *Users_Listptr)
{
    if (active_famNode_ptr == NULL || Exps_Listptr == NULL || Users_Listptr == NULL)
    {
        printf("\nError while calculating expenses\n");
    }
    else
    {
        float total_expense = 0.0;
        boolean expense_found_in_family = FALSE; // Flag to track if at least one expense is found
        boolean found_expense = FALSE;
        ExpenseNode *temp = Exps_Listptr;
        UserNode *uptr = NULL;
        char *userName = "Unknown";
        // Display header
        printf("\nTotal Monthly Expense Breakdown (Date-wise):\n");
        printf("------------------------------------------------------------------------\n");
        printf("| %-10s | %-10s | %-15s | %-10s | %-10s |\n", "Date", "UserID", "User", "Amount (Rs.)", "Category");
        printf("------------------------------------------------------------------------\n");

        // Iterate through expense list

        while (temp != NULL)
        {
            found_expense = FALSE;

            for (int i = 0; i < FAM_MAX_SIZE && !found_expense; i++)
            {
                if (active_famNode_ptr->family_members_ptr[i] != NULL)
                {
                    uptr = active_famNode_ptr->family_members_ptr[i];

                    if (temp->user_id == uptr->user_id)
                    {
                        found_expense = TRUE;
                        expense_found_in_family = TRUE; // Set flag to true
                        userName = uptr->user_name;
                    }
                }
            }

            if (found_expense)
            {
                printf("| %-10d | %-10d | %-15s | %-10.2f | %-10d |\n",
                       temp->date, temp->user_id, userName, temp->expense_amount, temp->category);
                total_expense += temp->expense_amount;
            }

            temp = temp->next;
        }
        printf("------------------------------------------------------------------------\n");
        if (!expense_found_in_family)
        {
            printf("\nNo expenses recorded.\n");
        }
        else
        {
            // Display total family monthly expense
            float balance = active_famNode_ptr->family_income - total_expense;
            printf("Total Family Monthly Expense: Rs. %.2f\n", total_expense);
            printf("Total Family Monthly Balance: Rs. %.2f\n", balance);
            printf("------------------------------------------------------------------------\n");

            // Update the family's total expense value
            active_famNode_ptr->family_expense = total_expense;
        }
    }
}

void Get_categorical_expense(ExpenseNode **Exps_Listpptr, UserNode *Users_Listptr, FamNode *active_famNode_ptr, Categorytype category)
{
    if (active_famNode_ptr == NULL || Exps_Listpptr == NULL || *Exps_Listpptr == NULL)
    {
        printf("\nError while calculating categorical expenses.\n");
        return;
    }

    // Sorting expenses
    mergeSortExpenses(Exps_Listpptr);

    float total_expense = 0.0;
    ExpenseNode *temp = *Exps_Listpptr;
    boolean category_found = FALSE; // Flag to track if any expense is found
    boolean found_expense = FALSE;
    char *userName = "Unknown";

    // Display header
    printf("\nTotal Monthly Expense Breakdown for Category : %-10d (Date-wise):\n", category);
    printf("--------------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-15s | %-10s |\n", "Date", "UserID", "User", "Amount (Rs.)");
    printf("--------------------------------------------------------------\n");

    // Iterate through expense list
    while (temp != NULL)
    {
        found_expense = FALSE;

        for (int i = 0; i < FAM_MAX_SIZE && !found_expense; i++)
        {
            if (active_famNode_ptr->family_members_ptr[i] != NULL)
            {
                UserNode *uptr = active_famNode_ptr->family_members_ptr[i];

                if (temp->user_id == uptr->user_id)
                {
                    found_expense = TRUE;
                    category_found = TRUE; // Set flag indicating an expense is found
                    userName = uptr->user_name;
                }
            }
        }

        // Print only if the expense belongs to a family member and matches the given category
        if (found_expense && temp->category == category)
        {
            printf("| %-10d | %-10d | %-15s | %-10.2f |\n",
                   temp->date, temp->user_id, userName, temp->expense_amount);

            total_expense += temp->expense_amount;
        }

        temp = temp->next;
    }

    printf("--------------------------------------------------------------\n");
    if (!category_found)
    {
        printf("\nNo expenses recorded in this category.\n");
    }
    else
    {
        printf("Total Family Monthly Expense in Category %-10d: Rs. %.2f\n", category, total_expense);
        printf("--------------------------------------------------------------\n");
    }
}

void Get_highest_expense_day(ExpenseNode *Exps_Listptr, UserNode *Users_Listptr, FamNode *active_famNode_ptr)
{
    if (active_famNode_ptr == NULL || Exps_Listptr == NULL || Users_Listptr == NULL)
    {
        printf("\nError while calculating highest expense day.\n");
        return;
    }

    float daily_expense[11] = {0}; // Index 0 is unused (dates 1-10)
    ExpenseNode *temp = Exps_Listptr;
    boolean highest_expense_day_found = FALSE;
    boolean found_expense = FALSE;
    float max_expense = 0.0;
    int highest_expense_day = 0;

    // Iterate through the expense list and accumulate expenses for each date
    while (temp != NULL)
    {
        found_expense = FALSE;

        for (int i = 0; i < FAM_MAX_SIZE && !found_expense; i++)
        {
            if (active_famNode_ptr->family_members_ptr[i] != NULL)
            {
                UserNode *uptr = active_famNode_ptr->family_members_ptr[i];

                if (temp->user_id == uptr->user_id)
                {
                    found_expense = TRUE;
                }
            }
        }

        if (found_expense)
        {
            daily_expense[temp->date] += temp->expense_amount;
        }

        temp = temp->next;
    }

    // Determine the highest expense day
    for (int i = 1; i <= 10; i++)
    {
        if (daily_expense[i] > max_expense)
        {
            max_expense = daily_expense[i];
            highest_expense_day = i;
            highest_expense_day_found = TRUE;
        }
    }

    // Print result
    if (highest_expense_day_found)
    {
        printf("\nHighest Expense Day: %d with an expense of Rs. %.2f\n", highest_expense_day, max_expense);
    }
    else
    {
        printf("\nNo expenses recorded for this family.\n");
    }
}

status_code DeleteUser(UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, FamNode *active_famNode_ptr, int userID)
{

    status_code sc = FAILURE;
    UserNode *prev_User_ptr;
    UserNode *User_ptr = SearchUserList(*Users_Listpptr, &prev_User_ptr, userID);
    if (User_ptr != NULL && User_ptr->family_id == active_famNode_ptr->family_id)
    {
        // Deleting all expense with userID
        ExpenseNode *exp = *Exps_Listpptr;
        ExpenseNode *prev_Exp_ptr = NULL;
        while (exp != NULL)
        {
            if (exp->user_id == userID)
            {
                DeleteAfter_Exp(Exps_Listpptr, prev_Exp_ptr, exp);
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
        for (int i = 0; i < FAM_MAX_SIZE && !flag; i++)
        {
            if (active_famNode_ptr->family_members_ptr[i] == User_ptr)
            {
                active_famNode_ptr->family_members_ptr[i] = NULL;
                flag = TRUE;
            }
        }

        // Deleting user from users list
        sc = DeleteAfter_User(Users_Listpptr, prev_User_ptr, User_ptr);
    }
    if (sc == SUCCESS)
    {
        active_famNode_ptr->no_of_users--;
        printf("\nUser Successfully Deleted");
    }
    return sc;
}

void AddUsertoFamily(FamNode *active_fam_ptr, UserNode *newUser_ptr)
{
    int i = 0;
    while (i < FAM_MAX_SIZE)
    {
        if (active_fam_ptr->family_members_ptr[i] == NULL)
        {
            active_fam_ptr->family_members_ptr[i] = newUser_ptr;
            i = 4; // exit loop
        }
        i++;
    }
}

status_code DeleteFamily(FamNode **Fams_Listpptr, UserNode **Users_Listpptr, ExpenseNode **Exps_Listpptr, FamNode *active_famNode_ptr, UserNode *active_userNode_ptr, int *numOfFams_ptr, int *numofUsers_ptr, int *numOfExp_ptr, int famID)
{
    status_code sc = SUCCESS;
    for (int i = 0; i < FAM_MAX_SIZE && sc; i++)
    {
        if (active_famNode_ptr->family_members_ptr[i] != 0)
        {
            printf("\nAttempting to delete user ID: %d", (active_famNode_ptr->family_members_ptr[i])->user_id);
            sc = DeleteUser(Users_Listpptr, Exps_Listpptr, active_famNode_ptr, (active_famNode_ptr->family_members_ptr[i])->user_id);
            if (sc == FAILURE)
            {
                printf("\nFailed to delete user ID: %d", (active_famNode_ptr->family_members_ptr[i])->user_id);
            }
        }
    }

    if (sc == FAILURE)
    {
        printf("\nUnable to Delete Family users! ");
    }
    else
    {
        FamNode *prev_Fam_ptr = NULL;
        FamNode *Fam_ptr = SearchFamList(*Fams_Listpptr, &prev_Fam_ptr, famID);
        if (Fam_ptr == NULL)
        {
            printf("\nError: Family ID %d not found in the list!", famID);
        }
        else
        {
            printf("\nDeleting Family from list");
            sc = DeleteAfter_Fam(Fams_Listpptr, prev_Fam_ptr, Fam_ptr);
            if (sc == FAILURE)
            {
                printf("\nError Occured! Unable to Delete Family");
            }
            else
            {
                if (sc == SUCCESS)
                {
                    (*numOfFams_ptr)--;
                    printf("\nFamily count after deletion: %d", *numOfFams_ptr);
                }
            }
        }
    }
    return sc;
}
