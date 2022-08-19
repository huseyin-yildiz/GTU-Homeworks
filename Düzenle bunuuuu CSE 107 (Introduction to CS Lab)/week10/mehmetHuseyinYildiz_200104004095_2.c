#include <stdio.h>

void  print_line(char c, int  num_of_chars);
void  print_histogram(char c, int  vals []);
int  len(int  arr []);

int  main()
{
	int  values [100],  val=1, count =0;
	printf("Enter  positive  integer(s), to  print  anhistogram .\nEnter a non -positive  integer  to stop.\n\n");
	
	do
	{
		printf("Enter a value:");
		scanf("%d", &val);
		values[count] = val;
		count ++;
	}while(val > 0);
	
	print_histogram('*', values);
	return  0;
}


void  print_line(char c, int  num_of_chars)
{
	for(int i=0; i<num_of_chars; i++ )
	{
		printf("%c",c);
	}
	printf("\n");
}


void  print_histogram(char c, int  vals [])
{
	printf("\nOutput:\n");
	for(int i=0; i<len(vals); i++)
	{
		printf("deger=%d",vals[i]);
		if(vals[i] > 0)
			print_line(c,vals[i]);
			
	}
}


int  len(int  arr [])
{
	int i=0;
	do
	{
		i++;		
	}while(arr[i] != -1);

	return i;
}

