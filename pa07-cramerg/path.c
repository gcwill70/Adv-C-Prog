#include <stdio.h>
#include <stdlib.h>
#include "path.h"

#ifndef READPATH_OFF
char * readPath(char * pathFilename) {

	//FILL IN
	FILE* fptr = fopen(pathFilename, "r");
	if(fptr == NULL)
	{
		return NULL;
	}
	int i = 0;
	while(fgetc(fptr) != EOF) {i++;}
	fclose(fptr);
	fptr = fopen(pathFilename, "r");
	char* path = malloc((i+1)*sizeof(char));
	i = 0;
	char c;
	while(c = fgetc(fptr), c != EOF)
	{
		path[i++] = c;
	}
	path[i] = '\0';
	fclose(fptr);
	return path;		
}
#endif //#ifndef READPATH_OFF

#ifndef CHECKPATH_OFF
bool checkPath(Maze * m, char * path) {
	
	//FILL IN
	int i = 0;
	MazePos position = m->start; //initialize current position variable
	while(path[i] != '\0')//for each input in path
	{
		switch((PathType)path[i++]) //update position
		{
			case NORTH:
				position.ypos--;
				break;
			case SOUTH:
				position.ypos++;
				break;
			case EAST:
				position.xpos++;
				break;
			case WEST:
				position.xpos--;
				break;
			default: return false;
		}
		if(position.xpos >= m->width || position.xpos < 0 || position.ypos >= m->height || position.ypos < 0) {return false;} //check if out of bounds
		if(m->maze[position.ypos][position.xpos].type == WALL) {return false;} //check if at a wall
		if(m->maze[position.ypos][position.xpos].visited) {return false;} //check if in a visited square
		m->maze[position.ypos][position.xpos].visited = true; //square is now visited
		if(position.xpos == (m->end).xpos && (position.ypos == (m->end).ypos)) {return true;}
	}
	return false;	
}
#endif //#ifndef CHECKPATH_OFF
