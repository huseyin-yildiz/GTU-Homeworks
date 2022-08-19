#include<stdio.h>

int dizi[100];
int sayi;
int toplam = 0;

int main(){

FILE *dosya = fopen("esenyurt.txt", "w");

printf("Kac sayi girmek istiyorsunuz: ");
scanf("%d",&sayi);

for(int i=1; i<=sayi; i++)
{
	printf("\n%d.sayi = ",i);
	scanf("%d",&dizi[i]);
	toplam += dizi[i];
	fprintf(dosya,"%d\n",dizi[i]);
}

printf("\n%d",toplam);
fprintf(dosya, "%d",toplam );

return 0;
}