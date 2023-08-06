#include "helpers.h"
#include <math.h>

#define BLUE_COLOR 0
#define GREEN_COLOR 1
#define RED_COLOR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // float sepiaRed = 0.0;
    // float sepiaGreen = 0.0;
    // float sepiaBlue = 0.0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            if (sepiaRed > 255)
                sepiaRed = 255;
            if (sepiaGreen > 255)
                sepiaGreen = 255;
            if (sepiaBlue > 255)
                sepiaBlue = 255;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Swap colors of two pixels
void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE tmp;
    tmp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }

    return;
}

int get_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_code)
{
    float count = 0;
    int sum = 0;
    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            if (row < 0 || column < 0 || row >= height || column >= width)
            {
                continue;
            }
            if (color_code == BLUE_COLOR)
            {
                sum = sum + image[row][column].rgbtBlue;
            }
            else if (color_code == GREEN_COLOR)
            {
                sum = sum + image[row][column].rgbtGreen;
            }
            else
            {
                sum = sum + image[row][column].rgbtRed;
            }
            count++;
        }
    }
    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Create a copy of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            image[i][j].rgbtBlue = get_blur(i, j, height, width, copy, BLUE_COLOR);
            image[i][j].rgbtGreen = get_blur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtRed = get_blur(i, j, height, width, copy, RED_COLOR);
        }
    }
    return;
}
