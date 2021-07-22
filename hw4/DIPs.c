#include "DIPs.h"
#include "Constants.h"
#include "Image.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


/* Example of DIP */
/* age the image to make it look like old picture */
IMAGE *Aging(IMAGE *image)
{
    int x, y;
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	    SetPixelB(image, x, y, (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 5);
            SetPixelR(image, x, y, (unsigned char)(GetPixelB(image, x, y)*1.6));
            SetPixelG(image, x, y, (unsigned char)(GetPixelB(image, x, y)*1.6));
	}
    }
    return image;
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{
    int x, y;
    int tmpr = 0, tmpg = 0, tmpb = 0;
   
    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    unsigned char R_temp[WIDTH][HEIGHT];
    unsigned char G_temp[WIDTH][HEIGHT];
    unsigned char B_temp[WIDTH][HEIGHT];
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R_temp[x][y] = GetPixelR(image, x, y);
            G_temp[x][y] = GetPixelG(image, x, y);
            B_temp[x][y] = GetPixelB(image, x, y);
        }
    }
    for (x = 1; x < WIDTH - 1; x++)
    {   for (y = 1; y < HEIGHT - 1; y++)
        {   
	    tmpr = 9 * GetPixelR(image, x, y) - GetPixelR(image, x-1, y-1) - GetPixelR(image, x-1, y) - GetPixelR(image, x-1, y+1) - GetPixelR(image, x, y-1) - GetPixelR(image, x, y+1) - GetPixelR(image, x+1, y-1) - GetPixelR(image, x+1, y) - GetPixelR(image, x+1, y+1);
            tmpg = 9 * GetPixelG(image, x, y) - GetPixelG(image, x-1, y-1) - GetPixelG(image, x-1, y) - GetPixelG(image, x-1, y+1) - GetPixelG(image, x, y-1) - GetPixelG(image, x, y+1) - GetPixelG(image, x+1, y-1) - GetPixelG(image, x+1, y) - GetPixelG(image, x+1, y+1);
            tmpb = 9 * GetPixelB(image, x, y) - GetPixelB(image, x-1, y-1) - GetPixelB(image, x-1, y) - GetPixelB(image, x-1, y+1) - GetPixelB(image, x, y-1) - GetPixelB(image, x, y+1) - GetPixelB(image, x+1, y-1) - GetPixelB(image, x+1, y) - GetPixelB(image, x+1, y+1);

        R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
        G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
        B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
        tmpr = tmpg = tmpb = 0;
        }
    }
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {  
	    SetPixelR(image, x, y, R_temp[x][y]);
            SetPixelG(image, x, y, G_temp[x][y]);
            SetPixelB(image, x, y, B_temp[x][y]);
        }
    }
    return image;
}

// edge detection function
IMAGE *Edge(IMAGE *image)
{   
    int x, y, m, n, a, b;

    int WIDTH = ImageWidth(image);
    int HEIGHT = ImageHeight(image);

    unsigned char   tmpR[WIDTH][HEIGHT];
    unsigned char   tmpG[WIDTH][HEIGHT];
    unsigned char   tmpB[WIDTH][HEIGHT];

    for (y = 0; y < HEIGHT; y++){
        for (x = 0; x < WIDTH; x++) {
            tmpR[x][y] = GetPixelR(image, x, y);
            tmpG[x][y] = GetPixelG(image, x, y);
            tmpB[x][y] = GetPixelB(image, x, y);
        }
    }
    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < HEIGHT - 1; y++){
        for (x = 1; x < WIDTH - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= WIDTH) ? WIDTH - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= HEIGHT) ? HEIGHT - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (tmpR[x][y] - tmpR[a][b]);
                    sumG += (tmpG[x][y] - tmpG[a][b]);
                    sumB += (tmpB[x][y] - tmpB[a][b]);
                }
            }
            SetPixelR(image, x, y, ((sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < MIN_PIXEL) ? MIN_PIXEL: sumR));
            SetPixelG(image, x, y, ((sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < MIN_PIXEL) ? MIN_PIXEL: sumG));
            SetPixelB(image ,x, y, ((sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < MIN_PIXEL) ? MIN_PIXEL: sumB));
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < HEIGHT; y++) {
        SetPixelR(image, 0, y, 0);
        SetPixelG(image, 0, y, 0);
        SetPixelB(image, 0, y, 0);
        SetPixelR(image, WIDTH-1, y, 0);
        SetPixelG(image, WIDTH-1, y, 0);
        SetPixelB(image, WIDTH-1, y, 0);
    }
    for (x = 0; x < WIDTH; x++) {
        SetPixelR(image, x, 0, 0);
        SetPixelG(image, x, 0, 0);
        SetPixelB(image, x, 0, 0);
        SetPixelR(image, x, HEIGHT-1, 0);
        SetPixelG(image, x, HEIGHT-1, 0);
        SetPixelB(image, x, HEIGHT-1, 0);
    }
    return image;
} 

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
