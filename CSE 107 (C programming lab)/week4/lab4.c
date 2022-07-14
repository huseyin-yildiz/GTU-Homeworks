#include<stdio.h>

void russian_multiplication(unsigned int*  multiplicand,unsigned int*multiplier){

	int sum = 0;								/* The variable to hold sum value */ 

	while(*multiplier > 1)
	{

		if(*multiplier % 2 == 1)					/* if the multipler is odd */
			sum += *multiplicand;						/* then adds to sum */
	
		*multiplicand *= 2;
		*multiplier /= 2; 
	}

	if(*multiplier == 1)							/* if the last value of multiplier is 1 */
		sum += *multiplicand;							/* then adds to sum */

	*multiplicand = sum;
}


void  multiply_polynomials  (double*  a3,  double*  a2,  double*  a1,  double*  a0,
  		double*  b3, double* b2, double* b1, double b0)
{
	double r6 = (*a3)*(*b3);													
	double r5 = (*a3)*(*b2) + (*a2)*(*b3);
	double r4 = (*a3)*(*b1) + (*a2)*(*b2) + (*a1)*(*b3);									/* calculates every result element */
	double r3 = (*a3)* b0 + (*a2)*(*b1) + (*a1)*(*b2) + (*a0)*(*b3);
	double r2 = (*a2)* b0 + (*a1)*(*b1) + (*a0)*(*b2);
	double r1 = (*a1)* b0  + (*a0)*(*b1) ;
	double r0 = (*a0)* b0 ;

	*a3 = r6;
	*a2 = r5;
	*a1 = r4;
	*a0 = r3;																/* then assign them to the pointers  */
	*b3 = r2;
	*b2 = r1;
	*b1 = r0;
}


void print_element(float c, int degree, short is_signed)				/* prints the given element */
{
	if(c != 0)
	{
		if(c != 0)
		{
			if(is_signed)
				printf("%+g",c );										/* if signed then adds + or - */
			else
				printf("%g",c );
		}
		if(degree != 0)
		{	
			printf("x");
			if(degree != 1)											/* prints degree and constant */
				printf("^%d ",degree );
		}
	}
}



int main(){

	unsigned int multiplier;
	unsigned int multiplicand;

	printf("Enter multiplier: ");						/* part 1 */
	scanf("%u",&multiplier);

	printf("Enter multiplicand: ");
	scanf("%u",&multiplicand);

	unsigned int* ptr1 = &multiplicand;
	unsigned int* ptr2 = &multiplier;

	russian_multiplication(ptr1, ptr2);

	printf("%u\n",*ptr1 );	


	
	/* Multiplying polynomial */

	double a3 = 1;
	double a2 = 2;
	double a1 = 3;
	double a0 = 4;
	double b3 = 5;
	double b2 = 6;
	double b1 = 7;
	double b0 = 8;
	
	
	multiply_polynomials(&a3,&a2,&a1,&a0,&b3,&b2,&b1,b0);

	print_element(a3,6,0);
	print_element(a2,5,1);
	print_element(a1,4,1);
	print_element(a0,3,1);
	print_element(b3,2,1);
	print_element(b2,1,1);
	print_element(b1,0,1);

	printf("\n");

}