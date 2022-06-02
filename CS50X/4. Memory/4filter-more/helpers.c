#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pixelbrightness=0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            pixelbrightness = (int)(0.5 + ((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = pixelbrightness;
            image[i][j].rgbtGreen = pixelbrightness;
            image[i][j].rgbtRed = pixelbrightness;
        }
    }
    return;
}

// Sepia image
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed=0;
    float sepiaGreen=0;
    float sepiaBlue=0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            sepiaRed = .393 * (float) image[i][j].rgbtRed + .769 * (float) image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * (float) image[i][j].rgbtRed + .686 * (float) image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * (float) image[i][j].rgbtRed + .534 * (float) image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            if (sepiaRed>255){sepiaRed=255;}
            if (sepiaGreen>255){sepiaGreen=255;}
            if (sepiaBlue>255){sepiaBlue=255;}
            image[i][j].rgbtBlue = (int) sepiaBlue;
            image[i][j].rgbtGreen = (int) sepiaGreen;
            image[i][j].rgbtRed = (int) sepiaRed;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int halfwidth = (int)width/2;
    RGBTRIPLE temp [halfwidth];
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<halfwidth; j++)
        {
            temp [j] = image [i][j];
            image [i][j] = image[i][width-1-j];
            image [i][width-1-j] = temp [j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int blurbox = 1; //represents number of pixels on either side to use for blurring
    float total[4]; //stores the total of the pixels to be blurred and their count.
    RGBTRIPLE temp[height][width];

    // temporarily store the original image to serve as reference while blurring.
    // Since we don't want to take reference from an already blurred pixel.
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width; j++)
        {
            temp[i][j]=image[i][j];
        }
    }

    //loop over every pixel (i,j) of the image
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {

            // reset total to 0 at start of each loop
            for (int m=0; m<4; m++)
            {
                total [m]=0.0;
            }

            //loops over a blurbox sized box around the pixel
            for (int k=0; k<blurbox*2+1; k++)
            {
                for (int l=0; l<blurbox*2+1; l++)
                {
                    //checks to ensure not out of bounds
                    if ((i-blurbox+k) >= 0 && (i-blurbox+k) < height && (j-blurbox+l)>=0 && (j-blurbox+l)<width)
                    {
                        //sum up rgb values in the blurbox, as well as the count of the number of pixels summed up
                        total[0] += temp[i-blurbox+k][j-blurbox+l].rgbtBlue;
                        total[1] += temp[i-blurbox+k][j-blurbox+l].rgbtGreen;
                        total[2] += temp[i-blurbox+k][j-blurbox+l].rgbtRed;
                        total[3] ++;
                    }
                }
            }
            //average the rgb values in the blurbox
            image[i][j].rgbtBlue = (int) round(total[0]/total[3]);
            image[i][j].rgbtGreen = (int) round(total[1]/total[3]);
            image[i][j].rgbtRed = (int) round(total[2]/total[3]);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    double totalx[3];
    double totaly[3];
    RGBTRIPLE temp[height][width];
    int G[3][3] = {{-1,0,1,}, {-2,0,2,}, {-1,0,1}};

    // temporarily store the original image to serve as reference while blurring.
    // Since we don't want to take reference from an already Sobel-ed pixel.
    for (int i=0; i<height;i++)
    {
        for (int j=0; j<width; j++)
        {
            temp[i][j]=image[i][j];
        }
    }

    //loop over every pixel (i,j) of the image
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {

            // reset total to 0 at start of each loop
            for (int m=0; m<3; m++)
            {
                totalx [m]=0;
                totaly [m]=0;
            }

            //loops over the adjacent pixels
            for (int k=0; k<3; k++)
            {
                for (int l=0; l<3; l++)
                {
                    //checks to ensure not out of bounds
                    if ((i-1+k) >= 0 && (i-1+k) < height && (j-1+l)>=0 && (j-1+l)<width)
                    {
                        //sum up adjusted rgb values in the pixels
                        totalx[0] += G[k][l] * temp[i-1+k][j-1+l].rgbtBlue;
                        totalx[1] += G[k][l] * temp[i-1+k][j-1+l].rgbtGreen;
                        totalx[2] += G[k][l] * temp[i-1+k][j-1+l].rgbtRed;
                        totaly[0] += G[l][k] * temp[i-1+k][j-1+l].rgbtBlue;
                        totaly[1] += G[l][k] * temp[i-1+k][j-1+l].rgbtGreen;
                        totaly[2] += G[l][k] * temp[i-1+k][j-1+l].rgbtRed;
                    }
                }
            }
            //calculate the new rgb values
            for (int n=0; n<3; n++)
            {
                int a = (int) round (pow (pow (totalx[n],2.0) + pow(totaly[n],2.0),0.5));
                if (a>255)
                {
                    a=255;
                }
                switch (n)
                {
                    case 0:
                        image[i][j].rgbtBlue = a;
                        break;
                    case 1:
                        image[i][j].rgbtGreen = a;
                        break;
                    case 2:
                        image[i][j].rgbtRed = a;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return;
}
