//
// Created by dell on 31/05/2021.
//

#ifndef CSE102_HW11_LINKEDLISTS_H
#define CSE102_HW11_LINKEDLISTS_H

#include <stdlib.h>
#include <string.h>

#define MAX_N_SIZE 100
#define MAX_G_SIZE 20


typedef struct{
    double budget;
    int year;
    char name[MAX_N_SIZE];
    struct movie_budget *next;
}movie_budget;

typedef struct{
    char genre[MAX_G_SIZE];
    char name[MAX_N_SIZE];
    double score;
    struct movie_name *next;
}movie_name;


movie_name * new_movie_name(char genre[], char name[], double score);

movie_budget * new_movie_budget(double budget, int year, char name[]);

typedef int comparator(movie_budget*, movie_budget*);

typedef int comparator2(movie_name *, movie_name *);

movie_budget * insert_sorted_budgets(movie_budget* head, movie_budget* node,comparator comparator1,comparator comparator2);

movie_name * insert_sorted_names(movie_name * head, movie_name * node,comparator2 comparator1,comparator2 comparator2);

void insert_names(movie_name ** head, movie_name * node);

int compareString(char str1[], char str2[]);

int yearComparator(movie_budget* mb1, movie_budget* mb2);

int budgetComparator(movie_budget* mb1, movie_budget* mb2);

int genreComparator(movie_name * mb1, movie_name* mb2);

int nameComparator(movie_budget* mb1, movie_budget* mb2);

int scoreComparator(movie_name* mb1, movie_name* mb2);

void printList(movie_name * list);




#endif //CSE102_HW11_LINKEDLISTS_H
