#include<stdio.h>
#include "FamilyStructure.h"

//Family* newfamdata_ptr = CreateFamilyStruct(active_userid_ptr,active_familyid_ptr,fam_name,user_name,user_income);
 
status_code CreateFamily(active_userid_ptr,active_familyid_ptr,fam_name,user_name,user_income)
{
    //get newFamdata_ptr for data_ptr
    //create fam node and  values
    status_code sc = FAILURE;
    Family* newFamData_ptr = (Family*)malloc(sizeof(Family));

    if(newFamData_ptr != NULL)
    {
        newFamData_ptr->family_id = 1;//find a way
        newFamData_ptr->family_name = fam_name;
        newFamData_ptr->family_income=0.0;
        newFamData_ptr->family_expense=0.0;
        newFamData_ptr->no_of_users = 0;

    //to be continued
       // Node* newFamNode = CreateNode(FAMILY,Fam_List,newFamData_ptr);

       // sc = InsertAfter(Fam_List->head,NULL,newFamData_ptr);
    }
    



    //get newUserdata_ptr for data_ptr
    //create user node and assign values 

    //add user to fam list
}

