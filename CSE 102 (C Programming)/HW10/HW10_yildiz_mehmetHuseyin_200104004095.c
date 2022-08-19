#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOVIE_FILE "Movies.txt"
#define INITIAL_ARRAY 100

typedef struct{
    double budget;
    int genre;
    char name[INITIAL_ARRAY];                                   /* i only did this one fixed array because about at the middle of the text file i took a weird malloc error */
    double score;
    int year;
}Movie;


typedef struct {
    Movie* array;
    int size, capacity;                                     /* required structs */
    char genres[INITIAL_ARRAY][20];
    int genreSize;
}movieArray;


int addGenre(movieArray* movies,char name[] ){                                                       /* adds genre to the genre list */
    int i;
    for (i = 0; i < movies->genreSize; ++i) {
        if(strcmp(name,movies->genres[i]) == 0)
            return i;
    }
    if(i == movies->genreSize) {
        strcpy(movies->genres[movies->genreSize], name);
        movies->genreSize = movies->genreSize+1;
    }
    return (movies->genreSize-1);
}




int findMovie(movieArray* movieArray1, char name[]) {                                     /* finds a movie if its not in then returns -1 */
    int i;
    for (i = 0; i < movieArray1->size; i++)
    {
        if(movieArray1->array[i].name != (char*)NULL)
            if (strcmp(movieArray1->array[i].name, name) == 0)
                return i;
    }
    return -1;
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


void increaseCapacity(movieArray* movieArray1){                                     /* increases the capacity of the movie array */
    int i;
    Movie* newArray;
    movieArray1->capacity *= 2;
    newArray = calloc(sizeof(Movie), movieArray1->capacity);
    for(i=0; i<movieArray1->size; i++){
         newArray[i] = movieArray1->array[i];
   /*     movieArray1->array[i].name = calloc(sizeof(char),strlen(temp[i].name));
        strcpy(movieArray1->array[i].name, temp[i].name);       */
    }

    free(movieArray1->array);
    movieArray1->array = newArray;

}

void addMovie(movieArray* movieArray1, Movie movie) {                                            /* adds a movie to the movie array */

    int index = findMovie(movieArray1,movie.name);
    if( index != -1)
    {
        movieArray1->array[index] = movie;
  /*      strcpy(movieArray1->array[index].name , movie.name);  */
    }
    else {
        if (movieArray1->capacity == movieArray1->size)
            increaseCapacity(movieArray1);
        movieArray1->array[movieArray1->size] = movie;
      /*  movieArray1->array[movieArray1->size].name = movie.name;      */
        movieArray1->size = movieArray1->size +1;
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


void readMovies(char fileName[], movieArray* movies){            /* reads all movies from the file and returns size and movies array */
    FILE *file = fopen(fileName,"r");
    Movie movie;
    char genre[20];
  /*  char name[100];*/
    char budget[25];                                    /* temporary variables to take inputs */
    char score[10];
    char year[10];
    int i=0;
    while(i++ < movies->capacity ) {
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


        movie.genre = addGenre(movies,genre);


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


void freq_genres(movieArray* movies){                                                /* selection 7 */
    int i;
    int *genres = calloc(sizeof(int),movies->genreSize);
    for (i = 0; i < movies->size; ++i) {
        genres[movies->array[i].genre] = genres[movies->array[i].genre] + 1;
    }

    for (i = 0; i < movies->genreSize; ++i) {
        printf("%-20s %d\n",movies->genres[i],genres[i]);
    }
}

void average_imdb(movieArray* movies){                                       /* selection 6 */
    double imdb = 0.0;
    int i;
    for (i = 0; i < movies->size ; ++i) {
        imdb += (float)(movies->array[i].score);
    }
    imdb  /= (movies->size);

    printf("Average: %lf",imdb);
}

void downCase(char name[], char** out){                                       /* downs the string Like ASD -> asd */
    int i;
    int len = (int)strlen(name);
    *out = calloc(sizeof(char), len);

    for(i=0; i<len; i++)
    {
        if(name[i] > 64 && name[i] <91)
            (*out)[i] =  (char)((int)name[i]+32);
        else
            (*out)[i] = name[i];
    }

}


void all_information(movieArray* movies){                                       /* selection 5 */
    char *name = calloc(sizeof(char),100);
    char *out1;
    char *out2;
    int i;
    char temp[100];
    printf("Please enter the name of the movie:\n");

    fflush(stdin);
    fgets(name, 100, stdin);
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';

    downCase(name,&out1);


    for(i=0; i<movies->size; i++ ){
        strcpy(temp, movies->array[i].name);
        downCase(temp,&out2);
        if(strcmp(out1,out2) == 0)
        {
            Movie* mv = &(movies->array[i]);
            if(mv->budget != -1.0)
                printf("\nBudget: %.2lf\n",mv->budget);
            else
                printf("\nBudget: Unknown\n",mv->budget);
            printf("Genre:  %s\n",movies->genres[mv->genre]);
            printf("Name:   %s\n",mv->name);
            printf("Score:  %.1lf\n",mv->score);
            printf("Year:   %d\n",mv->year);
            return;
        }
    }

    printf("The movie %s not found.\n",name);




}


void list_genres( movieArray * movies){                                       /* selection 2 */
    int i;
    for (i = 0; i < movies->genreSize; ++i) {
        printf("%s\n",movies->genres[i]);
    }
}



void through_scores(movieArray *movies){                                       /* selection 4 */
    double score;
    int i;
    int less_greater;
    short flag;

    printf("Enter a score:\n");
    scanf("%lf",&score);
    printf("Less (0) or Greater(1) %.1lf:",score);
    scanf("%d",&less_greater);

    flag = 0;
    for(i=0; i<movies->size; i++){
        if( ( less_greater == 0 && (movies->array[i].score) <= score )
                    || (less_greater == 1 && (movies->array[i].score) >= score) ){

                flag = 1;
                printf("%s\n",movies->array[i].name);
        }

    }
    if(flag == 0) {
        printf("TRY AGAIN\n");
        through_scores(movies);
    }

}


void through_years(movieArray *movies){                                       /* selection 3 */
    int year;
    int i;
    int less_greater;
    short flag;

    printf("Enter a year:\n");
    scanf("%d",&year);
    printf("Less (0) or Greater(1) %d:",year);
    scanf("%d",&less_greater);

    flag = 0;
    for(i=0; i<movies->size; i++){
        if( ( less_greater == 0 && (movies->array[i].year) <= year )
            || (less_greater == 1 && (movies->array[i].year) >= year) ){

            flag = 1;
            printf("%s\n",movies->array[i].name);
        }

    }
    if(flag == 0) {
        printf("TRY AGAIN\n");
        through_years(movies);
    }

}



void main_menu(movieArray* movies){                                       /* main menu for the program */
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
        case 1: main_menu(movies); break;
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
    int msize;
    int i;

    movieArray myMovies;
    msize = getMovieSize(MOVIE_FILE);

    myMovies.size =0;
    myMovies.capacity=msize;
    myMovies.array = calloc(sizeof(Movie),msize);
    myMovies.genreSize = 0;


   readMovies(MOVIE_FILE,&myMovies);

    main_menu(&myMovies);

}



