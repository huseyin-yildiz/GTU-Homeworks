#include<stdio.h>

int main()
{
	srand(time(NULL));
	
	int matrix[10][10];
	int arr[10];
	
	for(int i =0; i<10; i++)
	{
		for(int j=0; j<10; j++)
			{
			matrix[i][j] = 20 + rand()%79;
			arr[i]=0;
		}
	}
	
	
		for(int i =0; i<10; i++)
	{
		for(int j=0; j<10; j++)
			printf("%d ",matrix[i][j]);
		printf("\n");
	}
	printf("\n");
	
	
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
			arr[i] += matrix[j][i]   ;
		printf("%d ",arr[i]);
	}
	
	
	

	return 0;
}
