#include <cs50.h>
#include <stdio.h>

void print_hashes(int height);

int main(void)
{
	int height = 0;

	//get the height from the user
    do
	{
		height = get_int("Height: ");
	}
	while (height < 1 || height > 8);
	print_hashes(height);
}

void print_hashes(const int height)
{
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= height; j++)
		{
			if (i + j >= height + 1)
				printf("#");
			else
				printf(" ");
		}
		printf("\n");
	}

}