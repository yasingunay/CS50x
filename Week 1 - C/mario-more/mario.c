#include <cs50.h>
#include <stdio.h>

void print_hashes(int height);

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    print_hashes(height);
}

void print_hashes(const int height)
{
    for (int row = 1; row <= height; row++)
    {
        // print_spaces
        for (int space = 1; space <= height - row; space++)
            printf(" ");

        // print_left_hashes
        for (int hash = 1; hash <= row; hash++)
            printf("#");

        // print a space in the middle
        printf(" ");
        printf(" ");

        // print_right_hashes
        for (int hash = 1; hash <= row; hash++)
            printf("#");

        printf("\n");
    }
}