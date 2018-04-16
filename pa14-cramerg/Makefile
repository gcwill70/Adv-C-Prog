DATE := $(shell date)
PA = 14

update:
	git add filterParallel.c filterParallel.h
	git commit -m "$(DATE)"
	git push

tag_first:
	git tag -a submission -m "submission or PA$(PA)"
	git push --tags

tag_update:
	git tag -a -f submission -m "submission for PA$(PA)"
	git push --tags

FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -lpthread
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS = bmp.o filterParallel.o pa14.o

bmp.o:
	$(GCC) -c bmp.c

filterParallel.o: bmp.c
	$(GCC) -c filterParallel.c

pa14.o: bmp.c filterParallel.c
	$(GCC) -c pa14.c

all: $(OBJS)
	$(GCC) $(OBJS) -o pa14

test: all
	./pa14 test.bmp sharpen.filter out.bmp

memory: all
	valgrind -v --tool=memcheck --show-reachable=yes ./pa14 test.bmp out.bmp

clean:
	/bin/rm -f *.o pa14
