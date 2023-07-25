#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel in the image.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Check if the pixel is black (all color components are 0x00).
            if (image[i][j].rgbtRed == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtBlue == 0)
            {
                // Change the color to the desired color.
                image[i][j].rgbtRed = 0;
                image[i][j].rgbtGreen = 255;
                image[i][j].rgbtBlue = 0;
            }
        }
    }
}
