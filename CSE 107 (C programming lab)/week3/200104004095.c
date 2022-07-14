#include <stdio.h>


int find_max_ditance(int num_inputs){												
	
	printf("Please enter %d numbers\n",num_inputs);						/*Request numbers*/

	int i;
	int before=0, now=0, max=0;
	short flag=0;
	for (i = 0; i < num_inputs; ++i)
	{
		printf("%d : ",i+1);								/*prints counts to take number*/
		scanf("%d",&now);
		if(flag)											/*if its not first*/
		{	if(now-before > max )
				max = now - before;							/* Compare 2 numbers */
			if(before - now > max)
				max = before - now;
		}
		flag = 1;
		before = now;
	}

	return max;												/* Returns max one */
}

void find_odd_average(){
	printf("Please enter positive numbers (end -1 to stop entering):\n");

	float count = 0;
	float sum = 0;											/* Some required variables */
	int num = 0;
	int i=1;
	do
	{
		printf("%d: ",i );
		scanf("%d",&num);										/* takes numbers one by one */
		if(num > 0 && num %2 == 1)
		{
			sum += num;											/* if taken number is positive odd then adds it */
			count++;
		}
		i++;
	} while (num !=-1);											/* repeats the loop while num is not -1 */

	float av = sum / count;
	printf("Average of odd numbers: %.2f \n",av);
}


int main(){

	int max_number = find_max_ditance(5);
	printf("Max dist between two consecutive nums: %d\n\n",max_number);				/* calls the functions */

	find_odd_average();

}