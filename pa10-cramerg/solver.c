#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
	
  	//Fill in. (Your best bet is to modify a working implementation from PA08)
	//base cases
	if(!inBounds(curpos, m)) {return;}
	if(isVisited(curpos, m)) {return;}
	if(hitWall(curpos, m)) {return;}
	if(atEnd(curpos, m))
	{
		path[step] = '\0';
		addNode(successPaths, path);
		return;
	}
	m->maze[curpos.ypos][curpos.xpos].visited = true; //square is now visited

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
		depthFirstSolve(m, newpos, path, step + 1, successPaths);
		newpos = curpos; //take a step back
	}

	//all directions are bad
	path[step] = '\0';
	m->maze[curpos.ypos][curpos.xpos].visited = false; //current path is done with square so make it unvisited
	return;
}
