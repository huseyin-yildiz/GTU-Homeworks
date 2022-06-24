#include "hw9_lib.h"

void addCustomer(sequence* mySequence,customer* myCustomer){                                                                               /* add customer function */
    static short max_user_sizes[5] ={5,3,3,2,2};
    node* newCustomerNode;

    if(mySequence->size >= MAX_CUSTOMER){
        printf("The sequence is full");
        return;
    }
  
    if( mySequence->userSizes[myCustomer->label] >= max_user_sizes[myCustomer->label] )                                       /* if max is exceed */
    {
        node* newCustomerNode = malloc( sizeof(node) );
        newCustomerNode->dataCustomer = myCustomer;
        mySequence->last->next = (struct node *) newCustomerNode;
        mySequence->last = (node *) mySequence->last->next;
    }
    else{

        node* myNext = mySequence->first;
        short isBigger = 0;
        while ( myNext != NULL && myNext->dataCustomer->label <= myCustomer->label ) {                                                             /* finds the point to be inserted */
            isBigger = 1;
            if (myNext->next != NULL ) {
                myNext = (node *) myNext->next;
                isBigger = 0;
            }
            else
                break;
        }


        newCustomerNode = malloc( sizeof(node) );
        newCustomerNode->dataCustomer = myCustomer;

        if(mySequence->size == 0){                                                                                                 /* if the sequence is empty */
            mySequence->first = newCustomerNode;
            mySequence->last = newCustomerNode;
        }

        else if(myNext == mySequence->first && !isBigger){                                                                            /*  if adding to head of the sequence */
            mySequence->first->prev = (struct node *) newCustomerNode;
            newCustomerNode->next = (struct node *) mySequence->first;
            mySequence->first = newCustomerNode;
        }
        else{                                                                                           /* if the coming bigger than the point to be inserted */
            if(isBigger) {
                node *pre;
                newCustomerNode->prev = (struct node *) myNext;
                newCustomerNode->next = myNext->next;
                myNext->next = (struct node *) newCustomerNode;
                pre = (node *) newCustomerNode->next;
                if (pre != NULL)
                    pre->prev = (struct node *) newCustomerNode;

                if (myNext == mySequence->last)                                                     /* if adding to last pf the sequence */
                    mySequence->last = newCustomerNode;
            }
            else{                                                                                       /* if the coming is not bigger than the point to be inserted */
                node *pre;
                newCustomerNode->next = (struct node *) myNext;
                newCustomerNode->prev = myNext->prev;
                myNext->prev = (struct node *) newCustomerNode;

                pre = (node *) newCustomerNode->prev;
                if (pre != NULL)
                    pre->next = (struct node *) newCustomerNode;

                if (myNext == mySequence->first)                                                     /* if adding to first of the sequence */
                    mySequence->first = newCustomerNode;
            }
        }

        if(mySequence->last == NULL )
              mySequence->last = newCustomerNode;

    }

    mySequence->userSizes[myCustomer->label] = mySequence->userSizes[myCustomer->label]+1;
    mySequence->size++;
}


customer* processCustomer(sequence* mysequence){                                        /* removes the first customer in sequence and returns it */
    node* temp = mysequence->first;
    mysequence->first = (node *) mysequence->first->next;
    mysequence->size--;
    mysequence->userSizes[temp->dataCustomer->label] = mysequence->userSizes[temp->dataCustomer->label]-1;

    if(mysequence->size == 0)
        mysequence->last = NULL;

    return temp->dataCustomer;
}