DATE := $(shell date)
PA = 12

update:
	git add expressionTree.c
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
OBJS = expressionTree.o pa12.o scanner.o tree.o

all: $(OBJS)
	$(GCC) $(OBJS) -o pa12

expressionTree.o: tree.c
	$(GCC) -c expressionTree.c

pa12.o: scanner.o tree.o expressionTree.o
	$(GCC) -c pa12.c

scanner.o:
	$(GCC) -c scanner.c

tree.o: scanner.c
	$(GCC) -c tree.c

test: all
	./pa12 inputs/test1 out1
	./pa12 inputs/test2 out2
	./pa12 inputs/test3 out3
	./pa12 inputs/test4 out4

clean:
	/bin/rm -f *.o
	/bin/rm -f pa12
