#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{
	// Check argument number
	if (argc != 2 || only_digits(argv[1]) == false)
	{
		printf("Usage: ./caesar key\n");
		return 1;
	}

	//Convert argv[1] from a `string` to an `int`
	int key = 0;
	if (argv[1])
	{
		key = atoi(argv[1]);
	}

	// Prompt user for plaintext
	string plaintext = get_string("plaintext:  ");
	printf("ciphertext: ");

	// Change every char of plaintext
	for (int i = 0, len = strlen(plaintext); i < len; i++)
	{
		printf("%c", rotate(plaintext[i], key));
	}
	printf("\n");
	return 0;

}

// Check the key contains only digits
bool only_digits(string s)
{
	for (int i = 0, len = strlen(s); i < len; i++)
	{
		if (isdigit(s[i]) == 0)
		{
			return false;
		}
	}
	return true;
}

// For each character in the plaintext:
// Rotate the character if it's a letter
char rotate(char c, int n)
{
	if (c >= 'A' && c <= 'Z')
	{
		int new_index =	(c - 'A' + n) % 26;
		return ('A' + new_index);
	}
	else if (c >= 'a' && c <= 'z')
	{
		int new_index =	(c - 'a' + n) % 26;
		return ('a' + new_index);
	}
	else
	{
		return c;
	}
}

