#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
	int sum = 0;
	if (output == 'A')
	{
		for (int i = 0; i < weeks; i++)
		{
			sum = sum + hours[i];
		}
		return ((float)sum / weeks);
	}
	else
	{
		for (int i = 0; i < weeks; i++)
		{
			sum = sum + hours[i];
		}
		return (float)sum;
	}
}