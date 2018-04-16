#include <stdlib.h>
#include <stdio.h>
#include "huffman.h"

void makeTree(ListNode** head);
void freeTree(TreeNode* tn);
void huffman(TreeNode* tn, FILE* f, int count, int code);
int writeBit(FILE * fptr, unsigned char bit, 
	     unsigned char * whichbit, 
	     unsigned char * curbyte);
int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte);
int padZero(FILE * fptr, unsigned char * whichbit, 
	    unsigned char * curbyte);
void header(TreeNode* tn, FILE*f, unsigned char* whichBit, unsigned char* currentByte);
