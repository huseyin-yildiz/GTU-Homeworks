#include<stdio.h>
#define POINTNUMBER 10																					// how many points will classes enter

int main()
{
	float class1SumX = 0.0,class1SumY = 0.0,class2SumX = 0.0,class2SumY = 0.0 ,newX,newY,class1AverageX,class1AverageY,class2AverageX,class2AverageY;						// declaring required variables
	float middlePointX,middlePointY,slopeOfAverageLine,slopeOfSeperatingLine,interceptOfSeperatingLine,interceptOfAverageLine;

	// Taking Values and Finding average points 

	int i;
	for (i = 0; i < POINTNUMBER; ++i)																	// for loop for taking values point number times
	{	
		printf("Class 1 Please enter your point Like:(6.5 5.4): ");										// taking new point for class 1
		scanf("%f%f",&newX,&newY);																
		class1SumX += newX;
		class1SumY += newY;																				// adding new coordinantes to find average 
	}
	
	for (i = 0; i < POINTNUMBER; ++i)																	// for loop for taking values point number times
	{
		printf("Class 2 Please enter your point Like:(6.5 5.4): ");
		scanf("%f%f",&newX,&newY);
		class2SumX += newX;																				// adding new coordinantes to find average 
		class2SumY += newY;
	}

	class1AverageX = class1SumX / POINTNUMBER;
	class1AverageY = class1SumY / POINTNUMBER;															// calculating the average values for class 1 and 2.
	class2AverageX = class2SumX / POINTNUMBER;
	class2AverageY = class2SumY / POINTNUMBER;


	// Middle Point Finding 

	middlePointX = (class1AverageX + class2AverageX) / 2 ;
	middlePointY = (class1AverageY + class2AverageY) / 2 ;

	// Finding the line connecting the two average points and seperating line by using this formula (y = mx+c) --> m is slope and c is intercept 
	

	slopeOfAverageLine = (class1AverageY - class2AverageY) / (class1AverageX - class2AverageX == 0 ? 0.0001:class1AverageX - class2AverageX) ;		// Finding slope of the line between average points
	slopeOfSeperatingLine = slopeOfAverageLine * -1;													// Calculating the slope of Seperating line

	interceptOfSeperatingLine = middlePointY - slopeOfSeperatingLine * middlePointX ;					// finding intercept(c) by using formula (y = mx+c)
	interceptOfAverageLine = middlePointY - slopeOfAverageLine * middlePointX ;		


	// Classifying the user inputs

	float testPointX,testPointY;
	int input_status;
	printf("Please enter a point for testing: ");														// Taking the test point from user.
	input_status = scanf("%f%f",&testPointX,&testPointY);		

	do{
		// finding the owner of the point

		float yOfSeperatingLine = slopeOfSeperatingLine * testPointX + interceptOfSeperatingLine;		// finding y of the sepaerating line
		
		if(class2AverageY > class1AverageY )
		{
			if(yOfSeperatingLine > testPointY)
				printf("Class 1");
			else 																						// printing the class of the point
				printf("Class 2");
			/*	else
					printf("\n Its on the seperating line :)");	*/
		}
		else
		{
			if(yOfSeperatingLine > testPointY)
				printf("Class 2");
			else 																						// printing the class of the point
				printf("Class 1");
		}
	
		printf("\nPlease enter a point for testing: ");													// Taking the test point from user.
		input_status = scanf("%f%f",&testPointX,&testPointY);	
	}
	while(input_status == 2);																			// if scanf is done successfully continue on while loop

	return 0;
}