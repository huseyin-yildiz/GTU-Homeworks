#include<stdio.h>		// girilen sayinin perfect olup 'madigini bulan prgrm

int main()
{
int toplam=0,number;		


printf("Please write a number: ");
scanf("%d",&number);

int i;
for(i=1; i<number;i++) 				// for ile sayinin kendisine kadar elemanlari tek tek gezip
{
	if(number % i == 0)				// girilen sayinin modunu aldim 
		toplam += i;				// eger modu sifir cikiyorsa o sayiyi toplam degiskenine ekledim
}

if(number == toplam)				// burda ise toplam girilen sayiya esit ise prfct number oldugu yazdirilir.
	printf("%d is a perfect number",number);	
else
	printf("%d is not a perfect number",number);


return 0;	
}
