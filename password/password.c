// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
	int i = 0;
	int upper = 0;
	int lower = 0;
	int number = 0;
	int symbol = 0;
	while (password[i] != '\0')
	{
		if (isupper(password[i]) != 0)
			upper++;
		else if (islower(password[i]) != 0)
			lower++;
		else if (isalnum(password[i]) != 0)
			number++;
		else if (isalpha(password[i]) == 0)
			symbol++;
		i++;
	}
	if (upper <= 0 || lower <= 0 || number <= 0 || symbol <= 0)
    	return false;
	else
		return true;
}
