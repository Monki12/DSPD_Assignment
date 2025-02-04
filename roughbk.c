#include<stdio.h>
#include "LinkedList.h"

int main()
{
    printf("\nHELOO\n");
    Node* n1 = (Node*)malloc(sizeof(Node)) ;
    int a=2;
    n1->data_ptr= &a;
    n1->next=NULL;
    printf("b4");
    Node** npptr = &n1;
    printf("\nAfter");
    int* dataptr= (*npptr)->data_ptr;
    printf("trying to print");
    printf("%d",(int)*dataptr);
    return 0;
}