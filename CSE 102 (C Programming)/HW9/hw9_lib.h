#ifndef CSE102_HW9_HW9_LIB_H
#define CSE102_HW9_HW9_LIB_H

#include <string.h>
#include <stdlib.h>
#include "stdio.h"


#define MAX_NAME_SIZE 30
#define MAX_CUSTOMER 50



typedef struct{
    char name[MAX_NAME_SIZE];
    int age;
    short label;
}customer;


typedef struct{
    customer* dataCustomer;
    struct node* next;
    struct node* prev;
}node;

typedef struct {
    node* first;
    node* last;
    int userSizes[5];
    int size;
}sequence;

void addCustomer(sequence* mySequence, customer* myCustomer);
customer* processCustomer(sequence* mysequence);


#endif
