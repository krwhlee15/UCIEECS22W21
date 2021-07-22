#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"

// noise function
void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	srand(time(NULL));
	int total = n * WIDTH * HEIGHT / 100;
	int x, y;	

	for(int i=0; i < total; i++)
	{
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
		R[x][y] = 255;
		G[x][y] = 255;
		B[x][y] = 255;
	}	
}

// posterize function
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int i, j, k;
	
	int min = MIN_PIXEL;
	int max = MAX_PIXEL;
	
	for (k=0; k < rbits; k++)
	{
		min += (1 << k);
		max = max << 1;
	}
	for(j=0; j < HEIGHT; j++)
	{
		for(i=0; i < WIDTH; i++)
		{
			R[i][j] = R[i][j] & max;
			R[i][j] = R[i][j] | min;
		}
	}

	min = MIN_PIXEL;
	max = MAX_PIXEL;
	
	for (k=0; k < rbits; k++)
	{
		min += (1 << k);
		max = max << 1;
	}
	for(j=0; j < HEIGHT; j++)
	{
		for(i=0; i < WIDTH; i++)
		{
			G[i][j] = G[i][j] & max;
			G[i][j] = G[i][j] | min;
		}
	}

	min = MIN_PIXEL;
	max = MAX_PIXEL;
	
	for (k=0; k < rbits; k++)
	{
		min += (1 << k);
		max = max << 1;
	}
	for(j=0; j < HEIGHT; j++)
	{
		for(i=0; i < WIDTH; i++)
		{
			B[i][j] = B[i][j] & max;
			B[i][j] = B[i][j] | min;
		}
	}
}

// negative filter function
void NegativeFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	for(int j=0; j < HEIGHT;j++)
	{
		for(int i=0; i < WIDTH; i++)
		{
			R[i][j] = 255 - R[i][j];
			G[i][j] = 255 - G[i][j];
			B[i][j] = 255 - B[i][j];
		}
	}
}
