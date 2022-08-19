#include<stdio.h>

int main()
{
	int highness;
	
	
	printf("Enter the highness of pyramid: ");
	scanf("%d",&highness);
	

	for(int row=0; row<highness; row++)
	{
		
		for(int space=0; space < highness-row; space++)
		{
			printf(" ");
		}
		
		for(int star=0; star<=row; star++)
		{
			printf("*");
		}
		
		for(int star=0; star<row; star++ )
		{
			printf("*");
		}
		
		for(int space=0; space < highness-row; space++)
		{
			printf(" ");
		}
		
		printf("\n");
		
	}



	return 0;
}
