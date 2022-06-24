/*
** hw2_lib.c:
**
** The source file implementing library functions.
**
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "hw2_lib.h"


int find_weekday_of_data(int day, int month, int year)
{
	int _day = 1,
		_month = 1,											/* takes base according this date */
		_year = 2021;
	int weekday = 5;

	short isForward = 0;
	int days;

	if(year > _year)
		isForward = 1;
	else if(_year == year)
	{
		if(month > _month)
			isForward = 1;								/* determines if the taken date is forward or not */
		else if(_month == month)
		{
			if(day > _day)
				isForward = 1;
			else if(_day == day)
						return weekday;							/* if its same date, returns the weekday */
		}	
	}

	if(isForward)
    {	
    	days = count_day_between_dates(_day,_month, _year, day, month, year);			/* calculates number of days between them */
    	weekday += days%7;
    }
    else
    {
   		days = count_day_between_dates(day, month, year, _day, _month, _year);
		weekday -= days%7;																/* calculates mod of according to 7 */
	}

	return weekday;
}


int count_day_between_dates(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year)
{
	int days = 0;
	int month = start_month;								/*all required variables*/
	short flag = 1;
	int day_diff = 0;
	int i;
	for(i=start_year; i<end_year; i++)					/* calculates remaining days */
		{
			day_diff += 365;
			if(i%4 == 0)
			day_diff ++;
		}
label:
	switch(month)											/* calculates how many days up to the given date in the year */
	{
		case 12:days += 30;
		case 11:days += 31;
		case 10:days += 30;
		case 9: days += 31;
		case 8: days += 31;
		case 7: days += 30;
		case 6: days += 31;
		case 5: days += 30;
		case 4: days += 31;
		case 3: days += 28;
		case 2: days += 31;
		case 1: days += 0 ;
	}

	if(end_year %4 ==0 && month>2 )
		days++;

	
	if(flag)													/* if its for first date */
	{
		day_diff -= days;								
		days = 0;
		month = end_month;
		flag = 0;
		goto label;
	}
	day_diff += days;

	day_diff -= start_day;
	day_diff += end_day;

	return day_diff;
}


double find_angle(double a, double b, double c)
{
	float cos = (b*b + c*c - a*a) / (2.0*b*c);													/* solving by cosinus teorem */
	float side1 = sqrt(4.0*( (c*c/4.0) + b*b - b*c*cos )) / 3.0;
	float side2 = sqrt(4.0*( (b*b/4.0) + c*c - b*c*cos )) / 3.0;									/* finding two side of the angle */
	float angle = acos( (side1*side1 + side2*side2 - a*a) / (2*side1*side2) );
	return angle;
}


void print_tabulated(unsigned int r11, double r12, int r13, 
                     unsigned int r21, double r22, int r23, 
                     unsigned int r31, double r32, int r33, char border)
{
	char c = '|'
	,ul[] = "┌"											/* characters to make table */ 
	,ur[] = "┐"
	,dl[] = "└"
	,dr[] = "┘";
	int i=0;
	char borderText[56];
	char ints[3][17];
	int space1, space2, space3;

	if(border != '-' && border != '*')							/*if its not '-' or '*' then gives error. */
	{	
		printf("Cant be drawed with %c\n",border );						
		return;
	}

	
	for(i=0; i<56; i++)										/* sets the border text with border char */
		borderText[i] = border;

	printf("%s%s%c%s\n",ul,borderText,border,ur);	
	printf("%c %s %c %s %c %s %c\n",c,"    Row 101     ",c,				/* prints column heads */
								"   Row ABCDEFG   ",c,
								"   Row XYZ123   ",c);
    
	sprintf(ints[0], "%d", r11);										/* converts integers to string */
	sprintf(ints[1], "%d", r21);
	sprintf(ints[2], "%d", r31);

	space1 = strlen(ints[0])/2;
	space2 = strlen(ints[1])/2;										/* calculates required spaces to align center */
	space3 = strlen(ints[2])/2;


	printf("%c%s%c%c\n",border,borderText,border,border);
    printf("%c%*s%*s%c %-17.2f %c %-+16d %c\n",c, 9+space1, ints[0], 9-space1 ,"",c,r12,c,r13,c);    /* Prints the board rows */
	printf("%c%s%c%c\n",border,borderText,border,border);
    printf("%c%*s%*s%c %-17.2f %c %-+16d %c\n",c, 9+space2, ints[1], 9-space2 ,"",c,r22,c,r23,c);    
    printf("%c%s%c%c\n",border,borderText,border,border);
    printf("%c%*s%*s%c %-17.2f %c %-+16d %c\n",c, 9+space3, ints[2], 9-space3 ,"",c,r32,c,r33,c);    

 	printf("%s%s%c%s\n",dl,borderText,border,dr);	

	
}