#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

int main (int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "Incorrect number of arguments.\n");
		fprintf(stderr, "Usage: ./pa11 <input file>\n");		
		return EXIT_FAILURE;
	}

	float result; //store the result of your calculation here.
	
	/* Insert code here to perform the RPN calculation.
	Don't forget to free any memory you allocate once you're done with it! */

	FILE* fptr = fopen(argv[1], "r");
	if (fptr == NULL) {
		printf("Failed to open file.\n");
		return EXIT_FAILURE;
	}
	
	Stack *s = malloc(sizeof(Stack));
	s->top = NULL;
	
	char curr_op = '\0';
	float op1 = 0;
	float op2 = 0;
	fpos_t* filepos = malloc(sizeof(fpos_t)); //stores current file position

	while(!feof(fptr))
	{
		fgetpos(fptr, filepos); //get current place in file
		if (fscanf(fptr, "%f", &op1) == 1) { //try to read a number
			push(s, op1); //long float?
		}
		else //should be operator or space
		{
			fsetpos(fptr, filepos); //go back to where we were in the file before trying to read in a float	
			if (fscanf(fptr, "%c", &curr_op) == 1) { //try to read operand
				if (curr_op != 32 && curr_op != 10) { //if we aren't at a space, we should be at an operator
					if (twoNodes(s)) {
						if (curr_op == 42) { //multiply
							op1 = pop(s);
							op2 = pop(s);	
							push(s, op2 * op1);
						}
						else if (curr_op == 43) { //add
							op1 = pop(s);
							op2 = pop(s);	
							push(s, op2 + op1);
						}
						else if (curr_op == 45) { //subtract
							op1 = pop(s);
							op2 = pop(s);	
							push(s, op2 - op1);
						}
						else if (curr_op == 47) { //divide
							op1 = pop(s);
							op2 = pop(s);	
							push(s, op2 / op1);
						}
						else { //invalid character
							printf("Invalid character: '%c'. Must be operator ('+', '-', '*', '/') or space.\n", curr_op);
							freeStack(s);
							fclose(fptr);
							free(filepos);
							return EXIT_FAILURE;
						}
					}
					else {
						printf("Invalid file format.\n");
						freeStack(s);
						fclose(fptr);
						free(filepos);
						return EXIT_FAILURE;
					}
				}
			}
		}
	}
	if (s->top == NULL) {
		free(s);
		fclose(fptr);
		free(filepos);
		return EXIT_FAILURE;
	}
	else if (s->top->next != NULL) {
		freeStack(s);
		fclose(fptr);
		free(filepos);
		return EXIT_FAILURE;
	}
	else {
		result = s->top->val;
		free(s->top);
	}
	free(s);
	fclose(fptr);
	free(filepos);
	printf("%f\n", result);
	
	return EXIT_SUCCESS;
}
