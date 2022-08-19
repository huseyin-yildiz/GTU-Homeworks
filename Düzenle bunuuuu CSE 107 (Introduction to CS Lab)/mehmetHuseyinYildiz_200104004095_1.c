#include <stdio.h>
#include <string.h>


void  reverse_string(char  str[]);


int  main()
{
	char  str_arr [100];
	printf("Enter a string:");
	scanf("%s", str_arr);
	reverse_string(str_arr);
	printf("Reversed  string  is: %s \n", str_arr);
	
	
	return  0;

}

void  reverse_string(char  str[])
{
	int length = strlen(str); 
	char newStr[100];
	
	for(int i=(length-1) ; i>=0; i--)
		{
			int top = length-i-1;
			newStr[top] = str[i];
		}
		
	for (int i=0; i < length; i++)
		str[i] = newStr[i];
}
