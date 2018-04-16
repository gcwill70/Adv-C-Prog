DATE := $(shell date)
PA = 10

update:
	git add solver.c list.c
	git commit -m "$(DATE)"
	git push

tag_first:
	git tag -a submission -m "submission for PA$(PA)"
	git push --tags

tag_update:
	git tag -a -f submission -m "submission for PA$(PA)"
	git push --tags

FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  list.o maze.o mazehelper.o pa10.o path.o solver.o

pa10: $(OBJS)

list.o: list.c
	$(GCC) -c list.c

list_test.o: list_test.c list.c
	$(GCC) -c list_test.c

list_test_exec: list_test.o list.o
	$(GCC) list_test.o list.o -o list_test_exec

list_test: list_test_exec
	./list_test_exec list_test.txt

maze.o: maze.c
	$(GCC) -c maze.c

mazehelper.o: mazehelper.c
	$(GCC) -c mazehelper.c

pa10.o: maze.c solver.c path.c
	$(GCC) -c pa10.c

path.o: path.c mazehelper.c
	$(GCC) -c path.c

solver.o: solver.c mazehelper.c list.c path.c
	$(GCC) -c solver.c

test: pa10
	./pa10 inputs/maze1 maze1_sol.txt
	./pa10 inputs/maze2 maze2_sol.txt
	./pa10 inputs/maze3 maze3_sol.txt

clean:
	/bin/rm -f *.o pa10

memory: list_test_exec
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./list_test_exec maze1_sol.txt
