DATE := $(shell date)
PA = 13

update:
	git add bmp.c filter.c filter.h bmp.h
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
OBJS = bmp.o filter.o pa13.o

bmp.o:
	$(GCC) -c bmp.c

filter.o: bmp.c
	$(GCC) -c filter.c

pa13.o: bmp.c filter.c
	$(GCC) -c pa13.c

validate.o: bmp.c
	$(GCC) -c validate.c

validate: validate.o bmp.o
	$(GCC) validate.o bmp.o -o validate

all: $(OBJS)
	$(GCC) $(OBJS) -o pa13

test: all
	./pa13 test.bmp sharpen.filter out.bmp

test_val: validate
	./validate test.bmp out.bmp

memory: all
	valgrind -v --tool=memcheck --show-reachable=yes ./pa13 test.bmp out.bmp	

clean:
	/bin/rm -f *.o pa13 validate

