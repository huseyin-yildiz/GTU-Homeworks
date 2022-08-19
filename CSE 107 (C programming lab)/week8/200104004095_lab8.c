#include <stdio.h>
#include "math.h"

#define SIZE 3

typedef struct {                                                                 /* the matrix structure */
    double values[SIZE][SIZE];
    double determinant;
}matrix;


void determinant_of_matrix(matrix* initial_matrix){                                                               /* finds the determinant of the matrix */
    float det = 0;
    det += (initial_matrix->values[0][2])*(initial_matrix->values[1][1])*(initial_matrix->values[2][0]);
    det += (initial_matrix->values[0][0])*(initial_matrix->values[1][2])*(initial_matrix->values[2][1]);
    det += (initial_matrix->values[0][1])*(initial_matrix->values[1][0])*(initial_matrix->values[2][2]);

    det -= (initial_matrix->values[0][0])*(initial_matrix->values[1][1])*(initial_matrix->values[2][2]);
    det -= (initial_matrix->values[0][1])*(initial_matrix->values[1][2])*(initial_matrix->values[2][0]);
    det -= (initial_matrix->values[0][2])*(initial_matrix->values[1][0])*(initial_matrix->values[2][1]);

    initial_matrix->determinant = det;
}





void inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix){                                          /* finds invers of matrix if determinant is not 0 */
    determinant_of_matrix(initial_matrix);

    float det = initial_matrix->determinant;
    if(det != 0)
    {
        inverted_matrix->values[0][0] = (1.0/det) * initial_matrix->values[1][1]*initial_matrix->values[2][2] - initial_matrix->values[1][2]*initial_matrix->values[2][1];
        inverted_matrix->values[0][1] = (1.0/det) * initial_matrix->values[0][2]*initial_matrix->values[2][1] - initial_matrix->values[0][1]*initial_matrix->values[2][2];
        inverted_matrix->values[0][2] = (1.0/det) * initial_matrix->values[0][1]*initial_matrix->values[1][2] - initial_matrix->values[0][2]*initial_matrix->values[1][1];

        inverted_matrix->values[1][0] = (1.0/det) * initial_matrix->values[1][2]*initial_matrix->values[2][0] - initial_matrix->values[1][0]*initial_matrix->values[2][2];
        inverted_matrix->values[1][1] = (1.0/det) * initial_matrix->values[0][0]*initial_matrix->values[2][2] - initial_matrix->values[0][2]*initial_matrix->values[2][0];
        inverted_matrix->values[1][2] = (1.0/det) * initial_matrix->values[0][2]*initial_matrix->values[1][0] - initial_matrix->values[0][0]*initial_matrix->values[1][2];

        inverted_matrix->values[2][0] = (1.0/det) * initial_matrix->values[1][0]*initial_matrix->values[2][1] - initial_matrix->values[1][1]*initial_matrix->values[2][0];
        inverted_matrix->values[2][1] = (1.0/det) * initial_matrix->values[0][1]*initial_matrix->values[2][1] - initial_matrix->values[0][0]*initial_matrix->values[2][1];
        inverted_matrix->values[2][2] = (1.0/det) * initial_matrix->values[0][0]*initial_matrix->values[1][1] - initial_matrix->values[0][1]*initial_matrix->values[1][0];

    }
}


void print_matrix(matrix* mat){                                          /* prints the given matrix */
    int i,j;
    for(i=0; i<SIZE; i++)
    {
        for(j=0; j<SIZE; j++)
            printf("%10.4f",mat->values[i][j]);
        printf("\n");
    }
    printf("\n");
}


typedef struct {                                                          /*  the vector structure */
    double x,y,z;
}vector;


double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec){
double angle, up, down;

output_vec->x = vec_1.y*vec_2.z - vec_1.z*vec_2.y;
output_vec->y = -1.0* (vec_1.x*vec_2.z - vec_1.z*vec_2.x);          /* vector cross product*/
output_vec->z = vec_1.x*vec_2.y - vec_1.y*vec_2.x;

up = vec_1.x*vec_2.x + vec_1.y*vec_2.y + vec_1.z*vec_2.z;
down = sqrt( vec_1.x*vec_1.x + vec_1.y*vec_1.y + vec_1.z*vec_1.z );

angle = acos(up/down);

printf("angle: %lf\n",angle );

return angle;

}



typedef struct{
    float c1,c2,c3;                                                                       /* structure for third polynomial */
}third_order_polynomial;

typedef struct{
    float c1,c2,c3,c4;                                                                       /* structure for third polynomial */
}polynomial;



polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b)
{
        /* there was no enoughh time to implement */
}

int main() {
    matrix mtrx;


    printf("Enter matrix values");
    int i,j;
    for (i=0; i<SIZE; i++)
        for (j=0; j<SIZE; j++)
            scanf("%lf",&(mtrx.values[i][j]));


    matrix inverted;

    print_matrix(&mtrx);

    inverse_matrix(&mtrx, &inverted);
    print_matrix(&inverted);


    vector v1,v2,v3;
    printf("Enter vector 1");
    scanf("%lf %lf %lf",&v1.x,&v1.y,&v1.z);

    printf("Enter vector 2");
    scanf("%lf %lf %lf",&v2.x,&v2.y,&v2.z);

    double a =find_orthogonal(v1,v2,&v3);

    printf("ortho: %lf %lf %lf",v3.x,v3.y,v3.z);

    printf("angle: %lf",a);



}