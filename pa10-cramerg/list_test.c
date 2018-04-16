#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#define PATH_LENGTH 6

int main(int argc, char ** argv)
{
	if (argc != 2) {
		fprintf(stderr, "Wrong number of command line args\n");
		return EXIT_FAILURE;
	}

	FILE* fptr = fopen(argv[1], "w");
	if (fptr == NULL) {return EXIT_FAILURE;}

	PathLL* list = buildPaths();
	char* paths[PATH_LENGTH] = {"ewe", "eww", "n", "e", "ww", "nw"};
	for (int i = 0; i < PATH_LENGTH; i++) //test addNode
	{
		if(!addNode(list, paths[i]))
		{
			printf("Failed to add paths[%d] = %s\n", i, paths[i]);
		}
	}
	addNode(list, paths[0]); //try to add the same path twice
	printPaths(list,fptr);
	for (int i = 0; i < PATH_LENGTH; i++) //test conatinsNode
	{
		if(!containsNode(list,paths[i]))
		{
			printf("Failed to detect paths[%d] = %s\n", i, paths[i]);
		}	
	}
	removeNode(list,"eeee"); //try to remove nonexistent node
	for (int i = 0; i < PATH_LENGTH; i++) //test removeNode
	{
		if(!removeNode(list, paths[i]))
		{
			printf("Failed to remove paths[%d] = %s\n", i, paths[i]);
		}
	}
	freePaths(list);
	return 0;
}
