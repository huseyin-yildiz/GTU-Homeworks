#include <stdio.h>
#include <time.h>                                   /* defining the required libraries */
#include "stdlib.h"

#define MAX 150
#define MAX_ARRAY 50

float mycos(int n, float x){
    if(n == MAX+1)                                      /* if it reach the max value+1  returns 1 */
        return 1.0;
    else
       return 1.0- (x*x / ( (float)((2*n-1)*2*n) ) ) * mycos(n+1, x);
}


int search_element(int arr[], int input_number,int size){
    if(size == 0)                                                           /* if size is 0 then returns 0 (false)  */
        return 0;
    if(arr[0] == input_number)
        return 1;                                                       /* if first element equals to input_number returns 1 (true) */
    else
        return search_element(&arr[1],input_number,size-1);     /* else calls same function by decreasing array size and with sub array */
}



int check_palindrome(int a[], int n){
    if(n <= 2)
        return a[0] == a[n-1];                          /* if the array only contains 1 or 2 elements then returns if its equals to each others */
    if(a[0] == a[n-1])
        return check_palindrome(&a[1],n-2);         /* checks whether last and first item is equals to each other */
    else
        return 0;                                          /*  if they are not equals then return 0 (false) */
}





int main() {
    int a[MAX_ARRAY];


    int number,n;
    printf("how many number will you enter: ");
    scanf("%d",&number);                                                                             /* PART 1 test*/
    printf("Enter numbers");
    for (int i = 0; i < number; ++i) {
        scanf("%d",&a[i]);                  /* takes numbers */
    }
    int x = check_palindrome(a,number);
    if(x==1)
        printf("Your input is palindrome\n");
    else
        printf("Your input is not palindrome\n");






    srand(time(NULL));
    int array[20];
    int i;
    int num;
    int isfound;

    for( i=0; i<20; i++)
    {
        array[i] = rand()%101;
        printf("%d ",array[i]);                                 /* random numbers generating*/
    }
    printf("\nEnter the number: ");                                                                      /* part 2 test*/
    scanf("%d",&num);
    isfound = search_element(array,num,20);                     /* takes numbers */
    if(isfound)
        printf("The element is found in the array\n");
    else
        printf("The element is not found in the array\n");


    float x1;
    printf("Enter n and x");
    scanf("%d %f",&n,&x1);
    float y = mycos(n,x);                                             /* part 3 test */
    printf("sonuc: %f",y);





}
