#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>  // memset için
#include <unistd.h>  // close için

#define BOYUT 512

int main(){

    const char* sunucu_adres = "localhost";
    const int sunucu_port = 1453;

    // Bağlanılacak sunucu ayarları
    struct sockaddr_in sunucu_bilgileri;
    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));
    sunucu_bilgileri.sin_family = AF_INET;
    inet_pton(AF_INET, sunucu_adres, &sunucu_bilgileri.sin_addr);
    sunucu_bilgileri.sin_port = htons(sunucu_port);

    int yol = socket(AF_INET, SOCK_STREAM, 0);

    // Sunucuya bağlanma
    if( connect(yol, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) < 0 ){
        fprintf(stderr, "Sunucu bağlantısı sırasında hata oluştu.");
        return 1;
    }

    char alinan_veri[BOYUT];
    int veri_boyutu = recv(yol, alinan_veri, BOYUT, 0);

    if(veri_boyutu < 0){
        fprintf(stderr, "Veri alımı sırasında hata oluştu.");
        return 1;
    }

    fprintf(stdout, "Alınan veri: %s", alinan_veri);

    close(yol);
    return 0;
}