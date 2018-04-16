DATE := $(shell date)
PA = 15

#update:
#	git add pa15.c linkedlist.c linkedlist.h tree.h tree.c Makefile
#	git commit -m "$(DATE)"
#	git push
#
#tag_first:
#	git tag -a submission -m "submission or PA$(PA)"
#	git push --tags
#
#tag_update:
#	git tag -a -f submission -m "submission for PA$(PA)"
#	git push --tags

FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -lpthread
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS = pa15.o linkedlist.o tree.o

pa15.o: linkedlist.o tree.o
	$(GCC) -c pa15.c

tree.o: linkedlist.o
	$(GCC) -c tree.c

linkedlist.o:
	$(GCC) -c linkedlist.c

all: $(OBJS)
	$(GCC) $(OBJS) -o pa15

test: all
	./pa15 inputs/basic outputs/basic_sorted outputs/basic_huffman outputs/basic_header
	./pa15 inputs/prideandprejudice outputs/prideandprejudice_sorted outputs/prideandprejudice_huffman outputs/prideandprejudice_header
	diff expected/prideandprejudice_header outputs/prideandprejudice_header
	diff expected/prideandprejudice_sorted outputs/prideandprejudice_sorted
	diff expected/prideandprejudice_huffman outputs/prideandprejudice_huffman

memory: all
	valgrind -v --tool=memcheck --show-reachable=yes ./pa15 inputs/basic outputs/basic_sorted outputs/basic_huffman outputs/basic_header

clean:
	/bin/rm -f *.o
	/bin/rm -f pa15 pa15.prof
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
