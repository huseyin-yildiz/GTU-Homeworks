#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>

struct node
{
    int data;
    float number;
    char* name;
    struct node *next;
};


void insert_end(struct node **head, int val, float num, char* name_)
{
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = val;
    newNode->number = num;
    newNode->name = name_;
    newNode->next = NULL;

    if(*head == NULL)
        *head = newNode;
    else
    {
        struct node *lastNode = *head;

        while(lastNode->next != NULL)
        {
            lastNode = lastNode->next;
        }

        lastNode->next = newNode;
    }

}

void printList_withLoop(struct node *head)
{																		/* temp become next in every time  */
    struct node *temp;
   for(temp = head; temp!=NULL; temp = temp->next)
       printf("%d->%f->%s,\n",temp->data,temp->number,temp->name);

    printf("NULL\n");
}
void printList_withRecursive(struct node *list) {
    
    static int i = 0;													/* travers recursively and prints */
    i++;
    if(i==1)
        printf("[");
    else if(list != NULL)
        printf(", ");
    if(list != NULL){
        printf("%d->%f->%s",list->data,list->number,list->name);
        printList_withRecursive(list->next);
    }
    else
        printf("]");
}

int compare(char str1[], char str2[]){										/* compare according to alphabetically */
    if(str1[0] == '\0' && str2[0] != '\0')
        return -1;
    if(str2[0] == '\0' && str1[0] != '\0')
        return 1;
    if(str1[0] == '\0' && str2[0] == '\0')
        return 0;
    if(str1[0] > str2[0])
        return 1;
    if(str1[0] < str2[0])
        return -1;
    else
        return compare(&str1[1],&str2[1]);
}


void sortedInsert(struct node** head_ref, struct node* new_node)
{									/* finds correct plaace and swap */

        if((*head_ref)->name == NULL)
            *head_ref = new_node;

        else if( compare((*head_ref)->name,new_node->name ) >= 0 )
        {
            struct node* temp = *head_ref;
            *head_ref = new_node;
            (*head_ref)->next = temp;
        } else
            sortedInsert(&((*head_ref)->next),new_node);

}


/* A utility function to create a new node */
struct node* newNode(int new_data, float num, char* name_)
{
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->name = name_;
    newNode->number = num;									/* allocates and returns new node  */
    newNode->data = new_data;
    return newNode;
}


bool search(struct node* head, int x)
{									/* returns true if its in */

    if(head == NULL)
        return false;
    if(head->data == x)
        return true;
    else
        search(head->next,x);
}

int main()
{
    struct node *head = NULL;
    struct node* new_node;

    insert_end(&head,10,5.5,"hello1");
    insert_end(&head,20,5.5,"hello2");
    insert_end(&head,30,5.5,"hello3");

    printf("Print List with Loop: \n");
    printList_withLoop(head);

    new_node = newNode(1,5.5, "a");
    sortedInsert(&head, new_node);


    new_node = newNode(3,5.5, "c");
    sortedInsert(&head, new_node);


    new_node = newNode(2,5.5, "d");
    sortedInsert(&head, new_node);

    new_node = newNode(2,5.5, "b");
    sortedInsert(&head, new_node);

    printf("Print List with Recursive: \n");
    printList_withRecursive(head);

    printf("\nIs 20 belong this linked list?: " );
    printf(search(head, 20) ? "YES \n" : "NO \n");

    printf("\nIs 18 belong this linked list?: " );
    printf(search(head, 18) ? "YES \n" : "NO \n");

    return 0;
}