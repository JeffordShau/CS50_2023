#include "helpers.h"
#include <math.h>
#include <stdlib.h>

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
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            double redx  = 0;
            double greenx = 0;
            double bluex = 0;
            double redy  = 0;
            double greeny = 0;
            double bluey = 0;
            int RGB[3];

            for (int r = -1; r < 2; r++) {
                for (int c = -1; c < 2; c++) {
                    if (r + i == -1 || c + j == -1 || r + i == height || c + j == width) {
                        continue;
                    }

                    redx += imageCopy[r + i][c + j].rgbtRed * gx[r + 1][c + 1];
                    greenx += imageCopy[r + i][c + j].rgbtGreen * gx[r + 1][c + 1];
                    bluex += imageCopy[r + i][c + j].rgbtBlue * gx[r + 1][c + 1];
                    redy += imageCopy[r + i][c + j].rgbtRed * gy[r + 1][c + 1];
                    greeny += imageCopy[r + i][c + j].rgbtGreen * gy[r + 1][c + 1];
                    bluey += imageCopy[r + i][c + j].rgbtBlue * gy[r + 1][c + 1];
                    // counter += 1;
                }
            }

            RGB[0] = round(sqrt(pow(redx, 2) + pow(redy, 2)));
            RGB[1] = round(sqrt(pow(greenx, 2) + pow(greeny, 2)));
            RGB[2] = round(sqrt(pow(bluex, 2) + pow(bluey, 2)));

            for (int k = 0; k < 3; k++) {
                if (RGB[k] > 255) {
                    RGB[k] = 255;
                }
                else if (RGB[k] < 0) {
                    RGB[k] = 0;
                }
            }

            image[i][j].rgbtRed = RGB[0];
            image[i][j].rgbtGreen = RGB[1];
            image[i][j].rgbtBlue = RGB[2];
        }
    }
    return;
}
