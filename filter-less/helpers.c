#include "helpers.h"
#include <math.h> // added for "round" usage

// Function prototype for clampColor
int clampColor(int unclamped);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // count average & set all to avg
            int roundedAverage =
                round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtRed = roundedAverage;
            image[i][j].rgbtGreen = roundedAverage;
            image[i][j].rgbtBlue = roundedAverage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // initiate temp. values
            int sepiaRed, sepiaGreen, sepiaBlue;

            // calculate each color, will be clamped later
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                             .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                               .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                              .131 * image[i][j].rgbtBlue);

            // apply changes
            image[i][j].rgbtRed = clampColor(sepiaRed);
            image[i][j].rgbtGreen = clampColor(sepiaGreen);
            image[i][j].rgbtBlue = clampColor(sepiaBlue);
        }
    }
    return;
}

// clamp values for sepia
int clampColor(int unclamped)
{
    if (unclamped < 0)
        return 0;
    if (unclamped > 255)
        return 255;
    return unclamped;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop all
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // find the opposite pixel, starting from the last one (j-1, bcs of 0-indexed arrays)
            int oppositeIndex = width - 1 - j;

            // swap the opposites
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][oppositeIndex];
            image[i][oppositeIndex] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    // Loop all
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // fill in temp array
            temp[i][j] = image[i][j];
        }
    }

    // Calculate blur for each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Neighbor positions include the pixel itself and surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newI = i + di;
                    int newJ = j + dj;

                    // Check if neighbor is within the image boundaries
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        sumRed += image[newI][newJ].rgbtRed;
                        sumGreen += image[newI][newJ].rgbtGreen;
                        sumBlue += image[newI][newJ].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate average values
            temp[i][j].rgbtRed = round((float) sumRed / count);
            temp[i][j].rgbtGreen = round((float) sumGreen / count);
            temp[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    // Copy temp back to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
