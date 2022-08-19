#include<stdio.h>

int main(){

    int* arr;

    int brr[30];

    arr = brr;

    arr = calloc(10,sizeof(int));
    arr[0] = 12;

    arr = realloc(arr,sizeof(int)*15);

    printf("%d",arr[0]);




    typedef struct {
        int size;
        char reservedWords[50][50];
        int valueTable[50];                     // Variable Table
    }identifiers;

    identifiers id;
    id.size = 0;
    
    return 0;
}