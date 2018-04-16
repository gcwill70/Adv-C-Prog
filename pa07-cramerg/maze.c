#include <stdlib.h>
#include <stdio.h>
#include "maze.h"

#ifndef READMAZE_OFF
Maze * readMaze(char * mazeFilename) {

	//FILL IN
	FILE* fptr = fopen(mazeFilename ,"r");
	if (fptr == NULL)
	{
		return NULL;
	}
	Maze* temp = malloc(sizeof(Maze));
	if (fscanf(fptr, "%d %d\n", &(temp->height), &(temp->width)) != 2)
	{
		free(temp);
		fclose(fptr);
	}; //read in array size
	temp->maze = malloc((temp->height)*sizeof(MazeSquare*));
	for(int i = 0; i < temp->height; i++) //for each row
	{
		(temp->maze)[i] = malloc(temp->width*sizeof(MazeSquare)); //allocate the columns in the row
		for(int j = 0; j < temp->width; j++) //for each column
		{
			temp->maze[i][j].type = (SquareType)fgetc(fptr);
			temp->maze[i][j].visited = false;
			switch(temp->maze[i][j].type)
			{
				case START:
					(temp->start).xpos = j;
					(temp->start).ypos = i;
				break;
				case END:
					(temp->end).xpos = j;
					(temp->end).ypos = i;
				break;
				case WALL:
				case SPACE:
				break;
				default: 
					freeMaze(temp);
					fclose(fptr);
					return NULL;
				break;
			}
		}
		if(fgetc(fptr) != '\n') //new line character
		{ printf("error\n");}
	}
	fclose(fptr);

	return temp;
}
#endif //#ifndef READMAZE_OFF

#ifndef FREEMAZE_OFF
void freeMaze(Maze * m) {
	//1. Free each of the "rows" of the maze
	for(int i = 0; i < m->height; i++)
	{
		free(m->maze[i]);
	}	
	//2. Free the "spine" of the array
	free(m->maze);	
}
#endif //#ifndef FREEMAZE_OFF
