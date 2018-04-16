#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filter.h"

#ifndef BLUR_OFF
BMPImage * blur(BMPImage * image) {
	//FILL IN	
	BMPImage* blurImage = malloc(sizeof(BMPImage));
	blurImage->header = image->header;
	memcpy(&blurImage->header, &image->header, sizeof(BMPHeader));
	memcpy(&blurImage->norm_height, &image->norm_height, sizeof(int));
	blurImage->pixels = malloc(blurImage->norm_height*sizeof(Pixel*));
	
	Pixel cur_pixel = {.blue = 0, .green = 0, .red = 0, .alpha = 0};
	int i_sub = 0; //row index for box filter
	int j_sub = 0; //column index for box filter
	int blue = 0;
	int green = 0;
	int red = 0;
	int alpha = 0;

	for (int i = 0; i < blurImage->norm_height; i++) //for each row
	{
		blurImage->pixels[i] = malloc(sizeof(Pixel)*blurImage->norm_height);
		for (int j = 0; j < blurImage->header.width_px; j++) //for each column
		{
			blue = 0;
			green = 0;
			red = 0;
			alpha = 0;
			for (i_sub = - 1; i_sub < 2; i_sub++) //for each row in box filter
			{
				for (j_sub = -1; j_sub < 2; j_sub++) //for each column in box filter
				{
					cur_pixel = getPixel(image, i + i_sub, j + j_sub); //get pixel from box filter
					
					//Accumulate each color values
					blue += cur_pixel.blue;
					green += cur_pixel.green;
					red += cur_pixel.red;
					alpha += cur_pixel.alpha;
				}
			}
			blurImage->pixels[i][j].blue = blue/9;
			blurImage->pixels[i][j].green = green/9;
			blurImage->pixels[i][j].red = red/9;
			blurImage->pixels[i][j].alpha = alpha/9;		
		}	
	}
	
	return blurImage;
}
#endif

Pixel getPixel(BMPImage* image, int row, int col)
{
	if (row < 0) {row = 0;}
	else if (row > image->norm_height - 1) {row = image->norm_height - 1;}

	if (col < 0) {col = 0;}
	else if (col > image->header.width_px - 1) {col = image->header.width_px - 1;}

	return image->pixels[row][col];
}

// EXTRA CREDIT START
BMPImage * apply(BMPImage * image, BoxFilter f) {
	//FILL IN
	BMPImage* filtImage = malloc(sizeof(BMPImage));
	filtImage->header = image->header;
	memcpy(&filtImage->header, &image->header, sizeof(BMPHeader));
	memcpy(&filtImage->norm_height, &image->norm_height, sizeof(int));
	filtImage->pixels = malloc(filtImage->norm_height*sizeof(Pixel*));
	
	Pixel cur_pixel = {.blue = 0, .green = 0, .red = 0, .alpha = 0};
	int i_sub = 0; //row index for box filter
	int j_sub = 0; //column index for box filter
	int b = 0;
	int g = 0;
	int r = 0;
	int a = 0;

	for (int i = 0; i < filtImage->norm_height; i++) //for each row
	{
		filtImage->pixels[i] = malloc(sizeof(Pixel)*filtImage->norm_height);
		for (int j = 0; j < filtImage->header.width_px; j++) //for each column
		{
			b = 0;
			g = 0;
			r = 0;
			a = 0;
			for (i_sub = - 1; i_sub < 2; i_sub++) //for each row in box filter
			{
				for (j_sub = -1; j_sub < 2; j_sub++) //for each column in box filter
				{
					cur_pixel = getPixel(image, i + i_sub, j + j_sub); //get pixel from box filter
					
					//Accumulate each color value
					b += cur_pixel.blue*(f.filter[i_sub+1][j_sub+1]);
					g += cur_pixel.green*(f.filter[i_sub+1][j_sub+1]);
					r += cur_pixel.red*(f.filter[i_sub+1][j_sub+1]);
					a += cur_pixel.alpha*(f.filter[i_sub+1][j_sub+1]);
				}
			}
			b = b/f.norm;
			g = g/f.norm;
			r = r/f.norm;
			a = a/f.norm;
			
			if (b < 0) {b = 0;}
			else if (b > 255) {b = 255;}
		
			if (g < 0) {g = 0;}
			else if (g > 255) {g = 255;}
	
			if (r < 0) {r = 0;}
			else if (r > 255) {r = 255;}
			
			if (a < 0) {a = 0;}
			else if (a > 255) {a = 255;}
		
			filtImage->pixels[i][j].blue = b;
			filtImage->pixels[i][j].green = g;
			filtImage->pixels[i][j].red = r;
			filtImage->pixels[i][j].alpha = a;
		}	
	}
	
	return filtImage;
}

BoxFilter * readFilter(FILE * infile) {
	//FILL IN
	BoxFilter* f = malloc(sizeof(BoxFilter));
	for (int i = 0; i < 3; i++) //for each row
	{
		if (fscanf(infile, "%d ", &(f->filter[i][0])) != 1) //read in a coefficient
		{
			fprintf(stderr, "Invalid filter file formatting\n");
		
		}
		if (fscanf(infile, "%d ", &(f->filter[i][1])) != 1) //read in a coefficient
		{
			fprintf(stderr, "Invalid filter file formatting\n");
		}
		if (fscanf(infile, "%d", &(f->filter[i][2])) != 1) //read in a coefficient
		{
			fprintf(stderr, "Invalid filter file formatting\n");
		}
		/*if (fscanf(infile, "\n") != 1) //read new line character
		{	
			fprintf(stderr, "Invalid filter file formatting\n");
		}*/
	}
	if (fscanf(infile, "%f", &(f->norm)) != 1)
	{
		fprintf(stderr, "Invalid filter file formatting\n");
	}
	return f;

}
// EXTRA CREDIT END
