/*
** hw8_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.22.19.55
**
*/

#include <stdio.h>
#include "hw8_lib.h"

#define WORDSIZE 20

#define TRUE 1;
#define FALSE 0;




void write_to_file(FILE *pFile, char word[20]);



short read_word(FILE* infid, char* word){                       /* reads a word from the file */

    fscanf(infid,"%s",word);
    if(feof(infid))
        return FALSE;
    return TRUE;

}

short is_same(char word[], char word2[]) {                       /* checks if the both words is same */

    if(word[0] == '\0' && word2[0] == '\0' || (word[0] == '.' && word2[0] =='\0' && word[1] == '\0') )
        return TRUE;
    if(word[0] != word2[0])
        return FALSE;

    if(word[0] == word2[0])
        return is_same(&word[1],&word2[1]);
}

short contains(char* word,char* words_to_delete[WORDSIZE],int number_of_words){                       /* returns if the words is contains the other word */
   if(number_of_words == 0)
       return FALSE;
   if( is_same(word,words_to_delete[number_of_words-1]) ){
       return TRUE;}
   else{
       return contains(word,words_to_delete,number_of_words-1);}
}



void delete_words (FILE* infid, FILE* outfid, char* words_to_delete[WORDSIZE],  int number_of_words)                       /* deletes some words and writes to other file */
{
    char word[WORDSIZE];
    if( ! read_word(infid,word) )
        return;

    if(! contains(word,words_to_delete,number_of_words) )
        write_to_file(outfid,word);

    delete_words(infid,outfid,words_to_delete,number_of_words);

}

void write_to_file(FILE *pFile, char word[20]) {                           /* writes to the file */
    fprintf(pFile,"%s ",word);
}




void clean_file(char* infile, char * outfile, char* words_to_delete[WORDSIZE], int number_of_words)
{
    FILE* infid = fopen(infile,"r");
    FILE* outfid = fopen(outfile,"w");
    delete_words (infid, outfid, words_to_delete, number_of_words);
    fclose(infid);
    fclose(outfid);
}


typedef struct{                       /* a struct for location of maze game */
    int x,y;
}location;


cell_type* get_curr_cell(cell_type maze[][8], cell_type player,location* loc) {                       /* returns the cell of the current player */
    if(maze[loc->x][loc->y] == player)
        return &maze[loc->x][loc->y];
    else
    {
        if(loc->y == 7)
            loc->x++;
        loc->y = (loc->y+1) % 8;
        return get_curr_cell(maze,player,loc);
    }
}

cell_type* get_moved_cell(cell_type maze[][8],location* loc,move_type moveType){                           /* returns the cell after moving */
    switch (moveType) {
        case move_left : return &maze[loc->x][--loc->y];
        case move_right : return &maze[loc->x][++loc->y];
        case move_up : return &maze[--loc->x][loc->y];
        case move_down : return &maze[++loc->x][loc->y];
    }
}


int maze_move(cell_type maze[][8], cell_type player, move_type move)
{
    location loc;
    
	cell_type* curr_cell;
    cell_type* cell_to_move;

	loc.x=0;
    loc.y=0;

    curr_cell = get_curr_cell(maze, player,&loc);
    cell_to_move = get_moved_cell(maze,&loc,move);
    if(*cell_to_move == cell_free)                                                     /* if the cell is free */
    {
        *curr_cell = cell_free;
        *cell_to_move = player;
        return 0;
    }
    else if(*cell_to_move == cell_target)                                         /* if the cell is target */
    {
        *curr_cell = cell_free;
        *cell_to_move = player;
        return 1;
    }

}



void print(char a, int num){                                               /* prints the char a num times */
    if(num <= 1)
        printf("%c",a);
    else {
        printf("%c",a);
        print(a, num - 1);
    }
}

typedef struct {
    int stack[10];
    int size;                       /* a structure for rod */
    int capacity;
}rod;

typedef struct {
    rod rodA,rodB,rodC;                                                /* a structure for all rods */
}rods;


int poll(rod* r){
    return r->stack[--r->size];                       /* removes the last item and returns it */
}

void push(rod* r, int e){                       /* pushes the item to the rod */
    r->stack[r->size++] = e;
}


void print_element(rod* r, int n){                       /* prints the rod element */
    if(n > 0) {
        print(' ', n);
        print('*', 5 + (r->capacity - n) * 2);
        print(' ', n);

        printf("\n");
        print(' ', n);
        print('*', 1);
        print(' ', (r->capacity - n) + 1);
        printf("%d", r->stack[n-1]);
        print(' ', (r->capacity - n+1));
        print('*', 1);
        printf("\n");

        print_element(r,n-1);
    }

}

void fill_stack(rod* r, int n){                                    /* fills the rod */
    if(n == 1)
        push(r,n);
    else
    {
        push(r,n);
        fill_stack(r,n-1);
    }
}

void rods_constructor(rods* rds,int n){                     /* constructor for rods structure that initializes the required values */
    rds->rodA.capacity = n;
    rds->rodA.size = 0;
    fill_stack(&rds->rodA,n);

    rds->rodB.capacity = n;
    rds->rodB.size = 0;

    rds->rodC.capacity = n;
    rds->rodC.size = 0;


}

void print_elements(rods* rds, char start_peg, char end_peg, char aux_peg){                            /* prints all rods */

    printf("========= New Step =========\n");
    printf("========= %c =========\n",start_peg);
    print_element(&rds->rodA,rds->rodA.size);
    printf("========= %c =========\n",end_peg);
    print_element(&rds->rodB,rds->rodB.size);
    printf("========= %c =========\n\n\n",aux_peg);
    print_element(&rds->rodC,rds->rodC.size);

}




void sub_towers(char start_peg, char end_peg, char aux_peg, int n, rods* rds)                            /* helper function for towes_of_hanoi */
{

    if(n == 1){
        push(&(rds->rodB),poll(&rds->rodA));                    /* move disk 1 from start to end */
        print_elements(rds,start_peg,end_peg,aux_peg);
    }
    else{


        rod temp = rds->rodB;
        rds->rodB = rds->rodC;
        rds->rodC = temp;

        sub_towers(start_peg,aux_peg,end_peg,n-1,rds);

        temp = rds->rodB;
        rds->rodB = rds->rodC;
        rds->rodC = temp;


        push(&rds->rodB,poll(&rds->rodA));        /* move disk n from start to end */
        print_elements(rds,start_peg,end_peg,aux_peg);


        temp = rds->rodA;
        rds->rodA = rds->rodC;
        rds->rodC = temp;

        sub_towers(aux_peg,end_peg,start_peg,n-1,rds);

        temp = rds->rodA;
        rds->rodA = rds->rodC;
        rds->rodC = temp;

    }
}


void towers_of_hanoi(char start_peg, char end_peg, char aux_peg, int n){

    static rods rds;
    rods_constructor(&rds,n);                                                                                       /* construct and prints first state */

    print_elements(&rds,start_peg,end_peg,aux_peg);
    sub_towers(start_peg,end_peg,aux_peg,n,&rds);

}
/*
								                     My test cases

int main(){*/

    /*
    char *words[WORDSIZE] = {"ali","veli","mali"};
    char word[] = "ali";

    int a = contains(word,words,3);

    printf("%d",a);

    char infile[] ="f1.txt";
    char outfile[] ="f2.txt";

    clean_file(infile,outfile,words,3);
*/


  /*
  cell_type maze[][8] = {
           {cell_wall,cell_wall,cell_wall,cell_target,cell_wall,cell_wall,cell_wall,cell_wall}
          ,{cell_wall,cell_free,cell_free,cell_free,cell_wall,cell_free,cell_free,cell_wall}
          ,{cell_wall,cell_free,cell_wall,cell_free,cell_wall,cell_free,cell_wall,cell_wall}
          ,{cell_wall,cell_free,cell_wall,cell_free,cell_wall,cell_free,cell_free,cell_wall}
          ,{cell_wall,cell_free,cell_wall,cell_free,cell_free,cell_wall,cell_free,cell_wall}
          ,{cell_wall,cell_free,cell_wall,cell_wall,cell_free,cell_free,cell_free,cell_wall}
          ,{cell_wall,cell_free,cell_p2,cell_free,cell_free,cell_wall,cell_p1,cell_wall}
          ,{cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall,cell_wall}
  };

    short isEnd;
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_left);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_left);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_left);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d",isEnd);
    isEnd = maze_move(maze,cell_p1,move_up);
    printf("%d\n",isEnd);

    print_maze(maze);
*/

/*
  rod r;
  r.capacity = 5;
  r.size = 0;
  push(&r,5);
  push(&r,4);
  push(&r,3);
  push(&r,2);
  push(&r,1);

  print_element(&r);
    print_element(&r);
    print_element(&r);
    print_element(&r);
    print_element(&r);
*/
/*

    towers_of_hanoi('s','e','a',7);



    return 0;
}*/
