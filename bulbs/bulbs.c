#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
	string message = get_string("Message: ");
	int len = 0;
	len  = strlen(message);

	for (int i = 0; i < len; i++)
	{
		int binary[8] = {0};
		int decimal = message[i];

		int j = 0;
		while (decimal > 0)
		{
			binary[j] = decimal % 2;
			decimal /= 2;
			j++;
		}

		for (int k = BITS_IN_BYTE - 1; k >= 0; k--)
		{
			print_bulb(binary[k]);
		}
		printf("\n");
	}

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}