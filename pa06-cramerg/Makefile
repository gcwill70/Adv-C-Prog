FLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(FLAGS)
OBJS =  msort.o pa06.o student.o

pa06: $(OBJS)
	$(GCC) $(OBJS) -o pa06

pa06.o: pa06.c student.c 
	$(GCC) -c pa06.c -o pa06.o

student.o: student.c msort.c 
	$(GCC) -c student.c -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME -o student.o

msort.o: msort.c student.c
	$(GCC) -c msort.c -o msort.o

test: pa06
	echo "testinput1"
	./pa06 inputs/testinput1 id1 first1 last1
	echo "testinput2"
	./pa06 inputs/testinput2 id2 first2 last2
	echo "testinput3"
	./pa06 inputs/testinput3 id3 first3 last3

	diff id1 expected/id1	
	diff id2 expected/id2	
	diff id3 expected/id3

	diff first1 expected/first1 	
	diff first2 expected/first2 	
	diff first3 expected/first3 	

	diff last1 expected/last1
	diff last2 expected/last2
	diff last3 expected/last3

memory: pa06
	valgrind -v --tool=memcheck --leak-check=full --show-reachable=yes ./pa06 inputs/testinput3 id3 first3 last3


clean:
	/bin/rm -f *.o
	/bin/rm -f id*
	/bin/rm -f first*
	/bin/rm -f last*
	/bin/rm -f pa06
