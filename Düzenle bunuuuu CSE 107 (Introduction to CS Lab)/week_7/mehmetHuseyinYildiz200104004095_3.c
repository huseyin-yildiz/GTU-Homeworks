#include<stdio.h>

const int MAX_ARRAY = 1000;

short asalMi(int number);

int main()
{
	int number;
	int compositeNumbers[MAX_ARRAY];
	
	printf("Enter a number: ");
	scanf("%d",&number);
	
	int y=0;
	for(int i=1; i <= number; i++)						// asal mi kontrol eder
		if(!asalMi(i))
		{
			compositeNumbers[y] = i;
			y++;
		}
			
	int i = 0;
	while(i < y )										// composite leri basar
		{
			printf("%d is composite\n",compositeNumbers[i]);
			i++;
		}
	
	return 0;	
}


short asalMi(int number){
	
	for(int i =2; i<number; i++)
		if(number % i == 0)
			return 0;

	
	return 1;
}
