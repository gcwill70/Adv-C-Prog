#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

#ifndef READIMAGE_OFF
BMPImage * readImage(FILE * fp)
{
	// FILL IN
	if (fp == NULL)
	{
		fclose(fp);
		exit(1);
	}
	BMPImage* image = malloc(sizeof(BMPImage));
	fread(&(image->header), sizeof(image->header), 1, fp);
	
	int n_height = abs(image->header.height_px);
	image->pixels = malloc((n_height)*sizeof(Pixel*)); //allocate the number of rows
	for (int i = 0; i < n_height; i++) //for each row
	{
		image->pixels[i] = malloc((image->header.width_px)*sizeof(Pixel)); //allocate the columns in the row
		for (int j = 0; j < image->header.width_px; j++) //for each column
        	{
            		fread(&(image->pixels[i][j].blue), sizeof(uint8_t), 1, fp);
           		fread(&(image->pixels[i][j].green), sizeof(uint8_t), 1, fp);
          	 	fread(&(image->pixels[i][j].red), sizeof(uint8_t), 1, fp);
			fread(&(image->pixels[i][j].alpha), sizeof(uint8_t), 1, fp);
		}
	}

	image->norm_height = n_height;
	return image;
}

void freeImage(BMPImage * image)
{
	// FILL IN
	for (int i = 0; i < image->norm_height; i++) //for each row
	{
		free(image->pixels[i]);
	}
	free(image->pixels);
	free(image);
}
#endif

#ifndef WRITEIMAGE_OFF
void writeImage(BMPImage * image, FILE * fp)
{
	// FILL IN
	fwrite(&(image->header), sizeof(image->header), 1, fp);
	for (int i = 0; i < image->norm_height; i++)
	{
		for (int j = 0; j < image->header.width_px; j++)
		{
			fwrite(&(image->pixels[i][j].blue), sizeof(uint8_t), 1, fp);
			fwrite(&(image->pixels[i][j].green), sizeof(uint8_t), 1, fp);
			fwrite(&(image->pixels[i][j].red), sizeof(uint8_t), 1, fp);
			fwrite(&(image->pixels[i][j].alpha), sizeof(uint8_t), 1, fp);
		}
	}
}
#endif
