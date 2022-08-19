//      Sum     : This program is finds longest increasing subsequence in an array.
//      Author  : Mehmet Hüseyin YILDIZ
//      Date    : 12/11/2021

#include <stdio.h>


char* toStr(int n, char str[])
{
    char convertString[] = "0123456789";
    if (n < 10)
    {
        str[0] = convertString[n];
        return &str[1]; // converts char to string, and returns it
    }
    else
    {
        char* a = toStr(n / 10, str);
        *a = convertString[n % 10]; // function makes a recursive call to itself.
        *(a+1) = '\0';
        return;
    }
}

// Converts int to string
int int_to_str(int n, char str[10])                 // Space Complexity -> O(1) - Time Complexity -> O(1) (because max allowed digit size is 10)
{
    char convertString[] = "0123456789";     
    str[10]='\0';                              
    int i=9;                                    
    while(n !=0){                               
        int digit = n%10;
        str[i--]= convertString[digit];
        n/=10;
    }
    return i+1;
}


void wtof(int arr[], int size){
    for(int i=0; i<size; i++)
    {
        char str[10];
        toStr2(arr[i],str);
        // print(str) to file
        // print(,)
    }
}



int main()
{

    char str[10];
    int i = toStr2(13342, str);

    printf("str: %s ok", &str[i]);
    /*
    int array[] = {50,3,10,7,40,80};
    int size = 6;

    int result[] = {1,1,1,1,1,1,1,1,1,1};           // fixed for initializing (max size is 10) increase length for longer arrays
    int sequence[]   = {1,1,1,1,1,1,1,1,1,1};       // fixed for initializing (max size is 10) increase length for longer arrays

  
    int maxSize=0;

    int pathSize = subseq(array,size,-1);
  
    printf("size:%d\n",pathSize);



    int max_index = subseqArr(array,size,result);
    get_longest_path(result,array,max_index,sequence,size);
    print_sequence(sequence,max_index);
    printf(" size: %d\n",max_index);
*/

    return 0;
}

// solution 3 (finds both length and array of longest sequence)

// makes a result table by using array
int subseqArr(int array[], int size, int result[])      // Space Complexity -> O(1) (because array size is limited 10) if it was not limited, comp. would be (O(n))
                                                        // Time Complexity  -> O(n^2)
{                                                       
    int max_index = 1;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (array[i] > array[j] && result[j] >= result[i])
            {
                result[i] = result[j] + 1;
                if (result[i] > result[max_index])
                    max_index = result[i];
            }
        }
    }
    return max_index;
}

// extracts longest path from result table
void get_longest_path(int result[], int array[], int max_index, int path[], int size)       // Space Complexity -> O(n)
{                                                                                           // Time  Complexity -> O(n)
    int index = max_index;
    for (int i = size - 1; i >= 0; i--)
    {
        if (result[i] == index && (index == max_index || path[index] > array[i]))
        {
            path[--index] = array[i];
        }
    }
}

void print_sequence(int sequence[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", sequence[i]);
}


// solution 2 (finds only length of longest subsequence)

int subseq(int array[], int size, int last)
{

    if (size == 1)
    {
        //  sequence[0] = array[0];
        //     printf("%d ",array[0]);
        return 1;
    }
    else
    {
        int longestPathSize = 0;
        int node;

        //printf("%d ",array[0]);

        for (int i = 0; i < size; i++)
        {
            int path;
            if (array[i] > array[0])
            {
                path = subseq(&array[i], size - i, array[0]);
                if (path > longestPathSize)
                {
                    longestPathSize = path;
                    //   printf("%d,%d ",last,array[0]);
                }
            }
        }
        return longestPathSize + 1;
    }
}

// solution 1 not exact (wrong)

int subseq1(int array[], int size)
{

    int max_num;
    int max_size = 0;     // size of longest sequence
    int current_size = 0; // size for current sequence
    int index_of_longest = 0;

    for (int i = 0; i < size; i++)
    {
        max_num = -999999;
        printf("\n%d. ", i);
        for (int j = i; j < size; j++) // candidate sequence
        {
            if (array[j] > max_num)
            {
                max_num = array[j];
                printf("%d ", max_num);
                current_size++;
            }
        }

        if (max_size > current_size)
        {
            max_size = current_size;
            index_of_longest = i;
        }
    }

    printf("\n\nLongest sequence is %d.", index_of_longest);
    printf("\nSize = %d\n\n", max_size);
}
