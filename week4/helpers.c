#include "helpers.h"
#include <math.h>

int check_max(int n, int max);
RGBTRIPLE get_neighbour_averages(int row, int column, int max_height, int max_width,
                                 RGBTRIPLE image[max_height][max_width]);

// Convert image to grayscale
// Gets average of rgb to keep similar brightness
// Converts rgb to all same value to make gray
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int average = round((r + g + b) / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    const int max = 255;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaRed = check_max(sepiaRed, max);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaGreen = check_max(sepiaGreen, max);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            sepiaBlue = check_max(sepiaBlue, max);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

int check_max(int n, int max)
{
    if (n > max)
    {
        return max;
    }
    return n;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        // Only go over first half then get corresponding
        // so say width = 300, get up to 140 so width(300) - 140 = 160 and they swap in those
        // positions
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

// Blur image
// Using box blur
// each pixel and, for each color value, giving it a new value by averaging the color values of
// neighboring pixels row +- 1, column +- 1 make sure only to get pixels in the image so no over
// height or width or under 0
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
            RGBTRIPLE blurred = get_neighbour_averages(i, j, height, width, copy);
            image[i][j] = blurred;
        }
    }
}

RGBTRIPLE get_neighbour_averages(int row, int column, int max_height, int max_width,
                                 RGBTRIPLE image[max_height][max_width])
{
    int totalr = 0;
    int totalg = 0;
    int totalb = 0;
    int count = 0;
    RGBTRIPLE result;

    for (int i = row - 1; i <= row + 1; i++)
    {
        if (i >= 0 && i < max_height)
        {
            for (int j = column - 1; j <= column + 1; j++)
            {
                if (j >= 0 && j < max_width)
                {
                    int r = image[i][j].rgbtRed;
                    int g = image[i][j].rgbtGreen;
                    int b = image[i][j].rgbtBlue;
                    totalr += r;
                    totalg += g;
                    totalb += b;
                    count++;
                }
            }
        }
    }

    if (count == 0)
        count = 1;
    result.rgbtRed = round(totalr / (count * 1.0));
    result.rgbtGreen = round(totalg / (count * 1.0));
    result.rgbtBlue = round(totalb / (count * 1.0));
    return result;
}
