#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int numbers[5] = {5, 1, 4, 2, 3};
    int min_index;
    int temp = 0;

    // Outer loop for iterating through the array elements
    for (int i = 0; i < 4; i++)
    {
        // Assume the current index has the minimum value
        min_index = i;

        // Inner loop for finding the minimum value in the unsorted part of the array
        for (int j = i + 1; j < 5; j++)
        {
            // Check if the current element is smaller than the assumed minimum
            if (numbers[j] < numbers[min_index])
                min_index = j;
        }

        // Swap the current element with the minimum element found
        temp = numbers[i];
        numbers[i] = numbers[min_index];
        numbers[min_index] = temp;
    }

    for (int k = 0; k < 5; k++)
    {
        printf("%d", numbers[k]);
    }
    printf("\n");
}
