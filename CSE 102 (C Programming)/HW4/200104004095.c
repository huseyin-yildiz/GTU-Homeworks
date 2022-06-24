#include <stdio.h>
#include <math.h>



void print_element(float c, int degree, short is_signed)				/* prints the the taken element */
{
	if(c != 0)
	{
		if((c != 1 && c != -1) || degree == 0)
		{
			if(is_signed)
				printf("%+g",c );										/* prints with sign */
			else
				printf("%g",c );										/* prints without sign */
		}
		if(degree != 0)
		{	
			if(c == 1 && is_signed)
				printf("+");

			if(c == -1)
				printf("-");
			
			printf("x");
			if(degree != 1)
				printf("^%d",degree );								/* prints the degree */
		}
	}
}


int value_of_digit(int number, short digit_number){								/* returns the wanted digit in the given number  */

	int a = pow(10,digit_number);
	int b = pow(10,digit_number-1);
	int digit = (number % a - number % b) / b;
	return digit;
}



short isArmstrong(int number){													/* returns if the given number is armstrong or not */

	int initial_value = number;
	int sum = 0;
	int digit;
	short digit_count = 1;												
	int digit_value = 0;

	do 
	{
		digit_value = pow(10,digit_count-1);
		digit = value_of_digit(number,digit_count); 							/* takes the cube of every digit one by one */
		sum += pow(digit,3);
		number -= digit_value * digit;
		digit_count++;

	}while( number > 0  );

	return sum == initial_value;											/* returns sum value */
}

short digitSize(int number){									/* returns the digit size of the number */
	short digit = 0;
	while(number > 0)
	{
		number /= 10;
		digit++;
	}
	return digit;
}


short isPalindrome(int number){										/* returns if the given number is palindrome or not */
	int digit_size = digitSize(number);
	int i;
	for ( i = 0; i < digit_size/2; ++i)
	{

		if( value_of_digit(number,i+1) != value_of_digit(number,digit_size-i) )			/* compares first and last numbers one by one */
			return 0;
		
	}
	return 1;
}



void print_polynomial(){												
	int degree;
	int isSigned = 0;
	int i;

	printf("Enter your polynomial[n a_n a_n-1 a_n-2 ... a_0]:");
	scanf("%d",&degree);													/* takes the degree from the user */
	printf("p(x)= ");

	
	for( i=degree; i>=0; i--)
	{
		float c;
		if ( scanf("%f",&c) == 1 )
				print_element(c,i,isSigned);								/* prints all polynomial element one by one */
				
		else
		{	
			printf("Wrong input !!! \n");									/* if the input is not integer */
			break;
		}
		if(c != 0)
			isSigned = 1;
	}
}


void armstrong_palindrome(){
	int number;
	short is_palindrome;
	short is_armstrong;

	printf("\nPlease enter an integer number :");									/* Takes an integer from the user */
	scanf("%d",&number);

	is_palindrome = isPalindrome(number);
	is_armstrong = isArmstrong(number);									/* checks if the number is armstrong and palindrome */
	
	if( ! is_palindrome && is_armstrong )
		printf("This number is only Armstrong number.\n");
	
	else if( is_palindrome && ! is_armstrong )
		printf("This number is only Palindrome number.\n");						/* prints the status of the number by checking */

	else if(is_palindrome && is_armstrong)
		printf("This number is both Palindrome and Armstrong number.\n");

	else
		printf("This number does not satisfy any special cases.\n");
}





short isPrime(int number){									/* returns if the taken number is prime or not */
	int i;
	for( i=2; i<number; i++)
	{
		if(number % i == 0)
			return 0;
	}
	return 1;
}



void primeNumbers(){
	int small,big;
	int sum = 0;
	int i;

	printf("\nPlease enter first integer number: ");								/* Takes first number */
	scanf("%d",&small);

	printf("\nPlease enter second integer number: ");								/* Takes second number */
	scanf("%d",&big);


	if(small > big)
	{																			/* if first number is bigger than second changes them */
		int temp = big;															
		big = small;
		small = temp;
	}

	
	for(i=small+1; i<big; i++)												/* !! I assumed the small and the big one is not included */
		if(isPrime(i))														/* Checks all numbers between small and big number */
			sum += i;														/* and adds prime ones */
	
	printf("Sum of prime numbers between %d and %d : %d \n",small,big,sum );

}





int main(){

	print_polynomial();													/* PART 1 */
	armstrong_palindrome();												/* PART 2 */
	primeNumbers();														/* PART 3 */

}	
