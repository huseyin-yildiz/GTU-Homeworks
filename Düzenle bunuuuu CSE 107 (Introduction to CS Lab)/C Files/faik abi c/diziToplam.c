#include<stdio.h>

int topla(int dizi[],int buyukluk);

int main(){

    int dizi1[] = {5,62,47,96,47,23,66,11,46};
    int sonuc = topla(dizi1,9);
    printf("sonuc: %d\n",sonuc);
    return 0;
}

int topla(int dizi[],int buyukluk)
{
    int i,toplam=0;
    for(i=0; i<9; i++)
        toplam += dizi[i];
        
    return toplam;
}