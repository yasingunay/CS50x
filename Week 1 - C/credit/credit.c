#include <cs50.h>
#include <stdio.h>
#include <math.h>



int calculate_sum(long number);
int multiply_and_sum(int last_digit);
int number_of_digits(long number);
bool is_valid_amex(long mumber, int nb_digits);
bool is_valid_mastercard(long number, int nb_digits);
bool is_valid_visa(long number, int nb_digits);


int main(void)
{
    // Prompt the user for a credit card number
	long number = 0;
	int sum = 0;
	int nb_digits = 0;

	number = get_long("Number: ");
	sum = calculate_sum(number);
	nb_digits = number_of_digits(number);
	bool amex = is_valid_amex(number, nb_digits);
	bool mastercard = is_valid_mastercard(number, nb_digits);
	bool visa = is_valid_visa(number, nb_digits);
	if (sum % 10 != 0)
	{
		printf("INVALID\n");
		return 0;
	}
	else if (amex == true)
	{
		printf("AMEX\n");
	}
	else if (mastercard == true)
	{
		printf("MASTERCARD\n");
	}
	else if (visa == true)
	{
		printf("VISA\n");
	}
	else
	{
		printf("INVALID\n");
		return 0;
	}
}

int number_of_digits(long number)
{
	int count = 0;
	while (number > 0)
	{
		number = number / 10;
		count++;
	}
	return count;
}

bool is_valid_amex(long number, int nb_digits)
{
	int first_two_digits = number / pow(10, 13);
	if (nb_digits == 15 && (first_two_digits == 34 || first_two_digits == 37))
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool is_valid_mastercard(long number, int nb_digits)
{
	int first_two_digits = number / pow(10, 14);
	if (nb_digits == 16 && (first_two_digits > 50 &&  first_two_digits < 56))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_valid_visa(long number, int nb_digits)
{
	if (nb_digits == 13)
	{
		int first_digit = number / pow(10, 12);
		if (first_digit == 4)
		{
			return true;
		}
	}
	else if (nb_digits == 16)
	{
		int first_digit = number / pow(10, 15);
		if (first_digit == 4)
		{
			return true;
		}
	}
	return false;
}

int calculate_sum(long number)
{
	int sum = 0;
	int last_digit = 0;
	bool is_alternate_digit = false;
	while (number > 0)
	{
		if (is_alternate_digit == true)
		{
			last_digit = number % 10;
			sum = sum + multiply_and_sum(last_digit);
		}
		else
		{
			last_digit = number % 10;
			sum = sum + last_digit;
		}
		is_alternate_digit = !is_alternate_digit;
		number = number / 10 ;

	}
	return (sum);
}


//multiply the number’s second-to-last digits by 2
//add those products’ digits (i.e., not the products themselves) together
int multiply_and_sum(int last_digit)
{
	int sum = 0;
	int last_digit_multiply = 0;
	int multiply = last_digit * 2;
	while (multiply > 0)
	{
		last_digit_multiply = multiply % 10;
		sum = sum + last_digit_multiply;
		multiply = multiply / 10;
	}
	return sum;
}




