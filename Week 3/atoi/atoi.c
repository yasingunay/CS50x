#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
   	printf("%i\n", convert(input));
}

int convert(string input)
{
	// Base case
	if (input[0] == '\0')
		return 0;

	// Recursive case
    int index = 0;
	while (input[index] != '\0')
	{
		index++;
	}
	int last_digit = input[index - 1] -= 48;
	input[index - 1] = '\0';
	return last_digit + 10 * convert(input);
}