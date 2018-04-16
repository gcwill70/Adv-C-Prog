#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "filterParallel.h"
#include "bmp.h"

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
        BMPImage* imageIn = readImage(in);
	fclose(in);
	in = fopen(argv[1], "r");
	BMPImage* imageOut = readImage(in); //make duplicate image
	fclose(in);

        BoxFilter* filter = readFilter(filt);
        fclose(filt);

	int numThreads = 2;
        apply(imageIn, imageOut, *filter, numThreads);

        writeImage(imageOut, out);
        fclose(out);

        freeImage(imageIn);
        freeImage(imageOut);
        free(filter);

        return EXIT_SUCCESS;
}
