DATE := $(shell date)
PA = 11

update:
	git add Makefile pa11.c stack.c stack.h
	git commit -m "$(DATE)"
	git push

tag_first:
	git tag -a submission -m "submission or PA$(PA)"
	git push --tags

tag_update:
	git tag -a -f submission -m "submission for PA$(PA)"
	git push --tags

FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  stack.o pa11.o

all: $(OBJS)
	$(GCC) $(OBJS) -o pa11

stack.o: stack.c
	$(GCC) -c stack.c

pa11.o: pa11.c
	$(GCC) -c pa11.c

test: all
	./pa11 inputs/test1
	./pa11 inputs/test2
	./pa11 inputs/test3
	#./pa11 inputs/test4
	./pa11 inputs/test5

memory: all
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./pa11 inputs/test1

clean:
	/bin/rm -f *.o
	/bin/rm -f pa11
