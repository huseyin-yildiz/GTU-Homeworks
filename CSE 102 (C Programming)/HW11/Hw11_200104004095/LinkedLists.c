//
// Created by dell on 31/05/2021.
//

#include "LinkedLists.h"
#include <stdio.h>

movie_name * new_movie_name(char genre[], char name[], double score){
    movie_name * newNode = malloc(sizeof(movie_name));
    strcpy(newNode->name, name);
    newNode->score = score;
    strcpy(newNode->genre, genre);
    newNode->next = NULL;
    return newNode;
}


movie_budget * new_movie_budget(double budget, int year, char name[]){
    movie_budget *newNode = malloc(sizeof(movie_budget));
    newNode->next = NULL;
    strcpy(newNode->name, name);
    newNode->budget = budget;
    newNode->year = year;
    return newNode;
}


movie_budget* insert_sorted_budgets(movie_budget* head, movie_budget* node,comparator comparatorFunc1 ,comparator comparatorFunc2 ){

    movie_budget *ce,*ne;

    if(head == NULL || comparatorFunc1(head,node) < 0){
        node->next = (struct movie_budget *) head;
        head = node;
    }
    else{
        ce = head;
        ne = (movie_budget *) ce->next;
        while (ce!=NULL && ne!=NULL && !( comparatorFunc1(ce,node) >= 0 && comparatorFunc1(node,ne) >=0 )){
            ce = ne;
            ne = (movie_budget *) ce->next;
        }
        if( ne!=NULL && comparatorFunc1(ne,node) == 0 ){
            if(comparatorFunc2(node,ne) > 0){
                ce->next = (struct movie_budget *) node;
                node->next = (struct movie_budget *) ne;
            }
            else{
                ce = ne;
                ne = (movie_budget *) ce->next;
                while (ce!=NULL && ne!=NULL && comparatorFunc1(ne,node)==0 && !( comparatorFunc2(ce,node)>=0 && comparatorFunc2(node,ne)>0 )){
                    ce = ne;
                    ne = (movie_budget *) ce->next;
                }
                ce->next = (struct movie_budget *) node;
                node->next = (struct movie_budget *) ne;
            }
        }
        else{
            ce->next = (struct movie_budget *) node;
            node->next = (struct movie_budget *) ne;
        }

    }
    return head;
}

void insert_names(movie_name ** head, movie_name * node){
    node->next = (struct movie_name *) *head;
    *head = node;
}


int budgetComparator(movie_budget* mb1, movie_budget* mb2){
    if(mb1->budget > mb2->budget)
        return 1;
    if(mb1->budget < mb2->budget)
        return -1;
    else
        return 0;
}

int yearComparator(movie_budget* mb1, movie_budget* mb2){
    if(mb1->year > mb2->year)
        return 1;
    if(mb1->year < mb2->year)
        return -1;
    else
        return 0;
}


int compareString(char str1[], char str2[]){										/* compare according to alphabetically */
    if(str1[0] == '\0' && str2[0] != '\0')
        return 1;
    if(str2[0] == '\0' && str1[0] != '\0')
        return -1;
    if(str1[0] == '\0' && str2[0] == '\0')
        return 0;
    if(str1[0] < str2[0] )
        return 1;
    if(str1[0] > str2[0] )
        return -1;
    else
        return compareString(&str1[1],&str2[1]);
}

int genreComparator(movie_name * mb1, movie_name* mb2) {
    int i = compareString(mb1->genre, mb2->genre);

    return i;
}

int nameComparator(movie_budget* mb1, movie_budget* mb2){
    return compareString(mb1->name,mb2->name);
}

int scoreComparator(movie_name* mb1, movie_name* mb2){
    if(mb1->score > mb2->score)
        return 1;
    if(mb1->score < mb2->score)
        return -1;
    else
        return 0;
}

movie_name * insert_sorted_names(movie_name * head, movie_name * node,comparator2 comparatorFunc1,comparator2 comparatorFunc2){

    movie_name *ce,*ne;

    if(head == NULL || comparatorFunc1(head,node) < 0){                     // if head is null
        node->next = (struct movie_name *) head;
        head = node;            //
    }
    else{
        ce = head;
        ne = (movie_name *) ce->next;
        while (ce!=NULL && ne!=NULL && !( comparatorFunc1(ce,node) >= 0 && comparatorFunc1(node,ne) >=0 )){
            ce = ne;
            ne = (movie_name *) ce->next;
        }
        if( ne!=NULL && comparatorFunc1(ne,node) == 0 ){
            if(comparatorFunc2(node,ne) > 0){
                ce->next = (struct movie_name *) node;
                node->next = (struct movie_name *) ne;
            }
            else{
                ce = ne;
                ne = (movie_name *) ce->next;
                while (ce!=NULL && ne!=NULL && comparatorFunc1(ne,node)==0 && !( comparatorFunc2(ce,node)>=0 && comparatorFunc2(node,ne)>0 )){
                    ce = ne;
                    ne = (movie_name *) ce->next;
                }
                ce->next = (struct movie_name *) node;
                node->next = (struct movie_name *) ne;
            }
        }
        else{
            ce->next = (struct movie_name *) node;
            node->next = (struct movie_name *) ne;
        }

    }
 //   printList(head);
    return head;

}

void printList(movie_name * list){
    if(list != NULL){
        printf("Name: %s Score: %lf Genre: %s\n",list->name,list->score,list->genre);
        printList((movie_name *) list->next);
    } else
        printf("\n");
}

/*
int main(){



    movie_budget *movieBudget = new_movie_budget(1111,1212,"ali");
    movie_budget *newM = new_movie_budget(2222,2323,"veli");
    movie_budget *n2 = new_movie_budget(11,22,"vell");

    printList(movieBudget);
    movieBudget = insert_sorted_budgets(movieBudget,newM);
    printList(movieBudget);
    movieBudget = insert_sorted_budgets(movieBudget,n2);
    printList(movieBudget);

    movie_budget *n3 = new_movie_budget(101,202,"vella");
    movieBudget = insert_sorted_budgets(movieBudget,n3);
    printList(movieBudget);

    movie_budget *n4 = new_movie_budget(105,202,"vella1");
    movieBudget = insert_sorted_budgets(movieBudget,n4);
    printList(movieBudget);


    movie_budget *n5 = new_movie_budget(95,202,"vella");
    movieBudget = insert_sorted_budgets(movieBudget,n5);
    printList(movieBudget);

    movie_budget *n6 = new_movie_budget(99,202,"vella");
    movieBudget = insert_sorted_budgets(movieBudget,n6);
    printList(movieBudget);

    movie_budget *n7 = new_movie_budget(101,202,"vella");
    movieBudget = insert_sorted_budgets(movieBudget,n7);
    printList(movieBudget);



    movie_budget *movieBudget = new_movie_budget(1111,1212,"ali");
    movie_budget *newM = new_movie_budget(2222,2323,"veli");
    movie_budget *n2 = new_movie_budget(11,22,"vell");

    printList(movieBudget);
    movieBudget = insert_sorted_budgets_2(movieBudget,newM,yearComparator,budgetComparator);
    printList(movieBudget);
    movieBudget = insert_sorted_budgets_2(movieBudget,n2,yearComparator,budgetComparator);
    printList(movieBudget);

    movie_budget *n3 = new_movie_budget(101,202,"vella");
    movieBudget = insert_sorted_budgets_2(movieBudget,n3,yearComparator,budgetComparator);
    printList(movieBudget);

    movie_budget *n4 = new_movie_budget(105,202,"vella1");
    movieBudget = insert_sorted_budgets_2(movieBudget,n4,yearComparator,budgetComparator);
    printList(movieBudget);


    movie_budget *n5 = new_movie_budget(95,202,"vella");
    movieBudget = insert_sorted_budgets_2(movieBudget,n5,yearComparator,budgetComparator);
    printList(movieBudget);

    movie_budget *n6 = new_movie_budget(99,202,"vella");
    movieBudget = insert_sorted_budgets_2(movieBudget,n6,yearComparator,budgetComparator);
    printList(movieBudget);

    movie_budget *n7 = new_movie_budget(101,202,"vella");
    movieBudget = insert_sorted_budgets_2(movieBudget,n7,yearComparator,budgetComparator);
    printList(movieBudget);



    return 0;
}
*/