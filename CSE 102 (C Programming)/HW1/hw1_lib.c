/*
** hw4_lib.c:
**
** The source file implementing library functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/

#include <stdio.h>
#include "hw1_lib.h"


double integral3(double a0, double a1, double a2, double a3, double xs, double xe, double delta)
{
    int count = (xe -xs) / delta;	/* Determining how many times for loop */
	double sum = 0;
	printf("count:%d\n",count );

    for (int i = 0; i < count; i++)
    {
    	double x = delta*(i + 0.5);					/* calculating the area of rectangle */
    	double y = ( (a0*x + a1)*x + a2)*x + a3; 
    	sum += y*delta;
    }

    return sum;
}


double integral4(double a0, double a1, double a2, double a3, double a4, double xs, double xe, double delta)
{
    int count = (xe -xs) / delta;		/* Determining how many times for loop */
	double sum = 0;

    for (int i = 0; i < count; i++)
    {
    	double x = delta*(i + 0.5);
    	double y = ( ( (a0*x + a1)*x + a2)*x + a3)*x + a4; 	/* calculating the area of rectangle */
    	sum += y*delta;
    }

    return sum;
}


double root3(double a0, double a1, double a2, double a3, double xs, double xe)
{
    double oldY, oldX;
   for(double x=xs; x < xe; x+=0.00001 )		/* finding root of the given by trying x values from xs to xe.  */
   {											/* increasing x very very small to find exact value or very closed value */
   		double y = ( (a0*x + a1)*x + a2)*x + a3; 

   		if( (oldY<=0.0 && y>=0.0) || (oldY>=0.0 && y<=0.0) ) 	/* if the oldY is zero becomes signed- to signed + or reverse  */
   			return oldX;								/*then it returns the old x that exact value or very very closed to exact value*/
   		
   		oldY = y;
   		oldX = x;
   }
}


double root4(double a0, double a1, double a2, double a3, double a4, double xs, double xe)
{
    float oldY, oldX;
   for(double x=xs; x < xe; x+=0.00001 )		/* finding root of the given by trying x values from xs to xe.  */
   {											/* increasing x very very small to find exact value or very closed value */
   		double y = ( ( (a0*x + a1)*x + a2)*x + a3)*x + a4; 

   		if( (oldY<=0.0 && y>=0.0) || (oldY>=0.0 && y<=0.0)) /* if the oldY is zero becomes signed- to signed + or reverse  */
   			return oldX;					/*then it returns the old x that exact value or very very closed to exact value*/
   		
   		oldY = y;
   		oldX = x;
   }
}


int main(){

	float ax = integral3(5.0,-7.0,3.0,5.0,1.0,5.0,0.0001);
	double b =0;
	b=  root3(3.0,1.0,3.0,-7.0,0.0,2.0);

	printf("%lf\n",b );
}