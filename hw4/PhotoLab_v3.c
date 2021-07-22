/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22                   */
/*                                                                   */
/* This is an "A" level representation of PhotoLab v1.               */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution (and all associated files) is for your reference    */
/* for this course and is copyright belongs to the authors below.    */
/* Reproduction or sharing of this code outside of this class is     */
/* prohibited except with the express written consent of the authors.*/
/*                                                                   */
/* Author: Mina Moghadam, Ned Beigipar, QV Dang,   Wonhee Lee        */
/* Date:   11/8/2017	  08/17/2020    02/02/2021 03-05-2021        */
/*                                                                   */
/* Comments:                                                         */
/* added info about negative filter                                  */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{

#ifdef DEBUG
    AutoTest();
#else
    int rc;
    IMAGE *image = NULL;

    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    rc = 1;
    PrintMenu();
    scanf("%d", &option);

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* Square() parameter */    
    int x, y, L;

    /* Enlarge() parameter */
    int percentage;

    /* BrightnessandContrast() parameter */
    int brightness, contrast;

    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            image = LoadImage(fname);
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 11) {
            if (rc != SUCCESS || !image) {
                printf("No image to process!\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, image);
                        break;
                    case 3:
                        image = Aging(image);
                        printf("\"Aging\" operation is done!\n");
                        break;
                    case 4:
                        image = Edge(image);
                        printf("\"Edge Detection\" operation is done!\n");
                        break;
                    case 5:
                        image = Sharpen(image);
                        printf("\"Sharpen\" operation is done!\n");
			break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        image = Noise(image, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        image = Posterize(image, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        image = NegativeFilter(image);
                        printf("\"Negative Filter\" operation is done!\n");
                        break;
		    case 9:
			printf("Please input the enlarging percentage (integer between 100 - 200): ");
			scanf("%d", &percentage);
			while(percentage < 100)
			{
				printf("Warning: unproper input. Please input a proper integer in bound.");
				scanf("%d", &percentage);
			}
			image = Enlarge(image, percentage);
			printf("\"Enlarge the image\" operation is done!\n");
			break;
		    case 10:
			printf("Please enter the X offset value: ");
			scanf("%d", &x);
			printf("Please enter the Y offset value: ");
			scanf("%d", &y);
			printf("Please input the maximum cropped sqaure size: ");
			scanf("%d", &L);
			image = Square(image, x, y, L);
			printf("\"Square\" operation is done!\n");
			break;
		    case 11:
			printf("Please input the brightness level (integer between -255 - 255): ");
			scanf("%d", &brightness);
			printf("Please input the contrast level (integer between -255 - 255): ");
			scanf("%d", &contrast);
			image = BrightnessandContrast(image, brightness, contrast);
			printf("\"Brightness and Contrast Adjustment\" operation is done!\n");
			break;
		    default:
                        break;

                }
            }
        }

        else if (option == 22) {
            AutoTest();
            rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("Exiting program.\n");
#endif
    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save image in PPM and JPEG format\n");
    printf(" 3: Run aging\n");
    printf(" 4: Run edge detection filter\n");
    printf(" 5: Run sharpen filter\n");
    printf(" 6: Run noise filter\n");
    printf(" 7: Run posterize filter\n");
    printf(" 8: Run negative filter\n");
    printf(" 9: Enlarge image\n");
    printf("10: Create square (crop) image\n");
    printf("11: Adjust brightness and contrast\n");
    printf("22: Test all functions\n");
    printf("99: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
