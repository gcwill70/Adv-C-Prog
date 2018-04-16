#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "path.h"

char * solveMaze(Maze * m) {
	char * retval = malloc(sizeof(char) * ((m->width * m->height) + 1));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	if (!depthFirstSolve(m, mp, retval, 0)) {
		fprintf(stderr, "No solution found!\n");
	} else {
		printf("Solution found: %s\n", retval);
	}
	
	return retval;
}

bool depthFirstSolve(Maze * m, MazePos curpos, char * path, int step) {

	//FILL IN
	//base cases
	if(curpos.xpos >= m->width || curpos.xpos < 0 || curpos.ypos >= m->height || curpos.ypos < 0) {return false;} //check if out of bounds
	if(m->maze[curpos.ypos][curpos.xpos].visited) {return false;} //check if in a visited square
	m->maze[curpos.ypos][curpos.xpos].visited = true; //square is now visited
	if(m->maze[curpos.ypos][curpos.xpos].type == WALL) {return false;} //check if at a wall
	if(curpos.xpos == (m->end).xpos && (curpos.ypos == (m->end).ypos)) //check if at the end
	{
		path[step] = '\0';
		return true;
	}

	//recursive cases
	MazePos newpos = curpos; //new potential position
	char newdir = '\0'; //new direction	
	for (int i = 0; i < 4; i++) //step in each direction
	{
		switch(i)
		{
			case 0:
				newdir = 'n';
				newpos.ypos--;
				break;
			case 1:
				newdir = 's';
				newpos.ypos++;
				break;
			case 2:
				newdir = 'e';
				newpos.xpos++;
				break;
			case 3:
				newdir = 'w';
				newpos.xpos--;
				break;
		}
		path[step] = newdir;
		if (depthFirstSolve(m, newpos, path, step + 1)) //check if part of the solution
		{
			return true;
		}
		else
		{
			newpos = curpos; //take a step back
		}
	}

	//all directions are bad
	path[step] = '\0';

	return false;
}
