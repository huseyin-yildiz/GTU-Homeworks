/* 

The variable names that used in this file have no relation with the ones in the pdf file. 

<?> in the functions means something other than void, you should find the correct type for these functions.

*/

#include <stdio.h>

void trigonometry(int a, int b, int c)
{
   float sin = (float)a / (float)c;
   float cos = (float)b / (float)c;
   float tan = (float)a / (float)b;

   printf("sinx = %.2f\n",sin);
   printf("cosx = %.2f\n",cos);
   printf("tanx = %.2f\n",tan);
}

void trigonometry_calculation(int a, int b, int c)
{
   trigonometry(a,b,c);
}

void age(int x)
{
    unsigned long int second = 365*24*60*60 *(unsigned long int)x; 
    printf("You are %lu seconds",second);
}


void age_calculation(int x)
{
    age(x);
}


int main()
{
    int a,b,c;
    int age;

    printf("\na:");
    scanf("%d",&a);
    
    printf("\nb:");
    scanf("%d",&b);
    
    printf("\nc:");
    scanf("%d",&c);

    trigonometry_calculation(a,b,c);


    printf("\nYour age: ");
    scanf("%d",&age);

    age_calculation(age);

    return 0;
}
