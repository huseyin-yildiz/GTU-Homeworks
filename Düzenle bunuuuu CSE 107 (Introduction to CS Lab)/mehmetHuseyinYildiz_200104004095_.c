#include<stdio.h>
#include<stdlib.h>

#define FILENAME "text.txt"

typedef struct Student{
	char name[20];
	char surName[20];
	char id[20];
	float gpa;
}student;

	void read(student students[], int size);
	void printHighest(student students[],int size);
	void printLowest(student students[],int size);
	

int main()
{
	student students[15];
	
	read(students,15);
	
	printHighest(students,15);
	printLowest(students,15);
	
	getchar();
	return 0;
}


	void read(student students[],int size)
	{
		FILE *myFile;
		myFile = fopen(FILENAME,"r");
		
		if(myFile == NULL)
			printf("file error");
		// we can check the file if it is opened here
		
		int i = 0;
		while(!feof(myFile))
		{
			fscanf(myFile,"%s %s %s %f",&students[i].name
										,&students[i].surName
										,&students[i].id
										,&students[i].gpa);
			i++;
		}
		fclose(myFile); 
	
	}
	void printHighest(student students[],int arraySize)
	{
		int highest=0;
		for(int i=0; i<arraySize; i++)
			if(students[highest].gpa < students[i].gpa )
				highest = i;
				
		printf("The student with the highest GPA:\nname: %-10s surname: %-10s id: %-10s gpa: %.2f\n\n"
													,students[highest].name
													,students[highest].surName
													,students[highest].id
													,students[highest].gpa );
	}
	void printLowest(student students[],int size)
	{
		int lowest=0;
		for(int i=0; i<size; i++)
			if(students[lowest].gpa > students[i].gpa )
				lowest = i;
				
		printf("The student with the lowest GPA:\nname: %-10s surname: %-10s id: %-10s gpa: %.2f\n\n"
													,students[lowest].name
													,students[lowest].surName
													,students[lowest].id
													,students[lowest].gpa );
	}
	


