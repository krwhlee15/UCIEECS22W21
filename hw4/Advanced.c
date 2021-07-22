#include "Advanced.h"
#include "Constants.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n)
{
	int x, y, i;
	int num; /* number of noise added */
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);

	num = ( n*HEIGHT*WIDTH )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(WIDTH-1);
		y = ( (double)rand()/RAND_MAX )*(HEIGHT-1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int x, y;
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);

	for(x=0; x<WIDTH; x++) {
		for(y=0; y<HEIGHT; y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				SetPixelR(image, x, y,(GetPixelR(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image, x, y, (GetPixelR(image, x, y) & one));

			one = 1;
			for(i=0; i<gbits-1; i++) {
				SetPixelG(image, x, y, (GetPixelG(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image, x, y, (GetPixelG(image, x, y) & one));

			one = 1;
			for(i=0; i<bbits-1; i++) {
				SetPixelB(image, x, y, (GetPixelR(image, x, y) | one));
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image, x, y, (GetPixelR(image, x, y) & one));
		}
	}
	return image;
}

// Negative Filter
IMAGE *NegativeFilter(IMAGE *image)
{
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
			SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
			SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
		}
	}
	return image;
}

// Crops the image
IMAGE *Square(IMAGE *image, int x, int y, int L)
{
	int i, j;
	
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	unsigned char R_temp[WIDTH][HEIGHT];
	unsigned char G_temp[WIDTH][HEIGHT];
	unsigned char B_temp[WIDTH][HEIGHT];
	
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < HEIGHT; j++)
		{
			R_temp[i][j] = GetPixelR(image, i, j);
			G_temp[i][j] = GetPixelG(image, i, j);
			B_temp[i][j] = GetPixelB(image, i, j);
		}
	}
	
	image -> W = L;
	image -> H = L;
	WIDTH = L;
	HEIGHT = L;
	
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < L; j++)
		{
			SetPixelR(image, i, j, R_temp[x+i][y+j]);
			SetPixelG(image, i, j, G_temp[x+i][y+j]);
			SetPixelB(image, i, j, B_temp[x+i][y+j]);
		}
	}
	
	return image;
}

// Enlarges the image
IMAGE *Enlarge(IMAGE *image, int percentage)
{

    int x, y;
    int scale = percentage/100;
    int HEIGHT = image->H;
    int WIDTH = image->W;
    unsigned char R_temp[WIDTH][HEIGHT];
    unsigned char G_temp[WIDTH][HEIGHT];
    unsigned char B_temp[WIDTH][HEIGHT];
    for (x = 0; x < WIDTH; x++)
    {   for(y = 0; y < HEIGHT; y++)
        {   R_temp[x][y] = image->R[x+y*WIDTH];
            G_temp[x][y] = image->G[x+y*WIDTH];
            B_temp[x][y] = image->B[x+y*WIDTH];
        }
    }
    for (x = 0; x < WIDTH*scale; x++)
    {   for(y = 0; y < HEIGHT*scale; y++)
        {   image->R[x+y*WIDTH*scale] = R_temp[x/scale][y/scale];
            image->G[x+y*WIDTH*scale] = G_temp[x/scale][y/scale];
            image->B[x+y*WIDTH*scale] = B_temp[x/scale][y/scale];
        }
    }
    return image;
}

// Adjusts the brightness and contrast
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast)
{
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	
	double factor = (double)(259 * (contrast + 255)) / (double)(255 * (259 - contrast));

	unsigned char R_temp[WIDTH][HEIGHT];
	unsigned char G_temp[WIDTH][HEIGHT];
	unsigned char B_temp[WIDTH][HEIGHT];

	int tmpr = 0, tmpg = 0, tmpb = 0;

	int x, y;
	
	for(x = 0; x < WIDTH; x++)
	{
		for(y = 0; y < HEIGHT; y++)
		{
			R_temp[x][y] = GetPixelR(image, x, y);
			G_temp[x][y] = GetPixelG(image, x, y);
			B_temp[x][y] = GetPixelB(image, x, y);
		}
	}

	for(x = 1; x < WIDTH - 1; x++)
	{
		for(y = 1; y < HEIGHT - 1; y++)
		{
			tmpr = brightness + GetPixelR(image, x, y);
			tmpg = brightness + GetPixelG(image, x, y);
			tmpb = brightness + GetPixelB(image, x, y);
			R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
			G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
			B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
			tmpr = tmpg = tmpb = 0;
		}
	}


	for(int x = 1; x < WIDTH - 1; x++)
	{
		for(int y = 1; y < HEIGHT - 1; y++)
		{
			tmpr = R_temp[x][y];
			tmpr = (int)(factor * (tmpr - 128) + 128);
			tmpg = G_temp[x][y];
			tmpg = (int)(factor * (tmpg - 128) + 128);
			tmpb = B_temp[x][y];
			tmpb = (int)(factor * (tmpb - 128) + 128);
			R_temp[x][y] = (tmpr > 255)?255:(tmpr < 0)?0:tmpr;
			G_temp[x][y] = (tmpg > 255)?255:(tmpg < 0)?0:tmpg;
			B_temp[x][y] = (tmpb > 255)?255:(tmpb < 0)?0:tmpb;
		}
	}

	for(x = 0; x < WIDTH; x++)
	{
		for(y = 0; y < HEIGHT; y++)
		{
			SetPixelR(image, x, y, R_temp[x][y]);
			SetPixelG(image, x, y, G_temp[x][y]);
			SetPixelB(image, x, y, B_temp[x][y]);
		}
	}	

	return image;
}


