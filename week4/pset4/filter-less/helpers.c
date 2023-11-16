#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int avg = round((float) (red + green + blue) / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = round(((float) red * 0.393) + ((float) green * 0.769) + ((float) blue * 0.189));
            int sepiaGreen = round(((float) red * 0.349) + ((float) green * 0.686) + ((float) blue * 0.168));
            int sepiaBlue = round(((float) red * 0.272) + ((float) green * 0.534) + ((float) blue * 0.131));


            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed < 0 ? 0 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen < 0 ? 0 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue < 0 ? 0 : sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, k = width - 1; j <= k; j++, k--)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copyImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float countOfPixels;
            int avgRed;
            int avgGreen;
            int avgBlue;

            RGBTRIPLE middlePixel = copyImage[i][j];
            int middlePixelRed = copyImage[i][j].rgbtRed;
            int middlePixelGreen = copyImage[i][j].rgbtGreen;
            int middlePixelBlue = copyImage[i][j].rgbtBlue;

            if (i == 0 && j == 0)
            {
                countOfPixels = 4.0;
                RGBTRIPLE east = copyImage[i][j + 1];
                RGBTRIPLE south_east = copyImage[i + 1][j + 1];
                RGBTRIPLE south = copyImage[i + 1][j];

                avgRed = middlePixelRed + east.rgbtRed + south_east.rgbtRed + south.rgbtRed;
                avgGreen = middlePixelGreen + east.rgbtGreen + south_east.rgbtGreen + south.rgbtGreen;
                avgBlue = middlePixelBlue + east.rgbtBlue + south_east.rgbtBlue + south.rgbtBlue;


            }
            else if (i == 0 && j == width - 1)
            {
                countOfPixels = 4.0;
                RGBTRIPLE south = copyImage[i + 1][j];
                RGBTRIPLE south_west = copyImage[i + 1][j - 1];
                RGBTRIPLE west = copyImage[i][j - 1];

                avgRed = middlePixelRed + south.rgbtRed + south_west.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + south.rgbtGreen + south_west.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + south.rgbtBlue + south_west.rgbtBlue + west.rgbtBlue;
            }
            else if (i == height - 1 && j == 0)
            {
                countOfPixels = 4.0;
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE north_east = copyImage[i - 1][j + 1];
                RGBTRIPLE east = copyImage[i][j + 1];

                avgRed = middlePixelRed + north.rgbtRed + north_east.rgbtRed + east.rgbtRed;
                avgGreen = middlePixelGreen + north.rgbtGreen + north_east.rgbtGreen + east.rgbtGreen;
                avgBlue = middlePixelBlue + north.rgbtBlue + north_east.rgbtBlue + east.rgbtBlue;
            }
            else if (i == height - 1 && j == width - 1)
            {
                countOfPixels = 4.0;
                RGBTRIPLE north_west = copyImage[i - 1][j - 1];
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE west = copyImage[i][j - 1];

                avgRed = middlePixelRed + north_west.rgbtRed + north.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + north_west.rgbtGreen + north.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + north_west.rgbtBlue + north.rgbtBlue + west.rgbtBlue;
            }
            else if (i == 0)
            {
                countOfPixels = 6.0;
                RGBTRIPLE east = copyImage[i][j + 1];
                RGBTRIPLE south_east = copyImage[i + 1][j + 1];
                RGBTRIPLE south = copyImage[i + 1][j];
                RGBTRIPLE south_west = copyImage[i + 1][j - 1];
                RGBTRIPLE west = copyImage[i][j - 1];

                avgRed = middlePixelRed + east.rgbtRed + south_east.rgbtRed + south.rgbtRed + south_west.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + east.rgbtGreen + south_east.rgbtGreen + south.rgbtGreen + south_west.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + east.rgbtBlue + south_east.rgbtBlue + south.rgbtBlue + south_west.rgbtBlue + west.rgbtBlue;
            }
            else if (j == 0)
            {
                countOfPixels = 6.0;
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE north_east = copyImage[i - 1][j + 1];
                RGBTRIPLE east = copyImage[i][j + 1];
                RGBTRIPLE south_east = copyImage[i + 1][j + 1];
                RGBTRIPLE south = copyImage[i + 1][j];

                avgRed = middlePixelRed + north.rgbtRed + north_east.rgbtRed + east.rgbtRed + south_east.rgbtRed + south.rgbtRed;
                avgGreen = middlePixelGreen + north.rgbtGreen + north_east.rgbtGreen + east.rgbtGreen + south_east.rgbtGreen + south.rgbtGreen;
                avgBlue = middlePixelBlue + north.rgbtBlue + north_east.rgbtBlue + east.rgbtBlue + south_east.rgbtBlue + south.rgbtBlue;
            }
            else if (i == height - 1)
            {
                countOfPixels = 6.0;
                RGBTRIPLE west = copyImage[i][j - 1];
                RGBTRIPLE north_west = copyImage[i - 1][j - 1];
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE north_east = copyImage[i - 1][j + 1];
                RGBTRIPLE east = copyImage[i][j + 1];

                avgRed = middlePixelRed + north_west.rgbtRed + north.rgbtRed + north_east.rgbtRed + east.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + north_west.rgbtGreen + north.rgbtGreen + north_east.rgbtGreen + east.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + north_west.rgbtBlue + north.rgbtBlue + north_east.rgbtBlue + east.rgbtBlue + west.rgbtBlue;
            }
            else if (j == width - 1)
            {
                countOfPixels = 6.0;
                RGBTRIPLE north_west = copyImage[i - 1][j - 1];
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE south = copyImage[i + 1][j];
                RGBTRIPLE south_west = copyImage[i + 1][j - 1];
                RGBTRIPLE west = copyImage[i][j - 1];

                avgRed = middlePixelRed + north_west.rgbtRed + north.rgbtRed + south.rgbtRed + south_west.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + north_west.rgbtGreen + north.rgbtGreen + south.rgbtGreen + south_west.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + north_west.rgbtBlue + north.rgbtBlue + south.rgbtBlue + south_west.rgbtBlue + west.rgbtBlue;
            }
            else
            {
                countOfPixels = 9.0;
                RGBTRIPLE north_west = copyImage[i - 1][j - 1];
                RGBTRIPLE north = copyImage[i - 1][j];
                RGBTRIPLE north_east = copyImage[i - 1][j + 1];
                RGBTRIPLE east = copyImage[i][j + 1];
                RGBTRIPLE south_east = copyImage[i + 1][j + 1];
                RGBTRIPLE south = copyImage[i + 1][j];
                RGBTRIPLE south_west = copyImage[i + 1][j - 1];
                RGBTRIPLE west = copyImage[i][j - 1];

                avgRed = middlePixelRed + north_west.rgbtRed + north.rgbtRed + north_east.rgbtRed + east.rgbtRed + south_east.rgbtRed + south.rgbtRed + south_west.rgbtRed + west.rgbtRed;
                avgGreen = middlePixelGreen + north_west.rgbtGreen + north.rgbtGreen + north_east.rgbtGreen + east.rgbtGreen + south_east.rgbtGreen + south.rgbtGreen + south_west.rgbtGreen + west.rgbtGreen;
                avgBlue = middlePixelBlue + north_west.rgbtBlue + north.rgbtBlue + north_east.rgbtBlue + east.rgbtBlue + south_east.rgbtBlue + south.rgbtBlue + south_west.rgbtBlue + west.rgbtBlue;
            }

            avgRed = round((float) avgRed / countOfPixels);
            avgGreen = round((float) avgGreen / countOfPixels);
            avgBlue = round((float) avgBlue / countOfPixels);

            image[i][j].rgbtRed = avgRed;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtBlue = avgBlue;
        }
    }

    return;
}
