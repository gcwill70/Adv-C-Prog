FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  pa05.o student.o

all: pa05

pa05: $(OBJS)
	$(GCC) $(OBJS) -o pa05

pa05.o: pa05.c student.c student.h
	$(GCC) -c pa05.c -o pa05.o

student.o: student.c student.h pa05.c
	$(GCC) -c student.c -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME -o student.o

test: pa05
	echo "testinput1"
	./pa05 inputs/testinput1 id1 first1 last1
	echo "testinput2"
	./pa05 inputs/testinput2 id2 first2 last2
	echo "testinput3"
	./pa05 inputs/testinput3 id3 first3 last3

	diff id1 expected/id1	
	diff id2 expected/id2	
	diff id3 expected/id3

	diff first1 expected/first1 	
	diff first2 expected/first2 	
	diff first3 expected/first3 	

	diff last1 expected/last1
	diff last2 expected/last2
	diff last3 expected/last3

memory: pa05
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./pa05 inputs/testinput3 id3 first3 last3


clean:
	/bin/rm -f *.o
	/bin/rm -f id*
	/bin/rm -f first*
	/bin/rm -f last*
	/bin/rm -f pa05
