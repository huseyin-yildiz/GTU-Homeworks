#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>  // memset için
#include <unistd.h>  // close için

#define PORT 1453

int main(){
while(1){
    int yol = socket(AF_INET, SOCK_STREAM, 0);

    // Veri yapısı ayarları
    struct sockaddr_in sunucu_bilgileri;
    memset(&sunucu_bilgileri, 0, sizeof(sunucu_bilgileri));  // Veri yapısını sıfırlama
    sunucu_bilgileri.sin_family = AF_INET;
    sunucu_bilgileri.sin_addr.s_addr = htonl(INADDR_ANY);  // veya inet_addr("127.0.0.1")
    sunucu_bilgileri.sin_port = htons(PORT);

    // Adres bağlama
    if( bind(yol, (struct sockaddr*)&sunucu_bilgileri, sizeof(sunucu_bilgileri)) < 0 ){
        fprintf(stderr, "Bağlama sırasında hata oluştu.");
        return 1;
    }

    // Dinleme
    if( listen(yol, 5) < 0 ){
        fprintf(stderr, "Dinleme sırasında hata oluştu.");
        return 1;
    }

    // istekler kabul ediliyor.
    struct sockaddr_in istemci_bilgileri;
    socklen_t boyut = sizeof(istemci_bilgileri);
    int istemci_yol = accept(yol, (struct sockaddr*)&istemci_bilgileri, &boyut);
    if(istemci_yol < 0){
        fprintf(stderr, "İsteklerin kabulü sırasında hata oluştu.");
        return 1;
    }

    const char* mesaj = "Merhaba ben Yusuf SEZER";
    if( send(istemci_yol, mesaj, strlen(mesaj), 0) < 0 ){
        fprintf(stderr, "Mesaj gönderimi sırasında hata oluştu.");
        return 1;
    }

    close(istemci_yol);
    close(yol);
}
    return 0;
}