// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    float tax_amount = 0;
    float tip_amount = 0;
    float half = 0;
    tax_amount = bill * (tax / 100);
    bill += tax_amount;
    tip_amount = bill * ((float)tip / 100);
    half = (bill + tip_amount) / 2;

    return (half);
}
