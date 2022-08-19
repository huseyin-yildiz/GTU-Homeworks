#include <stdio.h>
#include "string.h"

#define MAX_NAME 20
#define MAX_ARRAY 100


                        /* PART 1 */
typedef struct {
    float x,y;
}point;

typedef struct {
    point point1, point2, point3;                                               /* required structures */
    float slope;
}line;


void calculate_line_values(line* myLine){                                                         /* calculates unknown values  */
    float b;
    float y_diff = (myLine->point1.y) - (myLine->point2.y);
    float x_diff = (myLine->point1.x) - (myLine->point2.x);

    myLine->slope = y_diff / x_diff;
    b = (myLine->point1.y) - (myLine->slope * (myLine->point1.x));
    myLine->point3.y = (myLine->slope) * (myLine->point3.x) + b;

}


                /* PART 2 */
    typedef struct {                                                /* required structures */
        float midterm, final, homework;
    }grades;

    typedef struct {
        int id;
        char name[MAX_NAME];
        char  surname[MAX_NAME];
        grades grades1;
    }student;

    grades calculate_average(student students[], float size){                               /* calculates average grades */
        grades average = {0,0,0};
        int i;
        for (i = 0; i < size; ++i) {
            average.homework += students[i].grades1.homework;
            average.midterm += students[i].grades1.midterm;
            average.final += students[i].grades1.final;
        }
        average.final /= size;
        average.midterm /= size;
        average.homework /= size;

        return average;
    }


    student* search_student(int id, student students[], int size ){                             /* searches the student with given id */
        int i;
        for(i=0; i<size; i++)
        {
            if(students[i].id == id)
                return &students[i];
        }
        printf("Error : The given id is not found in the students");
        return NULL;
    }



                    /* PART 3 */

    typedef struct {                                                                        /* required structures */
        char name[MAX_NAME];
        char platforms[MAX_ARRAY];
        int platform_size;
        float score;
    }game;

    float game_score_average(game games[MAX_ARRAY], int size){                   /* average of score of the games */
        int i;
        float average = 0;
        for (i = 0; i < size; ++i) {
            average += games[i].score;
        }
        average /= (float)size;
        return average;
    }

    void games_of_platforms(game games[MAX_ARRAY], int size){            /* games of platforms but there was no time to implement */
        int i,j;
        int platform_size = 0;
        int sizes[MAX_ARRAY];
        char platforms[MAX_ARRAY];
/*
        for(i=0; i<size; i++)
        {
            for(j=0; j<platform_size; j++)

        }
*/
    }



int main() {

    int student_size;
    int game_size;
    int id;
    int i;
    student students[MAX_ARRAY];
    student* found_student;

    line newLine;
    printf("Enter point 1: ");
    scanf("%f %f",&(newLine.point1.x), &(newLine.point1.y) );

    printf("Enter point 2: ");
    scanf("%f %f",&(newLine.point2.x), &(newLine.point2.y) );

    printf("Enter x of point 3: ");
    scanf("%f",&(newLine.point3.x) );

    calculate_line_values(&newLine);

    printf("The slope: %f  The y of point 3 : %f",newLine.slope, newLine.point3.y);

    /* PART 2 */


    printf("How many students will you enter: ");
    scanf("%d",&student_size);                                                          /* takes student size and infromation */

    for(i=0; i<student_size; i++){
        printf("Name: ");
        scanf("%s",students[i].name);

        printf("Surname: ");
        scanf("%s",students[i].surname);

        printf("Id: ");
        scanf("%d",&(students[i].id));

        printf("Midterm: ");
        scanf("%f",&(students[i].grades1.midterm));

        printf("Final: ");
        scanf("%f",&(students[i].grades1.final));

        printf("Homeworks: ");
        scanf("%f",&(students[i].grades1.homework));

    }

    grades average = calculate_average(students, (float)student_size);

    printf("Midterm average: %f Final average: %f  Homework average: %f\n",
           average.midterm, average.final, average.homework);



    printf("Enter the id to search : ");                             /* takes id and search */
    scanf("%d",&id );
    found_student = search_student(id, students, student_size);

    if(found_student != NULL)
    {
        printf("Id: %d\n", found_student->id);
        printf("Name: %s\n",found_student->name);
        printf("Surname: %s\n",found_student->surname);
        printf("Midterm: %f\n",found_student->grades1.midterm);
        printf("Final: %f\n",found_student->grades1.final);
        printf("Homeworks: %f\n",found_student->grades1.homework);
    }



    /* PART 3 */

    printf("Enter number of the games: ");                                      /* takes size of games and takes information */
    scanf("%d",&game_size);

    game games[MAX_ARRAY];

    for (i = 0; i < game_size; ++i) {
        int j;
        printf("Name: ");
        scanf("%s",games[i].name);

        printf("Score: ");
        scanf("%f",&(games[i].score));

        printf("Enter number of platforms: ");
        scanf("%d",&(games[i].platform_size));

        for (j = 0; j < games[i].platform_size; ++j) {
            printf("Enter platform name: ");
            scanf("%s", &(games[i].platforms[j]));
        }

    }

    printf("Average of the score of the games: %f", game_score_average(games,game_size));




    return 0;




}
