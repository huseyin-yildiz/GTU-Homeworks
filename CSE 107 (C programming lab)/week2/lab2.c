#include <stdio.h>
#include <math.h>

void stdCalc(){														/* the function standart calculation */
	int selection1, selection2;
	int int1, int2;
	float real1, real2, imag1, imag2;

	printf("Enter the number type\n");
	printf("1. Integer\n");
	printf("2. Complex\n");
	printf("----------------------\n");
	scanf("%d",&selection1);

	printf("Enter the calculation type\n");
	printf("1. Addition\n");												/* taking calculation type and number type */
	printf("2. Multiplication\n");
	printf("-------------------------\n");
	scanf("%d",&selection2);

	switch(selection1)
	{
		case 2: printf("Please enter first complex number (real part first):\n");
				scanf("%f%f",&real1,&imag1);
				printf("Please enter second  complex number(real part first):\n");				/* calculation */
				scanf("%f%f",&real2,&imag2);
				if(selection2 == 2)
					printf("Multiplication of numbers = %.2f +  %.2fi \n",real1*real2 - imag1*imag2, real1*imag2 + real2*imag1  );
				else
					printf("Addition = %.2f +  %.2fi \n",real1+real2, imag1+imag2);
		
				break;
		case 1: printf("Please enter first integer number:\n");
				scanf("%d",&int1);
				printf("Please enter second  integer number:\n");
				scanf("%d",&int2);
				if(selection2 == 2)
					printf("Multiplication of numbers = %d\n",int1*int2 );
				else
					printf("Addition = %d\n",int1+int2);
				break;
	}
}


void rectangle(){																/* the function for rectangle area, perimeter */
	float a,b;
	printf("Enter sides:\n");
	scanf("%f%f",&a,&b);

	printf("Perimeter : %f\n",(a+b)*2 );
	printf("Area : %f\n",a*b);
}

void triangle(){
	float a,b,c;																/* the function for triangle area, perimeter */
	printf("Enter three sides of triangle:\n");
	scanf("%f%f%f",&a,&b,&c);

	printf("Perimeter of Triangle = %.2f\n",a+b+c );
	
	float s = (a+b+c)/2.0;
	float area = sqrt(s*(s-a)*(s-b)*(s-c));
	printf("Area of Triangle: %.2f\n",area);
}


void circle(){
	float pi = 3.14,r;														/* the function for circle area, perimeter */
	printf("Enter r:\n");
	scanf("%f",&r);

	printf("Perimeter of circle = %f\n",2.0*pi*r );
	printf("Area %f:\n",pi*r*r);
}

void fahToKel(){															/*the function for fah to kelvin */
	float fah;
	printf("Please enter the Temperature in Fahrenheit:\n");
	scanf("%f",&fah);
	float result = ( (5.0/9.0)*(fah - 32.0) ) + 273.15;
	printf("Result = %f\n",result );
}

void kelToFah(){															/* the function kelvin to fahrenheit */
	float kel;
	printf("Please enter the Temperature in Kelvin:\n");
	scanf("%f",&kel);
	float result = ( (9.0/5.0)*(kel - 273.15) ) + 32.0;
	printf("Result = %f\n",result );
}


void tempCalc(){													/* menu for temp calculation */

	int selection;

	printf("Enter calculation type\n");
	printf("1. Fahrenheit to Kelvin\n");
	printf("2. Kelvin to Fahrenheit\n");
	printf("---------------------------\n");
	scanf("%d",&selection);

	if(selection == 1)
		fahToKel();
	else if(selection == 2)
		kelToFah();

}


void areaPerimeterCalc(){													/*menu for area and perimeter*/
	int selection;

	printf("1. Rectangle\n");
	printf("2. Triangle\n");
	printf("3. Circle\n");
	printf("-------------------------\n");
	scanf("%d",&selection);

	switch(selection){
		case 1: rectangle(); break;
		case 2: triangle(); break;
		case 3: circle(); break;
	}

}

int main(){

int selection;
	printf("Enter calculator type\n");
	printf("1. Standart Calculator\n" );							/*Taking calculation number*/
	printf("2. Area&Perimeter Calculator\n");
	printf("3. Temperature Calculator\n");
	printf("--------------------------\n");

	scanf("%d",&selection);

	switch(selection)
	{
		case 1: stdCalc(); break;
		case 2: areaPerimeterCalc(); break;
		case 3: tempCalc(); break;												/* calling the functions */
	}

	return 0;
}