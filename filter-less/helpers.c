#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int grayAvg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = grayAvg;
            image[i][j].rgbtGreen = grayAvg;
            image[i][j].rgbtBlue = grayAvg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            long sepiaRGB[] = {round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue), round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue), round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue)};
            for (int k = 0; k < 3; k++) {
                if (sepiaRGB[k] > 255) {
                    sepiaRGB[k] = 255;
                }
            }
            image[i][j].rgbtRed = (int) sepiaRGB[0];
            image[i][j].rgbtGreen = (int) sepiaRGB[1];
            image[i][j].rgbtBlue = (int) sepiaRGB[2];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *temp = calloc(width, sizeof(RGBTRIPLE));
    // RGBTRIPLE temp[width * sizeof(RGBTRIPLE)];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp[width - j - 1] = image[i][j];
        }
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[j];
        }
    }
    free(temp);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // border of RGBTRIPLES with value 0 around image
    // RGBTRIPLE *imageCopy = calloc(height + 2, (width + 2) *sizeof(RGBTRIPLE));
    RGBTRIPLE imageCopy[height][width * sizeof(RGBTRIPLE)];

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            imageCopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imageCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            float counter = 0;
            int red  = 0;
            int green = 0;
            int blue = 0;

            for (int r = i - 1; r < i + 2; r++) {
                for (int c = j - 1; c < j + 2; c++) {
                    if (r == -1 || c == -1 || r == height || c == width) {
                        continue;
                    }

                    red += imageCopy[r][c].rgbtRed;
                    green += imageCopy[r][c].rgbtGreen;
                    blue += imageCopy[r][c].rgbtBlue;
                    counter += 1;
                }
            }

            image[i][j].rgbtRed = round(red / counter);
            image[i][j].rgbtGreen = round(green / counter);
            image[i][j].rgbtBlue = round(blue / counter);
        }
    }
    // free(imageCopy);
    return;
}
