#include <iostream>



float fatura(float kullanim){

    float toplam = 0;

    if(kullanim > 60){
        toplam += (kullanim - 60)*6;
        kullanim = 60;
    }

   if(kullanim > 40){
       toplam += (kullanim - 40)*4;
        kullanim = 40;
    }

    if(kullanim > 20){
        toplam += (kullanim - 20)*2;
        kullanim = 20;
    }
    if(kullanim <= 20){
        toplam += 40;
    }

    return toplam;


}

int main(){
    float kullanim = 66;
    std::cout << fatura(kullanim);
}