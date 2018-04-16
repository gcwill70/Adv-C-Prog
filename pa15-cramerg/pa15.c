#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "huffman.h"
#include "linkedlist.h"
#include "tree.h"

/* count the occurrences in a file */

long *countLetters(FILE *fp)
{
   long *asciiCount = (long *)malloc(sizeof(long)*ASCII_SIZE);
   if (asciiCount == NULL) {
      return NULL;
   }
   int ch;
   for (ch = 0; ch < ASCII_SIZE; ch++) {
      asciiCount[ch] = 0;
   }
   fseek(fp, 0, SEEK_SET);
   while ((ch = fgetc(fp)) != EOF) {
      asciiCount[ch] += 1;
   }
   return asciiCount;
}

int main(int argc, char **argv)
{
   if (argc != 5) {
    printf("Sent %d arguments but expected 4.", argc);
    return EXIT_FAILURE;
   }
   FILE * inFile = fopen(argv[1], "r");
   if (inFile == NULL) {
      fprintf(stderr, "can't open the input file.  Quit.\n");
      return EXIT_FAILURE;
   }

   /* read and count the occurrences of characters */
   long *asciiCount = countLetters(inFile);
   fclose(inFile);

   if (asciiCount == NULL) {
      fprintf(stderr, "cannot allocate memory to count the characters in input file.  Quit.\n");  return EXIT_FAILURE;
      return EXIT_FAILURE;
   }
 
   // Your code should go here
	ListNode* head = sortLL(asciiCount);
	sorted(head, argv[2]);
	makeTree(&head);
	FILE* huff = fopen(argv[3], "w");
	if (huff == NULL) {
		printf("can't open huffman file.\n");
		exit(1);
	}
	huffman(head->ptr, huff, 0, 0);
	fclose(huff);
	FILE* headerfile = fopen(argv[4], "w");
	if (headerfile == NULL) {
		printf("can't open headerfile file.\n");
		exit(1);
	}
	unsigned char whichBit = 0;
	unsigned char currentByte = 0;;
	header(head->ptr, headerfile, &whichBit, &currentByte);
	padZero(headerfile, &whichBit, &currentByte);
	fclose(headerfile);
	freeTree(head->ptr);
	free(head);
	free(asciiCount);
	return EXIT_SUCCESS;
}
