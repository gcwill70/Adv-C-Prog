FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  pa07.o maze.o path.o

pa07: $(OBJS)
	$(GCC) $(OBJS) -o pa07

pa07.o: maze.c path.c pa07.c
	$(GCC) -c pa07.c -o pa07.o

path.o: maze.c path.c
	$(GCC) -c path.c -o path.o

maze.o: maze.c
	$(GCC) -c maze.c -o maze.o

test: pa07
	echo "testing path1"
	./pa07 inputs/maze1 inputs/path1 
	echo "testing path1-bad1"
	./pa07 inputs/maze1 inputs/path1-bad1
	echo "testing path1-bad2"
	./pa07 inputs/maze1 inputs/path1-bad2

memory: pa07
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./pa07 inputs/maze1 inputs/path1

clean:
	/bin/rm -f *.o
	/bin/rm -f pa07
