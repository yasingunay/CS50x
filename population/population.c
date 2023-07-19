#include <cs50.h>
#include <stdio.h>

int main(void)
{
	int size = 0;
	int end_size = 0;
	int years = 0;

	//Prompt for start size
	do
	{
		size = get_int("Start size: ");
	}
	while (size < 9);

	//Prompt for end size
	do
	{
		end_size = get_int("End size: ");
	}
	while (end_size < size);

	// Calculate number of years until we reach threshold
	while (size < end_size)
	{
		size = size + (size / 3) - (size / 4);
		years++;
		//to see the changement of variables in the loop
		//printf("after %i Years: ", years);
		//printf("Size:  %i\n",size);
	}

	//Print number of years
	printf("Years: %i\n", years);

	return (0);
}
