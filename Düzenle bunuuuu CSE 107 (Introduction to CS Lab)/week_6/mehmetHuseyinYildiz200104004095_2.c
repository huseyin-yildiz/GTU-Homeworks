#include<stdio.h>
									// girilen sayinin prime (asal) olup olmadigini kontrol eder
int main()
{
int number;
short isPrime=1;					// flag olusturdum prime oldup olmadigini tutmasi icin 
									// baslangic degeri 1 olan
printf("Enter a number: ");
scanf("%d",&number);

int i;
for(i=2; i<number; i++)				// 2den girilen numaraya kadar for ile tek tek gezip modunu aldim
{
	if(number % i == 0)					// eger modu herhangi bir sayiya bolununce sifir ise  isPrime 0 atanir
		{
			printf("%d is not prime",number);
			isPrime = 0;
			break;
			exit(0);
		}
}

if(isPrime == 1)							// flag hala 1  prime oldugunu ise print ettim 
	printf("%d is a prime number",number);

return 0;	
}
