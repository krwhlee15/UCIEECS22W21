/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2020                 */
/* 								                                     */
/* modifications: 						                             */
/* 01/13/21     QV  Adjusted for W21                                 */
/* 01/11/20 	WL	adjusted for W20			                     */
/* 10/1/18  	MC  adjusted for F18			                     */
/* 09/27/17 	RD	adjusted for lecture usage		                 */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 * ***************************************************************** *
 * First Name:	Wonhee	
 * Last Name:	Lee
 * UCInetID:	wonheel1	
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** global definitions ***/

#define WIDTH  600		/* image width */
#define HEIGHT 400		/* image height */
#define SLEN    64		/* maximum length of file names */

// added new defines for edge detection filter
// you can use these or not (not necessary, but we used it for convenience)
#define MAX_PIXEL 255	/* max pixel value */
#define MIN_PIXEL 0		/* min pixel value */

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* read image from a file */
/* written for you; should not been modified */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
/* written for you; should not been modified */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* aging the photo */
/* sample function to get you started */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* detect edges in a picture (black background with white edges) */
void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* Keeps pixel values in bound */
void Adjust(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int SR, int SG, int SB, int x, int y);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
    /* Two dimensional arrays to hold the current image data, */
    /* one array for each color component.                    */
    unsigned char   R[WIDTH][HEIGHT];
    unsigned char   G[WIDTH][HEIGHT];
    unsigned char   B[WIDTH][HEIGHT];
	int choice = 0;
	char fname[SLEN];

	while(1)
	{
		PrintMenu();
		scanf("%d", &choice);
		
		if(choice == 99)
		{
			break;
		}
		switch(choice)
		{
			case 1:
			{	
				printf("Please input the file name to laod: ");
				scanf("%79s", fname);
				LoadImage(fname, R, G, B);
				break;		
			}	
			case 2:
			{
				printf("Please input the file name to save: ");
				scanf("%79s", fname);
				SaveImage(fname, R, G, B);
				break;
			}
			case 3:
			{
				Aging(R, G, B);
				printf("\"Aging\" operation is done!");	
				break;
			}
			case 4:
			{
				EdgeDetection(R, G, B);
				printf("\"Edge Detection\" operation is done!");	
				break;
			}
			case 5:
			{
				Sharpen(R, G, B);
				printf("\"Sharpen\" operation is done!\n");
				break;
			}
			case 22:
			{
				AutoTest(R, G, B);
			}
		}
	}

    return 0;
}

/* takes in a file name without extension */
/* writes file into R, G, B arrays */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char Type[SLEN];
    int  Width, Height, MaxValue;
    int  x, y;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "r");
    if (!File) {
        printf("\nCannot open file \"%s\" for reading!\n", fname);
        return 1;
    }
    fscanf(File, "%79s", Type);
    if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
        printf("\nUnsupported file format!\n");
        return 2;
    }
    fscanf(File, "%d", &Width);
    if (Width != WIDTH) {
        printf("\nUnsupported image width %d!\n", Width);
        return 3;
    }
    fscanf(File, "%d", &Height);
    if (Height != HEIGHT) {
        printf("\nUnsupported image height %d!\n", Height);
        return 4;
    }
    fscanf(File, "%d", &MaxValue);
    if (MaxValue != 255) {
        printf("\nUnsupported image maximum value %d!\n", MaxValue);
        return 5;
    }
    if ('\n' != fgetc(File)) {
        printf("\nCarriage return expected!\n");
        return 6;
    }
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            R[x][y] = fgetc(File);
            G[x][y] = fgetc(File);
            B[x][y] = fgetc(File);
        }
    }
    if (ferror(File)) {
        printf("\nFile error while reading from file!\n");
        return 7;
    }
    printf("%s was read successfully!\n", fname_ext);
    fclose(File);
    return 0;
}

/* takes R, G, B arrays and writes it in a file */
/* filename (fname) has no extension */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    FILE *File;
    char ftype[] = ".ppm";
    char fname_ext[SLEN + sizeof(ftype)];
    char SysCmd[SLEN * 5];
    int  x, y;

    strcpy(fname_ext, fname);
    strcat(fname_ext, ftype);

    File = fopen(fname_ext, "w");
    if (!File) {
        printf("\nCannot open file \"%s\" for writing!\n", fname);
        return 1;
    }
    fprintf(File, "P6\n");
    fprintf(File, "%d %d\n", WIDTH, HEIGHT);
    fprintf(File, "255\n");

    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            fputc(R[x][y], File);
            fputc(G[x][y], File);
            fputc(B[x][y], File);
        }
    }

    if (ferror(File)) {
        printf("\nFile error while writing to file!\n");
        return 2;
    }
    fclose(File);
    printf("%s was saved successfully. \n", fname_ext);

    /*
     * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
     * and make it world readable
     */
    sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
    if (system(SysCmd) != 0) {
        printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
        return 3;
    }
    printf("%s.jpg was stored for viewing. \n", fname);

    return 0;
}


/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{

    LoadImage("lambo", R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
    printf("Aging tested!\n\n");
   
	LoadImage("lambo", R, G, B);
    EdgeDetection(R, G, B);
    SaveImage("edge", R, G, B);
    printf("Edge Detection tested!\n\n");
 
  	LoadImage("lambo", R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
    printf("Sharpen tested!\n\n");
}

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
    int x, y;

    for( y = 0; y < HEIGHT; y++ ) {
        for( x = 0; x < WIDTH; x++ ) {
	    B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
            R[x][y] = (unsigned char) (B[x][y]*1.6);
            G[x][y] = (unsigned char) (B[x][y]*1.6);
	    }
    }
}

void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{   
	int x, y = 0;
	int SR, SG, SB = 0;
	unsigned char R2[WIDTH][HEIGHT], G2[WIDTH][HEIGHT], B2[WIDTH][HEIGHT];

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R2[x][y] = R[x][y];
			G2[x][y] = G[x][y];
			B2[x][y] = B[x][y];
		}
	}

	for(y = 1; y < HEIGHT - 1; y++)
	{
		for(x = 1; x < WIDTH - 1; x++)
		{
			if(x == 0 || y == 0 || x == WIDTH - 1 || y == HEIGHT - 1)
			{
				SR = 0;
				SG = 0;	
				SB = 0;
			}
			else
			{
				SR = 8*R2[x][y] - (R2[x-1][y-1] + R2[x][y-1] + R2[x+1][y-1] + R2[x-1][y] + R2[x+1][y] + R2[x-1][y+1] + R2[x][y+1] + R2[x+1][y+1]);
				SG = 8*G2[x][y] - (G2[x-1][y-1] + G2[x][y-1] + G2[x+1][y-1] + G2[x-1][y] + G2[x+1][y] + G2[x-1][y+1] + G2[x][y+1] + G2[x+1][y+1]);
				SB = 8*B2[x][y] - (B2[x-1][y-1] + B2[x][y-1] + B2[x+1][y-1] + B2[x-1][y] + B2[x+1][y] + B2[x-1][y+1] + B2[x][y+1] + B2[x+1][y+1]);
			}
			Adjust(R, G, B, SR, SG, SB, x, y);
		}
	}
} 

void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x, y = 0;
	int SR, SG, SB = 0;
	unsigned char R2[WIDTH][HEIGHT], G2[WIDTH][HEIGHT], B2[WIDTH][HEIGHT];

	for(y = 0; y < HEIGHT; y++)
	{
		for(x = 0; x < WIDTH; x++)
		{
			R2[x][y] = R[x][y];
			G2[x][y] = G[x][y];
			B2[x][y] = B[x][y];
		}
	}

	for(y = 1; y < HEIGHT - 1; y++)
	{
		for(x = 1; x < WIDTH - 1; x++)
		{
			SR = 9*R2[x][y] - R2[x-1][y-1] - R2[x][y-1] - R2[x+1][y-1] - R2[x-1][y] - R2[x+1][y] - R2[x-1][y+1] - R2[x][y+1] - R2[x+1][y+1];
			SG = 9*G2[x][y] - G2[x-1][y-1] - G2[x][y-1] - G2[x+1][y-1] - G2[x-1][y] - G2[x+1][y] - G2[x-1][y+1] - G2[x][y+1] - G2[x+1][y+1];
			SB = 9*B2[x][y] - B2[x-1][y-1] - B2[x][y-1] - B2[x+1][y-1] - B2[x-1][y] - B2[x+1][y] - B2[x-1][y+1] - B2[x][y+1] - B2[x+1][y+1];
			Adjust(R, G, B, SR, SG, SB, x, y);
		}
	}
}

/* Keeps pixel values in bound */
void Adjust(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], int SR, int SG, int SB, int x, int y)
{
	if(SR <= MAX_PIXEL && SR >= MIN_PIXEL)
	{
		R[x][y] = SR;
	}
	if(SG <= MAX_PIXEL && SG >= MIN_PIXEL)
	{
		G[x][y] = SG;
	}
	if(SB <= MAX_PIXEL && SB >= MIN_PIXEL)
	{
		B[x][y] = SB;
	}
	if(SR < MIN_PIXEL)
	{
		R[x][y] = MIN_PIXEL;
	}
	if(SG < MIN_PIXEL)
	{
		G[x][y] = MIN_PIXEL;
	}
	if(SB < MIN_PIXEL)
	{
		B[x][y] = MIN_PIXEL;
	}
	if(SR > MAX_PIXEL)
	{
		SR = MAX_PIXEL;
	}
	if(SG > MAX_PIXEL)
	{
		SG = MAX_PIXEL;
	}
	if(SB > MAX_PIXEL)
	{
		SB = MAX_PIXEL;
	}
}

void PrintMenu(void)
{
	printf("Welcome to Photo Lab 2021 - v1!\n");
	printf("----------------------------------------------\n");
	printf(" 1: Load PPM image\n");
	printf(" 2: Save image in PPM and JPEG format\n");
	printf(" 3: Run aging filter\n");
	printf(" 4: Run edge detection filter\n");
	printf(" 5: Run sharpen filter\n");
	printf("22: Test all functions\n");
	printf("99: Exit\n");
	printf("---------------------------------------------\n");
	printf("Please make your choice: ");
}

/* MORE COMING SOON */

/* EOF */
