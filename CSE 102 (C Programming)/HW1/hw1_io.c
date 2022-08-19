/*
** hw1_io.c:
**
** The source file implementing output functions.
**
** Author: Yakup Genc. (c) 2018-2021
**
** Revision: 2021.03.03.20.16
** 
*/


#include <stdio.h>
#include "hw1_io.h"
#include "string.h"

void write_polynomial3(double a0, double a1, double a2, double a3)
{
		char str[4][10];
		double a[4] = {a0,a1,a2,a3};	/* assigning the arguments to array	*/

	for (int i = 0; i < 4; ++i)
	{
		if(a[i]>0)
			strcpy(str[i], "+");		/* adding signs to string */
		else if(a[i]<0)
			strcpy(str[i], "-");
		else
			strcpy(str[i], "");

		if( a[i] != 1.0 && a[i] != -1.0 && a[i] != 0 )
			{
				if( a[i]-(int)a[i] == 0)			/* if current a is exact or not*/
					snprintf(str[i], 10, "%+.f", a[i]);
				else
					snprintf(str[i], 10, "%+.1f", a[i]);	
			}
	}

	printf("%sx^3%sx^2%sx%s\n", str[0], str[1], str[2], str[3]);		/* Printing polynomial strings */
}


void write_polynomial4(double a0, double a1, double a2, double a3, double a4)
{
    char str[5][10];
		double a[5] = {a0,a1,a2,a3,a4};		/* assigning the arguments to array	*/

	for (int i = 0; i < 5; ++i)
	{
		if(a[i]>0)
			strcpy(str[i], "+");			/* adding signs to string */
		else if(a[i]<0)
			strcpy(str[i], "-");
		else
			strcpy(str[i], "");

		if( a[i] != 1.0 && a[i] != -1.0 && a[i] != 0 )
			{
				if( a[i]-(int)a[i] == 0)				/* if current a is exact or not*/
					snprintf(str[i], 10, "%+.f", a[i]);
				else
					snprintf(str[i], 10, "%+.1f", a[i]);	
			}
	}

	printf("%sx^4%sx^3%sx^2%sx%s\n", str[0], str[1], str[2], str[3], str[4]);		/* Printing polynomial strings */
}
