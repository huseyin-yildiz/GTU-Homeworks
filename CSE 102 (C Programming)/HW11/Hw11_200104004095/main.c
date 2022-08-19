#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "LinkedLists.h"

#define MOVIE_FILE "Movies.txt"
#define INITIAL_ARRAY 100

typedef enum {
    Budget,
    Genre,
    Name,
    Score,
    Year
}sorting;

typedef struct{
    double budget;
    char genre[MAX_G_SIZE];                                 /* these are allocated in heap when we allocate the struct */
    char name[INITIAL_ARRAY];
    double score;
    int year;
}Movie;

typedef struct {
    char name[MAX_G_SIZE];
    int size;
}genre;

typedef struct {
    movie_budget *movieBudgets;
    movie_name *movieNames;
    int size;                                     /* required structs */
    genre genres[INITIAL_ARRAY];
    int genreSize;
}movieList;

typedef struct {
    movie_name *movieName;
    movie_budget *movieBudget;
}movieResult;

int addGenre(movieList * movies,char name[] ){                                                       /* adds genre to the genre list */
    int i;
    for (i = 0; i < movies->genreSize; ++i) {
        if(strcmp(name,movies->genres[i].name) == 0){
            movies->genres[i].size = movies->genres[i].size+1;
            return i;
        }
    }
    if(i == movies->genreSize) {
        strcpy(movies->genres[movies->genreSize].name, name);
        movies->genres[movies->genreSize].size = 0;
        movies->genreSize = movies->genreSize+1;
    }
    return (movies->genreSize-1);
}

void downCase(char name[], char** out){                                       /* downs the string Like ASD -> asd */
    int i;
    int len = (int)strlen(name);
    *out = calloc(sizeof(char), len+1);

    for(i=0; i<len; i++)
    {
        if(name[i] > 64 && name[i] <91)
            (*out)[i] =  (char)((int)name[i]+32);
        else{
            char a = name[i];
            (*out)[i] = a;
        }
    }
    if((*out)[len] != '\0')
        (*out)[len] = '\0';

}


movieResult findMovie(movieList * movies, char name[]) {                                     /* finds a movie if its not in then returns -1 */
    movieResult result;
    movie_budget *movieBudget=NULL;
    movie_name  *movieName=NULL;

    char *out1, *out2;



  //  if(strcmp(name,"the phantom of the opera") == 0)
    //    printf("aaa");

    downCase(name, &out1);

    movieBudget = movies->movieBudgets;
    while (movieBudget != NULL){
        downCase(movieBudget->name,&out2);
           if(strcmp(out2,out1)==0){
               free(out2);
               break;
           }
           movieBudget = (movie_budget *) movieBudget->next;
           free(out2);
           out2 = NULL;
    }
    if(movieBudget != NULL){
        movieName = movies->movieNames;
        while (movieName != NULL){
            downCase(movieName->name,&out2);
            if(strcmp(out2,out1)==0){
                free(out2);
                break;
            }
            movieName = (movie_name *) movieName->next;
        }
    }
    free(out1);
    result.movieName = movieName;
    result.movieBudget = movieBudget;
    if(movieName == NULL && movieBudget!= NULL)
        printList(movies->movieNames);
    return result;
}

int getMovieSize(char file_name[]){                                     /* returns movies size in the text file */
    int i=0;
    FILE * file = fopen(file_name,"r");
    char ch;
    for (ch = (char)getc(file); ch != EOF; ch = (char)getc(file))
        if (ch == '\n')
            i++;

    fclose(file);
    return i;
}



void addMovie(movieList *movies, Movie movie) {                                            /* adds a movie to the movie array */
    movieResult result = findMovie(movies,movie.name);
    //if(strcmp(movie.name,"the phantom of the opera") == 0)
      //  printf("aaa");
    if( result.movieBudget != NULL)                                    /* updates the movie */
    {
        result.movieBudget->year = movie.year;
        result.movieBudget->budget = movie.budget;
        strcpy(result.movieName->genre,movie.genre);
        result.movieName->score = movie.score;
    }
    else {                                                                              /* adds new movie */
        movie_budget *movieBudget = new_movie_budget(movie.budget,movie.year,movie.name);
        movie_name  *movieName = new_movie_name(movie.genre,movie.name,movie.score);

        movies->movieBudgets = insert_sorted_budgets(movies->movieBudgets,movieBudget,yearComparator,budgetComparator);
        insert_names(&movies->movieNames,movieName);


        movies->size = movies->size +1;
    }
}

char* readUntil(FILE* file, char ch, char text[]){                                     /* reads until the character in the file */
    int i=0;
    do {
        char a = (char)getc(file);
        text[i] = a;
    }while(text[i++] != ch && i < 100);
    text[i-1] = '\0';
    return text;

}


void readMovies(char fileName[], movieList * movies){            /* reads all movies from the file and returns size and movies array */
    FILE *file = fopen(fileName,"r");
    Movie movie;
    char genre[20];
    /*  char name[100];*/
    char budget[25];                                    /* temporary variables to take inputs */
    char score[10];
    char year[10];
    int i=0;
    int size = getMovieSize(fileName);
    while(i++ < size ) {
        char *ptr;
        readUntil(file, ',',budget);
        readUntil(file, ',',genre);
        readUntil(file, ',',movie.name);
        readUntil(file, ',',score);
        readUntil(file, '\n',year);
        if(strcmp(budget,"budget") == 0)
            continue;


        if (strcmp(budget, "unknown") == 0)
            movie.budget = -1.0;
        else {
            ptr = &budget[strlen(budget)];
            movie.budget = strtod(budget, &ptr);
        }

        /*    int len;
            len = strlen(name);
            if(movie.name != NULL) {
                movie.name = NULL;
            }
            if(movies->size == 3562)
                printf("a");
           // movie.name = malloc(sizeof(char)*len);
            if(movie.name != NULL)
                strcpy(movie.name, name);
    */

        ptr = &score[strlen(score)];
        movie.score = strtod(score, &ptr);

        movie.year = atoi(year);

        addGenre(movies,genre);
        strcpy(movie.genre,genre);

        if(movies->size == -1)
            printf("a");
        /*   printf("%d\n",movies->size);          */
        addMovie(movies, movie);
/*
        if(budget != NULL)
            free(budget);
            budget = NULL;
        if(genre != NULL)
            free(genre);
            genre = NULL;
        if(name != NULL)
            free(name);
            name = NULL;
        if(score != NULL)
            free(score);
            score = NULL;
        if(year != NULL)
            free(year);
            year = NULL;
*/
    }

}


void freq_genres(movieList * movies){                                                /* selection 7 */
    int i;
    for (i = 0; i < movies->genreSize; ++i) {
        printf("%-20s %d\n",movies->genres[i].name,movies->genres[i].size);
    }
}

void average_imdb(movieList * movies){                                       /* selection 6 */
    double imdb = 0.0;
    movie_name *movieName;
    for (movieName = movies->movieNames; movieName!=NULL ; movieName = (movie_name *) movieName->next) {
        imdb += movieName->score;
    }
    imdb  /= (double)(movies->size);

    printf("Average: %lf",imdb);
}



void all_information(movieList * movies){                                       /* selection 5 */
    char *name = calloc(sizeof(char),100);
    movieResult result;
    printf("Please enter the name of the movie:\n");

    fflush(stdin);
    fgets(name, 100, stdin);
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';

    result = findMovie(movies,name);
    if(result.movieBudget != NULL){
        if (result.movieBudget->budget != -1.0)
            printf("\nBudget: %.2lf\n", result.movieBudget->budget);
        else
            printf("\nBudget: Unknown\n");
        printf("Genre:  %s\n", result.movieName->genre);
        printf("Name:   %s\n", result.movieBudget->name);
        printf("Score:  %.1lf\n", result.movieName->score);
        printf("Year:   %d\n", result.movieBudget->year);
        return;
    }
    printf("The movie %s not found.\n",name);


}


void list_genres( movieList * movies){                                       /* selection 2 */
    int i;
    for (i = 0; i < movies->genreSize; ++i) {
        printf("%s\n",movies->genres[i].name);
    }
}



void through_scores(movieList *movies){                                       /* selection 4 */
    double score;
    movie_name *movieName;
    int less_greater;
    short flag;

    printf("Enter a score:\n");
    scanf("%lf",&score);
    printf("Less (0) or Greater(1) %.1lf:",score);
    scanf("%d",&less_greater);

    flag = 0;
    for(movieName=movies->movieNames; movieName!=NULL; movieName= (movie_name *) movieName->next){
        if( ( less_greater == 0 && (movieName->score) <= score )|| (less_greater == 1 && (movieName->score) >= score) ){
            flag = 1;
            printf("%s\n",movieName->name);
        }

    }
    if(flag == 0) {
        printf("TRY AGAIN\n");
        through_scores(movies);
    }

}


void through_years(movieList *movies){                                       /* selection 3 */
    int year;
    movie_budget *movieBudget;
    int less_greater;
    short flag;

    printf("Enter a year:\n");
    scanf("%d",&year);
    printf("Less (0) or Greater(1) %d:",year);
    scanf("%d",&less_greater);

    flag = 0;
    for(movieBudget=movies->movieBudgets; movieBudget!=NULL; movieBudget= (movie_budget *) movieBudget->next){
        if( ( less_greater == 0 && (movieBudget->year) <= year )|| (less_greater == 1 && (movieBudget->year) >= year) ){
            flag = 1;
            printf("%s\n",movieBudget->name);
        }

    }
    if(flag == 0) {
        printf("TRY AGAIN\n");
        through_years(movies);
    }

}

int takeInt(char text[]){
    int val;
    printf("%s: ",text);
    scanf("%d",&val);
    return val;
}

void sort(movieList * movies, sorting sortingAccording){
    short sortingCase;
    comparator2 *cmp1, *cmp2;
    switch (sortingAccording) {
        case Budget:sortingCase = 1; cmp1 = (int (*)(movie_name *, movie_name *)) budgetComparator; cmp2 = (int (*)(
            movie_name *, movie_name *)) yearComparator; break;
        case Genre: sortingCase = 2; cmp1 = (int (*)(movie_name *, movie_name *)) (int (*)(movie_budget *,
                                                                                           movie_budget *)) genreComparator; cmp2 = (int (*)(
            movie_name *, movie_name *)) (int (*)(
            movie_budget *, movie_budget *)) scoreComparator; break;
        case Name: sortingCase = 1; cmp1 = (int (*)(movie_name *, movie_name *)) nameComparator; cmp2 = (int (*)(
            movie_name *, movie_name *)) yearComparator; break;
        case Score: sortingCase = 2; cmp1 = (int (*)(movie_name *, movie_name *)) (int (*)(movie_budget *,
                                                                                           movie_budget *)) scoreComparator; cmp2 = (int (*)(
            movie_name *, movie_name *)) (int (*)(
            movie_budget *, movie_budget *)) genreComparator; break;
        case Year: sortingCase = 1; cmp1 = (int (*)(movie_name *, movie_name *)) yearComparator; cmp2 = (int (*)(
            movie_name *, movie_name *)) budgetComparator; break;
    }

    if(sortingCase == 1){           // movieBudges sort
        movie_budget *head, *temp;
        head = (movie_budget *) movies->movieBudgets->next;
        movies->movieBudgets->next = NULL;

        int i = 0;
        while (head!=NULL){

            temp = head;
            head = (movie_budget *) head->next;
            temp->next = NULL;
            i++;
            movies->movieBudgets = insert_sorted_budgets(movies->movieBudgets, temp,
                                                         (int (*)(movie_budget *, movie_budget *)) cmp1,
                                                         (int (*)(movie_budget *, movie_budget *)) cmp2);
        }
        printf("%d\n",i);
    }
    else{
        movie_name *head, *temp;
        head = (movie_name *) movies->movieNames->next;
        movies->movieNames->next = NULL;

        while (head!=NULL){
            temp = head;
            head = (movie_name *) head->next;
            temp->next = NULL;

            movies->movieNames = insert_sorted_names(movies->movieNames,temp,cmp1,cmp2);
        }
    }

}

movieResult getMovie(movieList *movies, short sortingCase, int index){
    movieResult result;
    if(sortingCase == 2){
        movie_name *temp;
        int i=0;
        for(temp = movies->movieNames; temp!=NULL; temp= (movie_name *) temp->next){
            i++;
            if(i == index){
                result = findMovie(movies, temp->name);
                return result;
            }

        }
        return  result;
    }
    if(sortingCase == 1){
        movie_budget *temp;
        int i=0;
        for(temp = movies->movieBudgets; temp!=NULL; temp= (movie_budget *) temp->next){
            i++;
            if(i == index){
                result = findMovie(movies, temp->name);
                return result;
            }
        }
        return result;
    }
    else
        return result;
}


void list_sorted(movieList * movies){
    int selection;
    short sortingCase;
    char *sortText;
    movieResult result;
    printf("1. Budget\n");
    printf("2. Genre\n");
    printf("3. Name\n");
    printf("4. Score\n");
    printf("5. Year\n");

    selection = takeInt("Please Select an operation");

    switch (selection) {
        case 1: sort(movies,Budget);sortingCase=1; sortText="budget"; break;
        case 2: sort(movies,Genre);sortingCase=2; sortText="genre"; break;
        case 3: sort(movies,Name);sortingCase=1; sortText="name"; break;
        case 4: sort(movies,Score);sortingCase=2; sortText="score"; break;
        case 5: sort(movies,Year);sortingCase=1; sortText="year"; break;
        default:
            printf("\nWrong selection\n");
            return list_sorted(movies);
    }

    printf("1. Single Selection\n");
    printf("2. Multiple Selection\n");

    selection = takeInt("Please Select an operation");

    if(selection == 1){

        int index = takeInt("Enter value");
        result = getMovie(movies,sortingCase,index);
        printf("\n%d. Movie\n",index);
        if(result.movieBudget->budget == -1.0)
            printf("%-20s %-20s %-20s %-5.1lf %d\n","Unknown",result.movieName->genre, result.movieName->name, result.movieName->score, result.movieBudget->year);
        else
            printf("%-20lf %-20s %-20s %-5.1lf %d\n",result.movieBudget->budget,result.movieName->genre, result.movieName->name, result.movieName->score, result.movieBudget->year);
    } else if(selection == 2){
        int start, end, i;
        start = takeInt("Enter start value");
        end = takeInt("Enter end value");
        printf("\nMovies between %d and %d, sorted by %s.\n",start,end,sortText);
        for (i=start; i<=end; i++){
            result = getMovie(movies,sortingCase,i);
            if(result.movieBudget->budget == -1.0)
                printf("%-20s %-20s %-20s %-5.1lf %d\n","Unknown",result.movieName->genre, result.movieName->name, result.movieName->score, result.movieBudget->year);
            else
                printf("%-20lf %-20s %-20s %-5.1lf %d\n",result.movieBudget->budget,result.movieName->genre, result.movieName->name, result.movieName->score, result.movieBudget->year);
        }
    } else{
        printf("TRY AGAIN");
        list_sorted(movies);
    }
}


void main_menu(movieList * movies){                                       /* main menu for the program */
    int selection;

    printf("1. List of the Sorted Data\n");
    printf("2. List of the Genres\n");
    printf("3. List of the Movie Through the Years\n");
    printf("4. List of the Movie Through the Scores\n");
    printf("5. All information of a Single Movie\n");
    printf("6. Average of the IMDB Scores\n");
    printf("7. Frequence of the Genres\n");
    printf("8.Exit\n\n");

    printf("Select an operation: ");
    scanf("%d",&selection);

    switch (selection) {
        case 1: list_sorted(movies); main_menu(movies); break;
        case 2: list_genres(movies); main_menu(movies); break;
        case 3: through_years(movies); main_menu(movies); break;
        case 4: through_scores(movies); main_menu(movies); break;
        case 5: all_information(movies); main_menu(movies); break;
        case 6: average_imdb(movies); main_menu(movies);break;
        case 7: freq_genres(movies); main_menu(movies); break;
        case 8: break;
        default:
            printf("Wrong Selection\n\n");main_menu(movies);
    }

}







int main() {                                                   /* main funtion of the program */
    movieList myMovies={.movieBudgets=NULL,.movieNames=NULL};


    myMovies.size =0;
    myMovies.genreSize = 0;
    readMovies(MOVIE_FILE,&myMovies);

    main_menu(&myMovies);

}



