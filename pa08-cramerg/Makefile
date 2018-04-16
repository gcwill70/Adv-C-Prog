FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  path.o pa08.o solver.o maze.o

pa08: $(OBJS)

pa08.o: pa08.c solver.c
	$(GCC) -c pa08.c -o pa08.o

solver.o: solver.c
	$(GCC) -c solver.c -o solver.o

test: pa08
	echo "testing maze1"
	./pa08 inputs/maze1 path1
	echo "testing maze2"
	./pa08 inputs/maze2 path2
	echo "testing maze3"
	./pa08 inputs/maze3 path3
	echo "testing maze4"
	./pa08 inputs/maze4 path4
	echo "testing maze5"
	./pa08 inputs/maze5 path5
	echo "testing maze6"
	./pa08 inputs/maze6 path6

memory: pa08
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./pa08 inputs/maze1

clean:
	/bin/rm -f solver.o
	/bin/rm -f pa08.o
	/bin/rm -f pa08
