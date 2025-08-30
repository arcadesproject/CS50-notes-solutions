#include "helpers.h"
#include <math.h>

RGBTRIPLE blurred_averages(int row, int column, int max_height, int max_width,
                                 RGBTRIPLE image[max_height][max_width]);
RGBTRIPLE modify_edges(int row, int column, int max_height, int max_width,
                                 RGBTRIPLE image[max_height][max_width]);
// Convert image to grayscale
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
            RGBTRIPLE blurred = blurred_averages(i, j, height, width, copy);
            image[i][j] = blurred;
        }
    }
}

// Detect edges
// Like image blurring, edge detection also works by taking each pixel, and modifying it based on the 3x3 grid of pixels that surrounds that pixel.
// Sobel operator computes the new value of each pixel by taking a weighted sum of the values for the surrounding pixels.
// Have to detect edges in x direction and one for y direction
// Gx and Gy then combines in calculating sqrt of Gx^2 + Gy^2
// pixels past edge just treat as black so rgb 000000
void edges(int height, int width, RGBTRIPLE image[height][width])
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
            RGBTRIPLE modified_edges = modify_edges(i, j, height, width, copy);
            image[i][j] = modified_edges;
        }
    }
}

RGBTRIPLE blurred_averages(int row, int column, int max_height, int max_width,
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

//scuffed attempt
// RGBTRIPLE modify_edges(int row, int column, int max_height, int max_width,
//                                  RGBTRIPLE image[max_height][max_width])
// {
//     int rx = 0;
//     int gx = 0;
//     int bx = 0;
//     int ry = 0;
//     int gy = 0;
//     int by = 0;

//     for (int i = row - 1; i <= row + 1; i++)
//     {
//         if (i >= 0 && i < max_height)
//         {
//             for (int j = column - 1; j <= column + 1; j++)
//             {
//                 if (j >= 0 && j < max_width)
//                 {
//                     int r = image[i][j].rgbtRed;
//                     int g = image[i][j].rgbtGreen;
//                     int b = image[i][j].rgbtBlue;
//                     if (i == row-1)
//                     {
//                         if (j == column-1)
//                         {
//                             rx += r * -1;
//                             gx += g * -1;
//                             bx += b * -1;
//                             ry += r * -1;
//                             gy += g * -1;
//                             by += b * -1;
//                         }
//                         else if (j == column)
//                         {
//                             ry += r * -2;
//                             gy += g * -2;
//                             by += b * -2;
//                         }
//                         else if (j == column + 1)
//                         {
//                             rx += r;
//                             gx += g;
//                             bx += b;
//                             ry += r * -1;
//                             gy += g * -1;
//                             by += b * -1;
//                         }
//                     }
//                     else if (i == row)
//                     {
//                         if (j == column-1)
//                         {
//                             rx += r * -2;
//                             gx += g * -2;
//                             bx += b * -2;
//                         }
//                         else if (j == column + 1)
//                         {
//                             rx += r * 2;
//                             gx += g * 2;
//                             bx += b * 2;
//                         }
//                     }
//                     else if (i == row + 1)
//                     {
//                         if (j == column-1)
//                         {
//                             rx += r * -1;
//                             gx += g * -1;
//                             bx += b * -1;
//                             ry += r * 1;
//                             gy += g * 1;
//                             by += b * 1;
//                         }
//                         else if (j == column)
//                         {
//                             ry += r * 2;
//                             gy += g * 2;
//                             by += b * 2;
//                         }
//                         else if (j == column + 1)
//                         {
//                             rx += r;
//                             gx += g;
//                             bx += b;
//                             ry += r;
//                             gy += g;
//                             by += b;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     RGBTRIPLE result;
//     result.rgbtRed = round(sqrt(pow(rx, 2) + pow(ry, 2)));
//     result.rgbtGreen = round(sqrt(pow(gx, 2) + pow(gy, 2)));
//     result.rgbtBlue = round(sqrt(pow(bx, 2) + pow(by, 2)));

//     if (result.rgbtRed > 255)   result.rgbtRed = 255;
//     if (result.rgbtGreen > 255) result.rgbtGreen = 255;
//     if (result.rgbtBlue > 255)  result.rgbtBlue = 255;

//     return result;
// }

// Apply Sobel edge detection operator to a single pixel at (row, column).
// Looks at the 3x3 neighborhood of that pixel, applies Gx and Gy kernels,
// then computes the gradient magnitude for each color channel.
// TABLE DRIVEN programming
// Convolution is a mathematical operation where you take a small grid of numbers (called a kernel or filter) and “slide” it across a bigger grid (like an image).
RGBTRIPLE modify_edges(int row, int column, int max_height, int max_width,
                       RGBTRIPLE image[max_height][max_width])
{
    // Sobel kernels for x-gradient and y-gradient
    const int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // Accumulators for each color channel, in both x and y directions
    int rx = 0, gx = 0, bx = 0;   // red, green, blue × Gx
    int ry = 0, gy = 0, by = 0;   // red, green, blue × Gy

    // Iterate over the 3x3 neighborhood around the target pixel
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int row_n = row + i;   // neighbor row index
            int col_n = column + j; // neighbor col index

            // If neighbor is outside image bounds, skip it (treat as black)
            if (row_n < 0 || row_n >= max_height || col_n < 0 || col_n >= max_width)
                continue;

            // Neighbor’s color values
            int r = image[row_n][col_n].rgbtRed;
            int g = image[row_n][col_n].rgbtGreen;
            int b = image[row_n][col_n].rgbtBlue;

            // Get corresponding Sobel kernel coefficients
            int gx_value = Gx[i + 1][j + 1];
            int gy_value = Gy[i + 1][j + 1];

            // Apply kernels to each color channel
            rx += r * gx_value;
            gx += g * gx_value;
            bx += b * gx_value;

            ry += r * gy_value;
            gy += g * gy_value;
            by += b * gy_value;
        }
    }

    // Combine Gx and Gy results into gradient magnitude for each channel
    RGBTRIPLE result;
    result.rgbtRed   = fmin(255, round(sqrt(rx * rx + ry * ry)));
    result.rgbtGreen = fmin(255, round(sqrt(gx * gx + gy * gy)));
    result.rgbtBlue  = fmin(255, round(sqrt(bx * bx + by * by)));

    return result;
}
