/*
** hw5_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.04.02.23.55
** 
*/

#include <stdio.h>
#include "hw5_lib.h"
#include "math.h"

typedef enum {pa,pb,pc,pd,pe} party;

typedef enum {q1,q2,q3,q4} quadratic;


void multiply  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	double m6 = (*a3)*(*b3);
	double m5 = (*a3)*(*b2) + (*a2)*(*b3);
	double m4 = (*a3)*(*b1) + (*a2)*(*b2) + (*a1)*(*b3) ;
	double m3 = (*a3)*(*b0) + (*a2)*(*b1) + (*a1)*(*b2) +(*a0)*(*b3);
	double m2 = (*a2)*(*b0) + (*a1)*(*b1) + (*a0)*(*b2);
	double m1 = (*a1)*(*b0) + (*a0)*(*b1);
	double m0 = (*a0)*(*b0);											/* multiplies polynomials */

	*a3 = m3;
	*a2 = m2;
	*a1 = m1;
	*a0 = m0;
	
	*b3 = m6;
	*b2 = m5;
	*b1 = m4;
}

void add  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	*a3 += (*b3);
	*a2 += (*b2);										/* adds two polynomials */
	*a1 += (*b1);
	*a0 += (*b0); 
}

void divide  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	*a3 = (*a3)/(*b0);
	*a2 = (*a3)/(*b1) + (*a2)/(*b0);
	*a1 = (*a3)/(*b2) + (*a2)/(*b1) + (*a1)/(*b0);								/*divideds polynomails each other*/
	*a0 = (*a3)/(*b3) + (*a2)/(*b2) + (*a1)/(*b1) + (*a0)/(*b0);
}


void substract  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0)
{
	*a3 -= *b3;
	*a2 -= *b2;						/* subtract the polynomial */
	*a1 -= *b1;
	*a0 -= *b0;
}


void read_polynomial  (double* a3, double* a2, double* a1, double* a0)
{
	printf("Enter the polynomial like: (3,a),(2,b),(1,c),(0,d) : ");					/*takes polynomial from user*/
	if ( scanf("(3,%lf),(2,%lf),(1,%lf),(0,%lf)",a3,a2,a1,a0) == -1 )
	{
		printf("wrong input !!!\n");
		read_polynomial(a3,a2,a1,a0);
	}
	printf("\n");

}





void operate_polynomials  (double* a3, double* a2, double* a1, double* a0, double* b3, double* b2, double* b1, double* b0, char op)
{
/*
	read_polynomial(a3,a2,a1,a0);
	char a;
	scanf("%c",&a);
	printf("%c\n",a );
	printf(" %lf %lf %lf %lf %lf %lf %lf \n",*b3,*b2,*b1,*a3,*b2,*a1,*a0 );
	read_polynomial(b3,b2,b1,b0);
	printf(" %lf %lf %lf %lf %lf %lf %lf \n",*b3,*b2,*b1,*a3,*b2,*a1,*a0 );
*/
	
	printf("\nEnter the first polynomial coefficients from big to small : ");
	scanf("%lf %lf %lf %lf",a3,a2,a1,a0);
	printf("\nEnter the second polynomial coefficients from big to small : ");
	scanf("%lf %lf %lf %lf",b3,b2,b1,b0);

	switch(op){
		case '*': multiply(a3,a2,a1,a0,b3,b2,b1,b0); break;
		case '+': add(a3,a2,a1,a0,b3,b2,b1,b0); break;					/* selects appropriate operation */
		case '/': divide(a3,a2,a1,a0,b3,b2,b1,b0); break;
		case '-': substract(a3,a2,a1,a0,b3,b2,b1,b0); break;
		default: printf("Wrong operator selection !!! \n");
	}
}


void four_d_vectors (double* mean_a0, double* mean_a1, double* mean_a2, double* mean_a3, double* longest_distance, int N)
{
	double d0, d1, d2, d3, euclidian_distance;
	double p0 = -1,p1= -1,p2 = -1,p3 = -1;
	double t0 = -1,t1= -1,t2 = -1,t3 = -1;
	int i=0;

	*mean_a0 = 0;
	*mean_a1 = 0;
	*mean_a2 = 0;
	*mean_a3 = 0;

	*longest_distance = 0;

	
	for(i=0; i<N; i++){
		printf("Enter 4d vector combination: ");
		scanf("%lf %lf %lf %lf",&t0,&t1,&t2,&t3);			/* takes 4d vector */

		if(t0 == -1 && t1 == -1 && t2 == -1 && t3 == -1 )
			break;

		*mean_a0 += t0;
		*mean_a1 += t1;
		*mean_a2 += t2;													/* adds up */
		*mean_a3 += t3;

		if(i != 0)
		{	d0 = t0-p0;
			d1 = t1-p1;
			d2 = t2-p2;
			d3 = t3-p3;

			distance_between_4d_points (d0, d1, d2, d3, &euclidian_distance);					/* finds distance */
		}

		p0 = t0;
		p1 = t1;
		p2 = t2;
		p3 = t3;

		
		if(*longest_distance < euclidian_distance)
			*longest_distance = euclidian_distance;								/* takes longest distance */

	}

	*mean_a0 /= i;
	*mean_a1 /= i;											/* calculates avarage */
	*mean_a2 /= i;
	*mean_a3 /= i;

}


void distance_between_4d_points (double d0, double d1, double d2, double d3, double* euclidian_distance)
{
    *euclidian_distance = sqrt( d0*d0 + d1*d1 + d2*d2 + d3*d3 );						/* calculates distance  */
}

party find_Highest(int partyA, int partyB, int partyC, int partyD, int partyE){
	if(partyA > partyB && partyA > partyC && partyA > partyD && partyA > partyE)
		return pa;
	if(partyB > partyA && partyB > partyC && partyB > partyD && partyB > partyE)
		return pb;
	if(partyC > partyB && partyC > partyA && partyC > partyD && partyC > partyE)			/* returns highest parity as enum */
		return pc;
	if(partyD > partyB && partyD > partyC && partyD > partyA && partyD > partyE)
		return pd;
	if(partyE > partyB && partyE > partyC && partyE > partyD && partyE > partyA)
		return pe;
	else
	return pe;	
}


void dhondt_method (int* partyA, int* partyB, int* partyC, int* partyD, int* partyE, int numberOfSeats)
{
	int d1=1, d2=1, d3=1, d4=1, d5=1;						/* divider counts */
	int s1=0, s2=0, s3=0, s4=0, s5=0;
	int i=0;

	for(i=0; i<numberOfSeats; i++){


		party p = find_Highest((*partyA)/d1,(*partyB)/d2,(*partyC)/d3,(*partyD)/d4,(*partyE)/d5);
	
		switch(p){
			case pa:  d1++; s1++; break;
			case pb:  d2++;	s2++; break;									/* increments divider and seat */
			case pc:  d3++;	s3++; break;
			case pd:  d4++;	s4++; break;
			case pe:  d5++;	s5++; break;
		}
	}

	*partyA = s1;
	*partyB = s2;
	*partyC = s3;
	*partyD = s4;																/* puts parity seats */
	*partyE = s5;

}

quadratic find_quadrant(double x, double y){
	if(x > 0)
		if(y>0)
			return q1;
		else
			return q2;										/* finds the quadrant according to point */
	else
		if(y>0)
			return q4;
		else
			return q3;
}

double absolute_val(double val){
	if(val < 0)
		return val*-1;											/* takes absolute value */
	return val;
}

double find_proximate_angle(double x1,double y1){
	double angle;
	quadratic q = find_quadrant(x1,y1);

	x1 = absolute_val(x1);												/* calculates approximate angle between y axis */ 
	y1 = absolute_val(y1);

	switch(q){
		case q1: angle = (270 + y1/x1);  	break;
		case q2: angle = (180 + x1/y1);	break;
		case q3: angle = (90  + y1/x1);	break;
		case q4: angle = (x1/y1); 		break;
			
	}

	return angle;
}

void swap  (double* x1, double* y1, double* x2, double* y2, double* a1,double* a2){
	double temp = *x1;
	*x1 = *x2;
	*x2 = temp;

	temp = *y1;														/* swaps two value */
	*y1 = *y2;
	*y2 = temp;

	temp = *a1;
	*a1 =* a2;
	*a2 = temp;
}

void order_2d_points_cc (double* x1, double* y1, double* x2, double* y2, double* x3, double* y3)
{
	double a1 = find_proximate_angle(*x1,*y1);
	double a2 = find_proximate_angle(*x2,*y2);
	double a3 = find_proximate_angle(*x3,*y3);

	if(a2<a1)
		swap(x1,y1,x2,y2,&a1,&a2);
	if(a3<a1)
		swap(x1,y1,x3,y3,&a1,&a3);								/* compare approximate angles and sorts them */
	if(a3<a2)
		swap(x3,y3,x2,y2,&a3,&a2);
}


void number_encrypt (unsigned char* number)
{
	char b7='-', b6='-', b5='-', b4='-', b3='-', b2='-', b1='-', b0='-';			/* initializes the values */
	get_number_components (*number, &b7, &b6, &b5, &b4, &b3, &b2, &b1, &b0);			
	reconstruct_components (number, b7, b6, b5, b4, b3, b2, b1, b0);
	
	printf("%c%c%c%c%c%c%c%c\n",b7,b6,b5,b4,b3,b2,b1,b0 );
}


void get_number_components (unsigned char number, char* b7, char* b6, char* b5, char* b4, char* b3, char* b2, char* b1, char* b0)
{
	*b0 = '0' + number % 2 ;
	number /= 2;
	*b1 = '0' + number % 2 ;
	number /= 2;
	*b2 = '0' + number % 2 ;
	number /= 2;
	*b3 = '0' + number % 2 ;			/* converts the number to binary form as char */
	number /= 2;
	*b4 = '0' + number % 2 ;
	number /= 2;
	*b5 = '0' + number % 2 ;
	number /= 2;
	*b6 = '0' + number % 2 ;
	number /= 2;
	*b7 = '0' + number % 2 ;
	
}

void swap_char(char* a,char* b){
	char temp = *a;
	*a = *b;									/* swaps two chars */
	*b = temp;
}


void reconstruct_components (unsigned char* number, char b7, char b6, char b5, char b4, char b3, char b2, char b1, char b0)
{
	char temp;
	swap_char(&b7,&b2);
	swap_char(&b6,&b3);
	swap_char(&b5,&b0);
	swap_char(&b4,&b1);

	temp = b7;
	b7 = b5;
	b5 = b3;
	b1 = b1;
	b1 = temp;								/* encrypts the binary form with the algorithm given in pdf */
	temp = b6;
	b6 = b4;
	b4 = b2;
	b2 = b0;
	b0 = temp;

	*number = (b7-'0')*128 + (b6-'0')*64 + (b5-'0')*32 + (b4-'0')*16 + (b3-'0')*8 + (b2-'0')*4 + (b1-'0')*2 + (b0-'0')*1;

printf("%c%c%c%c%c%c%c%c\n",b7,b6,b5,b4,b3,b2,b1,b0 );
}
/*
int main()
{
	double a3, a2, a1, a0, b3, b2, b1, b0;
	
	operate_polynomials(&a3,&a2,&a1, &a0, &b3, &b2, &b1, &b0, '+');

	printf(" %lf %lf %lf %lf %lf %lf %lf \n",b3,b2,b1,a3,b2,a1,a0 );

*/
/*
	int a = 100000;
	int b = 80000;
	int c = 30000;
	int d = 0;
	int e = 0; 

	dhondt_method(&a, &b, &c, &d, &e, 8);

		printf("a:%d b:%d c:%d d:%d \n",a,b,c,d );
*/



/*	double x2 = -3.2;
	double x1 = -0.2;
	double x3 = 4.2;
	double y1 = 8.2;
	double y2 = -9.2;
	double y3 = 7.2;
	
	order_2d_points_cc(&x1,&y1,&x2,&y2,&x3,&y3);

	printf("1:%lf,%lf \n 2:%lf,%lf \n 3:%lf,%lf \n",x1,y1,x2,y2,x3,y3 );



	unsigned char num = 134;
	number_encrypt(&num);
	printf("%d \n",num );

	double mean_a0,  mean_a1,  mean_a2,  mean_a3, longest_distance;

	four_d_vectors(&mean_a0, &mean_a1, &mean_a2, &mean_a3, &longest_distance, 5 );

	printf("sonuc: %lf\n",longest_distance );

	printf("mean_a0: %lf \n",mean_a0 );
	printf("mean_a1: %lf \n",mean_a1 );
	printf("mean_a2: %lf \n",mean_a2 );
	printf("mean_a3: %lf \n",mean_a3 );



	return 0;
}

*/