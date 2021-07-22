#include <stdio.h>
#include <stdlib.h>

#include "Image.h"
#include "Constants.h"

/* Get the R intensity of pixel (x, y) in image */
unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image -> R[x + y *(image -> W)];
}

/* Get the G intensity of pixel (x, y) in image */
unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image -> G[x + y *(image -> W)];
}

/* Get the B intensity of pixel (x, y) in image */
unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
	return image -> B[x + y *(image -> W)];
}

/* Set the R intensity of pixel (x, y) in image to r */
void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r)
{
	image -> R[x + y *(image -> W)] = r;
}

/* Set the G intensity of pixel (x, y) in image to g */
void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g)
{
	image -> G[x + y *(image -> W)] = g;
}

/* Set the B intensity of pixel (x, y) in image to b */
void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b)
{
	image -> B[x + y *(image -> W)] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
	IMAGE *image;
	image = malloc(sizeof(IMAGE));
	image -> H = Height;
	image -> W = Width;
	image -> R = malloc(Width * Height * sizeof(unsigned char));
	image -> G = malloc(Width * Height * sizeof(unsigned char));
	image -> B = malloc(Width * Height * sizeof(unsigned char));

	return image;
}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image)
{
	free(image -> R);
	free(image -> G);
	free(image -> B);
	free(image);
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image)
{
	return image -> W;
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image)
{
	return image -> H;
}
