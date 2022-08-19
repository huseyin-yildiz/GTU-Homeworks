#include<stdio.h>
#include<string.h>

#define BASAMAK 31		// ilk rakamlar toplamı sonucu basamak artarsa

char* topla(char* uzun, char* kisa);
short uzunMu(char* sayi1, char* sayi2);
char* sagakaydir(char* string);
void fullSifir(char* sayi);
void ekranaYazdir(char* sonuc);

int main(){
    char uzun[BASAMAK] = "", kisa[BASAMAK] = "";

    printf("İlk sayiyi girin...:");
    scanf("%s",uzun);

    printf("İkinci sayiyi girin:");
    scanf("%s",kisa);

	printf("\n");
    if(uzunMu(kisa,uzun))
        {
            char yedek[BASAMAK];
            strncpy(yedek,kisa,BASAMAK);
            strncpy(kisa,uzun,BASAMAK);
            strncpy(uzun,yedek,BASAMAK);
        }
	
	sagakaydir(uzun);
	printf("Sayi 1:%s\n",uzun );
	sagakaydir(kisa);
	printf("Sayi 2:%s",kisa );

    char* sonuc = topla(uzun,kisa);
    ekranaYazdir(sonuc);
    return 0;
}

void ekranaYazdir(char* sonuc)
{
	short sil = 1;
	printf("\nSonuc :");
	for (int i = 0; i < BASAMAK; ++i)
	{
		if(sonuc[i]!='0'  || sil == 0)
			{
				printf("%c",sonuc[i]);
				sil = 0;
			}
		else if(sil == 1)
			printf(" ");
	}
	printf("\n");
}

char* topla(char* uzun, char* kisa)
{
    static char toplam[BASAMAK+1] = "0";
    static int sira = BASAMAK - 1;
    static int elde = 0;
    int digitToplam = 0;

    if(sira == -1)
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
        digitToplam = ( elde + ( kisa[sira] != ' ' ? kisa[sira]-'0' : 0) + ( uzun[sira] != ' ' ? uzun[sira]-'0' : 0 ) ) % 10;
        elde = ( elde + ( kisa[sira] != ' ' ? kisa[sira]-'0' : 0 ) + ( uzun[sira] != ' ' ? uzun[sira]-'0' : 0 ) ) / 10;
        toplam[sira] = digitToplam !=' ' ? digitToplam+'0' : ' ' ;
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

char* sagakaydir(char* string)
{
	char yedek[BASAMAK];
	for (int i = 0; i < BASAMAK; ++i)									//123\0
	{																	//   \0      
		if(string[i] == 0)
		{
			fullSifir(string);
			strncpy(&string[BASAMAK-i],yedek,i);
			break;
		}
		yedek[i] = string[i];
	}
}

void fullSifir(char* sayi)
{
	for (int i = 0; i < BASAMAK; ++i)
		sayi[i] = '0';
}