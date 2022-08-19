#include<stdio.h>		// 0 1 1 2 3 5 8 13 

int main()
{
	
	int simdi=1,birOnceki=0;										// iki degisken tuttum.
	int number;
	
	printf("Please enter how many terms you would like to print:");			
	scanf("%d",&number);
	
	printf("Top %d terms: %d",number,birOnceki);
	
	
	
	int i =0;
	for(i=0; i<number-1; i++)			// kac tane sayi isteniyorsa for ile
	{
		printf(" %d",simdi);			// her seferinde simdi adli degisken bastýrýlýyor
		int yedek = simdi;
		simdi = simdi+ birOnceki;		// simdi degere bir onceki deger ekleniyor
		birOnceki = yedek;				// bir onceki deger ayarlanýyor
	}
	
	return 0;
}
