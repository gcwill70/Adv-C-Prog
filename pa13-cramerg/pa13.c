#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filter.h"

int main(int argc, char ** argv) {
	if (argc != 4)
	{
		fprintf(stderr, "Invalid command line args\n");
		return EXIT_FAILURE;
  	}

	FILE* in = fopen(argv[1], "r");
	FILE* filt = fopen(argv[2], "r");
	FILE* out = fopen(argv[3], "w");

	if (!in || !filt || !out) {
		fprintf(stderr, "Couldn't open files.\n");
	}
	BMPImage* image = readImage(in);
	fclose(in);
	
	BoxFilter* filter = readFilter(filt);
	fclose(filt);

	BMPImage* filtImage = apply(image, *filter);

	writeImage(filtImage,out);
	fclose(out);

	freeImage(image);
	freeImage(filtImage);
	free(filter);

	return EXIT_SUCCESS;
}
