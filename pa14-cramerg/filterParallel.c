#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "filterParallel.h"

void applyThread(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int tid, int numThreads) {
	
	//FILL IN. This is the work that thread #tid should do
	//You may find it useful to know the number of threads (numThreads) to
	//figure out what to do.

	int intervalLength = (imageOut->norm_height + numThreads - 1) / numThreads;
	int lo = tid * intervalLength;
	int hi = lo + intervalLength;
	hi = (hi > imageOut->norm_height) ? imageOut->norm_height : hi;
	
	Pixel cur_pixel = {.blue = 0, .green = 0, .red = 0, .alpha = 0};
	int i_sub = 0; //row index for box filter
	int j_sub = 0; //column index for box filter
	int b = 0;
	int g = 0;
	int r = 0;
	int a = 0;

	for (int i = lo; i < hi; i++) //for each row
	{
		for (int j = 0; j < imageOut->header.width_px; j++) //for each column
		{
			b = 0;
			g = 0;
			r = 0;
			a = 0;
			for (i_sub = - 1; i_sub < 2; i_sub++) //for each row in box filter
			{
				for (j_sub = -1; j_sub < 2; j_sub++) //for each column in box filter
				{
					cur_pixel = getPixel(imageIn, i + i_sub, j + j_sub); //get pixel from box filter
					
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
		
			imageOut->pixels[i][j].blue = b;
			imageOut->pixels[i][j].green = g;
			imageOut->pixels[i][j].red = r;
			imageOut->pixels[i][j].alpha = a;
		}	
	}

	return;
}

Pixel getPixel(BMPImage* image, int row, int col)
{
	if (row < 0) {row = 0;}
	else if (row > image->norm_height - 1) {row = image->norm_height - 1;}

	if (col < 0) {col = 0;}
	else if (col > image->header.width_px - 1) {col = image->header.width_px - 1;}

	return image->pixels[row][col];
}


void * applyThreadWrapper(void * args) {
	ApplyArgs * applyArgs = (ApplyArgs *) args;
	fprintf(stdout, "calling thread %d\n", applyArgs->tid);
	
	applyThread(applyArgs->in, applyArgs->out, applyArgs->filter, applyArgs->tid, applyArgs->numThreads);
	
	fprintf(stdout, "finished with thread %d\n", applyArgs->tid);
	
	return NULL;
}

void apply(BMPImage * imageIn, BMPImage * imageOut, BoxFilter f, int numThreads) {

	//FILL IN:
	//1. create numThreads threads, that each call applyThreadWrapper
	pthread_t* threads = malloc(sizeof(pthread_t)*numThreads);
	ApplyArgs* args = malloc(sizeof(ApplyArgs)*numThreads);
	for (int i = 0; i < numThreads; i++)
	{
		args[i].in = imageIn;
		args[i].out = imageOut;
		args[i].filter = f;
		args[i].tid = i;
		args[i].numThreads = numThreads;	
	}
	for (int i = 0; i < numThreads; i++)
	{
		pthread_create(&(threads[i]), NULL, applyThreadWrapper, &(args[i]));
	}
	//2. wait for all threads to finish
	for (int i = 0; i < numThreads; i++)
	{
		pthread_join(threads[i], NULL);
	}
	//3. clean up any memory allocation you did.
	free(args);
	free(threads);
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
	}
	if (fscanf(infile, "%f", &(f->norm)) != 1)
	{
		fprintf(stderr, "Invalid filter file formatting\n");
	}
	return f;

}
