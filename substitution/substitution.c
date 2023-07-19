#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool check_key(string s);
char map_letter(char letter, string s);

int main(int argc, string argv[])
{
	// Check number of command-line arguments
	if (argc != 2)
	{
		printf("Usage: ./substitution key\n");
		return 1;
	}

	// Check the key is valide or not
	if (argv[1])
	{
		if (check_key(argv[1]) == 0)
			return 1;
	}

	// Prompt the user for a string of plaintext
	string plaintext = get_string("plaintext:  ");

	// Map each letter and print ciphertext
	printf("ciphertext: ");
	for (int i = 0; plaintext[i] != '\0'; i++)
	{
		printf("%c", map_letter(plaintext[i], argv[1]));
	}
	printf("\n");
	return 0;
}

bool check_key(string s)
{
	// Check key lenght
	if (strlen(s) != 26)
	{
		printf("Key must contain 26 characters.\n");
		return false;
	}

	// Check for non-aphabetic characters
	for (int i = 0; i < 26; i++)
	{
		if (isalpha(s[i]) == 0)
		{
			printf("The key must consist of only letters of the alphabet.\n");
			return false;
		}
	}

	// Check for repetad chracters(case-insensitive)
	int char_count[26] = {0};
	for (int i = 0; i < 26; i++)
	{
		char lowercase_char = tolower(s[i]);

		if (lowercase_char >= 'a' && lowercase_char <= 'z')
		{
			char_count[lowercase_char - 'a']++;
			if (char_count[lowercase_char - 'a'] > 1)
			{
				printf("The key has repeated characters.\n");
				return false;
			}
		}
	}
	return true;
}

char map_letter(char letter, string s)
{
	if (letter >= 'A' && letter <= 'Z')
	{
		int index = letter - 'A';
			return toupper(s[index]);
	}
	else if (letter >= 'a' && letter <= 'z')
	{
		int index = letter - 'a';
			return tolower(s[index]);
	}
	return letter;
}