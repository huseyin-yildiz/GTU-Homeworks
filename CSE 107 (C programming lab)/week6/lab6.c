#include<stdio.h>

void fill_matrix(int *matrix, int m, int n ){
	printf("Matrix: \n");
	for(int i=0; i<m; i++)
	{	
		for(int j=0; j<n; j++)
		{
			int x = n*i + j + 1;
			int y = 2*x*x-3 ;
			*((matrix+i*n) + j) = y;
			printf("%-5d",*((matrix+i*n) + j) );
	
		}
		printf("\n");
	}
}


float average_finder(int *matrix, int m, int n){
	float sum = 0;
	float number = 0;
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
		{
			if((i+j) %2 == 0)
			{
				sum += *((matrix+i*n) + j);
				number++;
			}
		}
		
		float average = sum / number;
		return average;
}





void intervew (const char s1[], const char s2[], char * s3){

int ia =0;
int ib =0;
int i=0;

while( s1[ia] != '\0' || s2[ib] != '\0' )
{
	if(s1[ia] != '\0')
	{
		*(s3+i) = s1[ia];
		ia++;
		i++;
	}
	
	if(s2[ib] != '\0')
	{
		*(s3+i) = s2[ib];
		ib++;
		i++;
	}

}



*(s3+i) = '\0';


}




int main(){

int matrix1[3][5];

fill_matrix(&matrix1[0][0],3,5);
float average = average_finder(&matrix1[0][0],3,5);

printf("Result = %.1f\n\n",average );


int matrix2[4][9];

fill_matrix(&matrix2[0][0],4,9);
average = average_finder(&matrix2[0][0],4,9);

printf("Result = %.1f\n",average );


char s[100];

char s1[] = "abcdefg";
char s2[] = "1234";

intervew (s1, s2, &s[0]);

printf("%s\n",s );



}