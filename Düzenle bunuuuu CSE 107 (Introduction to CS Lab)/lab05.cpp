#include<stdio.h>

int main (){

    float weight, height,bmi;

    printf("Enter your weight Please: ");
    scanf("%f",&weight);

    printf("\nEnter your height Please: ");
    scanf("%f",&weight);

    bmi = weight / (height * height) ;

    printf("\nYour body mask index is %f and your category is %f",bmi);
    if(bmi < 18.5)
        printf("Underweight.");
        else if(bmi < 24)
            printf("Healthy Weight.");
            else if(bmi < 30)
            printf("Overweight.");
            else if(bmi < 35)
            printf("Obese(Class I).");
            else if(bmi < 40)
            printf("Obese(Class II).");
            else if(bmi < 50)
            printf("Obese(Class III).");
            else
                printf("Obese(Class IV)");
 
 return 0;           
}

