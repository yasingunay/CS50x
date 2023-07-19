// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string word);

int main(int argc, string argv[])
{
    if (argc != 2)
	{
		printf("Usage: ./no-vowels word\n");
		return 1;
	}
	printf("%s\n", replace(argv[1]));
}

string replace(string word)
{
	int lenght = 0 ;
	lenght = strlen(word);
	for (int i = 0; i < lenght; i++)
	{
		switch (word[i])
		{
			case 'a':
				word[i] = '6';
				break;

			case 'e':
				word[i] = '3';
				break;

			case 'i':
				word[i] = '1';
				break;

			case 'o':
				word[i] = '0';
				break;

			default:
				break;
		}
	}
	return word;
}