#include<stdio.h>
#include<string.h>

#define BASAMAK 35

char* topla(char* uzun, char* kisa);
short uzunMu(char* sayi1, char* sayi2);



int main(){

    char uzun[BASAMAK] = " ", kisa[BASAMAK] = " ";

    printf("İlk sayiyi girin:");
    scanf("%s",uzun);

    printf("İkinci sayiyi girin:");
    scanf("%s",kisa);

    if(uzunMu(kisa,uzun))
        {
            char yedek[BASAMAK];
            strncpy(yedek,kisa,BASAMAK);
            strncpy(kisa,uzun,BASAMAK);
            strncpy(uzun,yedek,BASAMAK);
        }

    char* sonuc = topla(uzun,kisa);

    printf("%s\n",sonuc);

    return 0;
}

char* topla(char* uzun, char* kisa)
{
    static char toplam[BASAMAK+1];
    static int sira = BASAMAK;
    static int elde = 0;
    int digitToplam = 0;

    if(sira == 0)
    {
        if(elde != 0)
        {
            strncpy(&toplam[1],toplam,BASAMAK);
            toplam[0] = elde;
            return toplam;
        }
        
        return toplam;
    }

    else
    {
        digitToplam = ( elde + ( kisa[sira] != ' ' ? kisa[sira]-'0' : 0 ) + ( uzun[sira] != ' ' ? uzun[sira]-'0' : 0 ) ) % 10;
        elde = ( elde + ( kisa[sira] != ' ' ? kisa[sira]-'0' : 0 ) + ( uzun[sira] != ' ' ? uzun[sira]-'0' : 0 ) ) / 10;
        toplam[sira] = digitToplam;
        
        sira--;
        return topla(uzun,kisa);
    }
    
}


short uzunMu(char* sayi1, char* sayi2)
{
    for (int i = 0; i < BASAMAK; i++)
    {
        if(sayi1[i] == ' ')
            return 1;
        if(sayi2[i] == ' ')
            return 0;
    }
    return 0;
}
