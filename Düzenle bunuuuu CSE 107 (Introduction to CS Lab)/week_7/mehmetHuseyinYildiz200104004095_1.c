#include<stdio.h>

int main()
{
	int highness;

	
	printf("Enter the highness of triangle: ");
	scanf("%d",&highness);

	for(int row=0; row<=highness; row++)
	{
		for(int i=0; i<row; i++)
			printf("*");
		printf("\n");
	}



	return 0;
}
