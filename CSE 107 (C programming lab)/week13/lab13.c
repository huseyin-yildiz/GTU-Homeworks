#include <stdio.h>
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"

#define FILENAME "file.txt"                     /* filename */
#define MAX 100


typedef struct {
    char *country;
    char *capital;
    int population;
    bool driving_side;
}record;

typedef struct {
    record *record1;
    struct recordNode* next;
}record_node;

                                            /* all required structs */
typedef struct{
    record ** records;
    int size;
    int capacity;
}countriesArray;

record * new_record(char country1[],char capital1[], int population1, bool driving_side1 ){
    record * record1 = malloc(sizeof(record));
    record1->country = calloc(sizeof(char), strlen(country1)+1);
    strcpy(record1->country, country1);

    record1->capital = calloc(sizeof(char), strlen(capital1)+1);
    strcpy(record1->capital, capital1);
    record1->population = population1;
    record1->driving_side = driving_side1;
    return record1;
}



void get_new_record(countriesArray* countries){
    char country[MAX];
    char capital[MAX];
    int pop,a;
    bool ds;
    record *record1;

    printf("Country Name");
    scanf("%s",country);

    printf("Capital");
    scanf("%s",capital);

    printf("Population of %s",country);
    scanf("%d",&pop);

    printf("Do people in %s drive on the right side? (Yes:1, No:0)",country);
    scanf("%d",&a);
    ds = (bool)a;

    record1 = new_record(country, capital, pop, ds);


    if(countries->size == countries->capacity && countries->size != 0){
        countries->records = realloc(countries->records,(countries->capacity*2) );
    }
    a = countries->size;
    countries->records[a] = record1;
    countries->size = countries->size +1;

}


void writeFile(countriesArray * countries){
    char lr[6];
    int i;
    record *record1;
    FILE * file = fopen(FILENAME,"w");

    for(i=0; i<countries->size; i++) {
        record1 = countries->records[i];
        if (record1->driving_side == true)
            strcpy(lr,"Right");
        else
            strcpy(lr,"Left");

        fprintf(file, "\n%s %s %d %s",record1->country, record1->capital, record1->population, lr);

    }
    fclose(file);
}


record_node* readFile(){
    FILE *file = fopen(FILENAME, "r");
    char lr[6];
    bool first = true;
    record_node *records = malloc(sizeof(record_node));
    records->record1 = NULL;

    while ( !feof(file) ) {
        record_node *recordNode = malloc(sizeof(record));
        record *record1;
        char name[MAX];
        char cap[MAX];
        int pop;


        fscanf(file, "\n%s %s %d %s", &name[1], &cap[0], &pop, lr);


        record1 = new_record(&name[1], cap, pop, false);


        if (strcmp(lr, "Right") == 0) {
            record1->driving_side = true;
        }


        recordNode->record1 = new_record(&name[1], cap, pop, false);
        recordNode->record1 = record1;

        if (records->record1 == NULL)
            records->record1 = recordNode->record1;
        else {
            recordNode->next = records;
            records = recordNode;
        }
        first = false;
    }
    return records;
}


void print_records(record_node * records){
    record_node *temp;
    record *record1;
    for(temp = records; temp!=NULL; temp=temp->next){
        char lr[6];
        record1 = temp->record1;
        if(record1->driving_side == true)
            strcpy(lr,"Right");
        else
            strcpy(lr,"Left");

        printf("Country: %-20s Capital: %-20s Population: %-20d Driving Side: %s\n",record1->country, record1->capital, record1->population, lr);
    }
}




int main() {

    countriesArray countries = {.size=0, .capacity=10};
    countries.records = calloc(sizeof(record), 10);
    record_node * records;



    int sel;
    do {

        printf("1: Enter new record\n");
        printf("2: Write to file\n");
        printf("3: Read from the file\n");
        printf("4: Print the linked list\n");
        printf("5: Exit\n");

        printf("\nSelect: ");
        scanf("%d", &sel);

        switch (sel) {
            case 1: get_new_record(&countries);break;
            case 2: writeFile(&countries); break;
            case 3: records = readFile(); break;
            case 4: print_records(records); break;
            case 5: break;

        }
    } while (sel != 5);



    return 0;
}
