#include<stdio.h>

struct sonuc
{
    float bolum;
    int kalan;
};

void bol(int* a, int* b,int c , struct sonuc* d);

int main()
{
    int buyukluk = 6;
    int dizi1[] = {3,6,9,12,16,18};
    int dizi2[] = {2,3,3,4,4,4};
    struct sonuc sonuclar[buyukluk];

    bol(dizi1,dizi2,buyukluk,sonuclar);


    printf("Bolumler: ");
    for (int i = 0; i < buyukluk; i++)
        printf("%3.1f ",sonuclar[i].bolum);

    printf("\nKalanlar: ");
    for (int i = 0; i < buyukluk; i++)
        printf("%d ",sonuclar[i].kalan);
    
    
    

    return 0;
}


void bol(int* bolunenler, int* bolenler,int buyukluk,struct sonuc* sonuclar)
{
    for (int i = 0; i < buyukluk; i++)
    {
       sonuclar[i].bolum = ((float)bolunenler[i]) / bolenler[i] ;
       sonuclar[i].kalan = bolunenler[i] % bolenler[i] ;
    }
}