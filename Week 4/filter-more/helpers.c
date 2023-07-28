#include "helpers.h"
#include <math.h>

#define BLUE 0
#define GREEN 1
#define RED 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

void swap(RGBTRIPLE *image1, RGBTRIPLE *image2)
{
    RGBTRIPLE tmp;

    tmp = *image2;
    *image2 = *image1;
    *image1 = tmp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - j - 1]);
        }
    }
    return;
}

int get_blur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_code)
{
    int sum = 0;
    float counter = 0.0;

    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            if (column < 0 || column >= width || row < 0 || row >= height)
            {
                continue;
            }
            if (color_code == BLUE)
                sum = sum + image[row][column].rgbtBlue;
            else if (color_code == GREEN)
                sum = sum + image[row][column].rgbtGreen;
            else
                sum = sum + image[row][column].rgbtRed;
            counter++;
        }
    }
    return round(sum / counter);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

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
            image[i][j].rgbtBlue = get_blur(i, j, height, width, copy, BLUE);
            image[i][j].rgbtGreen = get_blur(i, j, height, width, copy, GREEN);
            image[i][j].rgbtRed = get_blur(i, j, height, width, copy, RED);
        }
    }
    return;
}

int get_edges(int i, int j, int height, int width, RGBTRIPLE image[height][width], int color_code)
{
    int sum_gx = 0;
    int sum_gy = 0;

    // Use 3x3 matrix to keep the values of Gx and Gy
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            // Pass edges
            if (column < 0 || column >= width || row < 0 || row >= height)
            {
                continue;
            }
            if (color_code == BLUE)
            {
                sum_gx = sum_gx + image[row][column].rgbtBlue * gx[row - i + 1][column - j + 1];
                sum_gy = sum_gy + image[row][column].rgbtBlue * gy[row - i + 1][column - j + 1];
            }

            else if (color_code == GREEN)
            {
                sum_gx = sum_gx + image[row][column].rgbtGreen * gx[row - i + 1][column - j + 1];
                sum_gy = sum_gy + image[row][column].rgbtGreen * gy[row - i + 1][column - j + 1];
            }
            else
            {
                sum_gx = sum_gx + image[row][column].rgbtRed * gx[row - i + 1][column - j + 1];
                sum_gy = sum_gy + image[row][column].rgbtRed * gy[row - i + 1][column - j + 1];
            }
        }
    }
    // If the value exceeds the max channel value of 255, cap the value at the number 255
    return fmin(255, round(sqrt(sum_gx * sum_gx + sum_gy * sum_gy)));
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Copy image not to lose the original pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Iterate over the image pixel by pixel and apply the Sobel operator for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = get_edges(i, j, height, width, copy, BLUE);
            image[i][j].rgbtGreen = get_edges(i, j, height, width, copy, GREEN);
            image[i][j].rgbtRed = get_edges(i, j, height, width, copy, RED);
        }
    }
    return;
}
