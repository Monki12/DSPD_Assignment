#include<stdio.h>
#include "LinkedList.h"

void foo(char* s)
{
    printf("%s",s);
}

int main()
{
   char fam_name[20];

    printf("\nWelcome, \nPlease enter valid details to sign up\n");

    printf("\nPlease enter new Family name : ");
    scanf("%[^\n]s",fam_name);
    printf("%s",fam_name);
    foo(fam_name);
}
