/*
*
*	Author: Mehmet Huseyin YILDIZ
*	Date : 29/03/2021 23:15
*
*/
#include<stdio.h>

void print_fibonacci(int num){				/* Prints the fibonacci series with taken parameter */

	printf("Fibonacci Sequence:\n");			
	int last1 = 1, last2 = 0;				
	int now = last1;
	for(int i=0; i<num; i++){
		printf("%d\n",now );				/* sums the last 2 elements always  and updates them*/
		now = last1 + last2;
		last2 = last1;
		last1 = now;
	}
}

void calculate_fibonacci_sequence(){
	int number = 0;
	short isCorrect = 1;						/* All required variable declarations */
	char garbage;	
	
		while(1){
			
			if(!isCorrect)
			{
				scanf("%c",&garbage);				/* scanf for buffered character */
				if(garbage == '*')
				break;													/* if garbage char is * then breaks the loop */
				printf("Please enter \"numeric\" term(s) number:");
			}
			else if(number < 0 )		/* if the number is negative */
			{
				scanf("%c",&garbage);
				if(garbage == '*')										/* if garbage char is * then breaks the loop */
				break;
				printf("Please enter \"positive\" term(s) number:");
			}
			else
			{	if(number > 0)					/* if the number is not initial value */
					print_fibonacci(number);
				printf("Please enter term(s) number:");
			}

			isCorrect = scanf("%d",&number);		/* takes number */

		}
}

void is_perfect(int number,int sum)
{
	printf("Is Perfect Number?:");			/* if sum and number is equals then prints yes else no */
	if(number == sum && sum!=0)
		printf("Yes\n");
	else
		printf("No\n");
}

short isInteger(float num){
	return (int)num == num;				/* returns if the num is integer(exact value like 2.0) or not */
}

void is_harmonic(int number){
	
	float sum_of_divisors = 0;
	int divisor_count;
	for(int i=1; i<=number; i++){
		if(number % i == 0)
		{
			sum_of_divisors += 1.0/i;
			divisor_count++;							/* calculates sum of divisors */
		}
	}

	sum_of_divisors = divisor_count / sum_of_divisors;

	printf("Is Harmonic Divisor Number?:");
	if( isInteger(sum_of_divisors) )					/* checks if sum of divisor integer then prints yes else no */
		printf("Yes\n");
	else
		printf("No\n");
}

void is_perfect_harmonic_number(int number){
	
	printf("Natural Number Divisors:");
	int sum = 0;
	for(int i=1; i<number; i++)
	{
		if(number % i == 0)
		{
			printf("%d,",i);								/* prints natural number divisors */
			sum += i;
		}
	}
	printf("%d\n",number );

	is_perfect(number,sum);

	is_harmonic(number);
}

void decide_perfect_harmonic_number(){
	int number = 0;
	short isCorrect = 1;
	short isFirst = 1;
	char garbage;
	
		while(1){
			
			if(!isCorrect)
			{
				scanf("%c",&garbage);										/* scanf for buffered character */
				if(garbage == '*')											/* if garbage char is * then breaks the loop */
				break;
				printf("Please enter \"numeric\" term(s) number:");
			}
			else if(number < 0 )
			{
				scanf("%c",&garbage);											/* scanf for buffered character */
				if(garbage == '*')
				break;															/* if garbage char is * then breaks the loop */
				printf("Please enter \"natural\" input number:");
			}
			else
			{	if(!isFirst)
					is_perfect_harmonic_number(number);						/* if it is not first run of loop calls the function  */
				printf("\nPlease enter input number:");
			}

			isCorrect = scanf("%d",&number);
			isFirst = 0;
		}
}

void difference_max_min(){
	printf("Please enter 5 numbers:");
	float max = -99999, min = 99999;
	for (int i = 0; i < 5; ++i)
	{
		float current;
		scanf("%f",&current);
		if(current > max)									/* if current is bigger than max */
			max = current;				
		if(min > current)									/* if current is smaller than min */
			min = current;
	}
	
		printf("Maximum number is:%.6g\n",max );
		printf("Minimum number is:%.6g\n",min );
		printf("Different between maximum and minimum is:%.6g\n",max-min);
}

short bmi_category(float weight, float height ){
	float bmi = weight / (height * height);
	
	if(bmi < 16 )
		return 1;								/* bmi category is represented as value is 1 to 5 */
	else if(bmi <= 18.4)
		return 2;								
	else if(bmi <= 24.9)
		return 3;
	else if(bmi <= 30)
		return 4;
	else
		return 5;
}

void bmi_calculation(){

	float height = 0, weight = 0;
	printf("Please enter weight(kg):");										/* takes weight and height */
	scanf("%f",&weight);

	printf("Please enter height(m):");
	scanf("%f",&height);

	short category = bmi_category(weight, height);
	
	printf("Your category:");
	switch(category){
		case 1:printf("Severely Underweight\n");	break;
		case 2:printf("Underweight\n");	break;
		case 3:printf("Normal\n");		break;
		case 4:printf("Overweight\n");	break;
		case 5:printf("Obese\n");		break;
	}
}

int main(void){

	calculate_fibonacci_sequence();			/* PART 1 */
	decide_perfect_harmonic_number();		/* PART 2 */
	difference_max_min();					/* PART 3 */
	bmi_calculation();						/* PART 4 */
}