#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

void freePaths(PathLL * p) {
	//fill in
	if (p == NULL || p->head == NULL) {return;}
	
	PathNode* second = p->head; //start at beginning of LL
	free(p); //free path LL head pointer
	PathNode* first = second->next;

	while(first != NULL) //iterate through LL until the end
	{
		freeNode(second);
		second = first; //increment second to the next pointer
		first = first->next; //increment first to the next pointer
	}

	//free the last node that caused the loop to end
	freeNode(second);	
	return;
}

PathNode * buildNode(char * path) {
	//fill in
	PathNode* new = malloc(sizeof(PathNode));
	new->path = malloc(sizeof(char)*strlen(path) + 1);
	strcpy(new->path, path);
	new->next = NULL;
	return new;	
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}

void freeNode(PathNode * p) {
	//fill in
	if(p == NULL) {return;}
	free(p->path);
	free(p);
	return;
}

bool addNode(PathLL * paths, char * path) {	
	//fill in
	if((paths == NULL)) {return false;} //make sure there is at least 1 node
	if(paths->head == NULL) //no nodes in LL
	{
		paths->head = buildNode(path);
		return true;
	}

	//initialize cursor
	PathNode** cur = &(paths->head);

	while (*cur != NULL) //go to end of LL
	{
		int compLength = strlen(path) - strlen((*cur)->path); //integer to compare path lengths
		if (strcmp((*cur)->path, path) == 0) //if paths are the same
		{
			return false;
		}
		else if (compLength < 0) //if path to be added is shorter than the currently checked path
		{
			PathNode* temp = *cur;
			*cur = buildNode(path);
			(*cur)->next = temp;
			return true;
		}
		else if (compLength == 0) //if paths are the same length
		{
			int numTurns_curpath = 0; //number of turns in current path
			int numTurns_path = 0; //number of turns in path to be added
			for(int i = 0; i < strlen(path) - 1; i++) //for first element to second-to-last element
			{
				if((*cur)->path[i] != (*cur)->path[i+1]) {numTurns_curpath++;}	
				if(path[i] != path[i+1]) {numTurns_path++;}
			}
			int compTurns = numTurns_path - numTurns_curpath; //integer to compare path turns
			if(compTurns < 0) //check if path to be added has a fewer number of turns
			{
				PathNode* temp = *cur;
				*cur = buildNode(path);
				(*cur)->next = temp;
				return true;
			}
			else if (compTurns == 0) // check if paths have the same number of turns
			{
				for (int i = 0; i < strlen(path); i++)
				{
					int compOrder = (int)path[i] - (int)(*cur)->path[i]; //integer to compare ASCII values
					if (compOrder < 0) //check if path to be added comes first alphabetically 
					{
						PathNode* temp = *cur;
						*cur = buildNode(path);
						(*cur)->next = temp;
						return true;
					}
					else if (compOrder > 0) //check if path to be added does not come first alphabetically
					{
						break;
					}
				}
			}
		}
		//update cursor
		cur = &((*cur)->next);
	}
	//path needs to be added to the end of the LL
	*cur = buildNode(path);
	return true;
}

bool removeNode(PathLL * paths, char * path) {
 	 //fill in
	if((paths == NULL) || (paths->head == NULL)) {return false;} //make sure there is at least 1 node
	PathNode** cur = &(paths->head);

	while ((*cur != NULL) && (strcmp((*cur)->path, path) != 0)) //while there is still a node to check and that node's path is not equal to the path to be found
	{
		cur = &((*cur)->next); //update cur
	}
	//need to determine the reason that the while loop exited
	if (*cur == NULL) //not path found
	{
		return false;
	}
	//path found
	PathNode* toRemove = *cur;
	*cur = toRemove->next;
	freeNode(toRemove);
	return true;
}

bool containsNode(PathLL * paths, char * path) {
	//fill in
	if((paths == NULL) || (paths->head == NULL)) {return false;} //make sure there is at least 1 node
	PathNode* cur = paths->head;

	while ((cur != NULL) && (strcmp(cur->path,path) != 0)) //while there is still a node to check and that node's path is not equal to the path to be found
	{
		cur = cur->next; //update cur
	}
	if(cur == NULL) {return false;}
	return true;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
