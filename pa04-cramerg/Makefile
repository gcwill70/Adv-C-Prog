CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
GCC = gcc $(CFLAGS) $(PROFFLAG)
FUNCS = func1.o func2.o func3.o func4.o func5.o
OBJS =  pa04.o answer04.o

all: pa04

pa04: $(OBJS) $(FUNCS) pa04.h
	$(GCC) $(OBJS) $(FUNCS) -o pa04 -lm

pa04.o: pa04.c pa04.h answer04.c
	$(GCC) -c pa04.c pa04.h -lm
func1.o: func1.c
	$(GCC) -c func1.c

#compile func2
func2.o: func2.c
	$(GCC) -c func2.c

#compile func3
func3.o: func3.c
	$(GCC) -c func3.c

#compile func4
func4.o: func4.c
	$(GCC) -c func4.c

#compile func5
func5.o: func5.c
	$(GCC) -c func5.c
answer04.o: answer04.c pa04.h pa04.c
	$(GCC) -c answer04.c -DRUN_INTEGRATE -DTEST_INTEGRATE -o answer04.o -lm

testall: pa04
	echo "test1"
	./pa04 testdir/test1 output_test1
	echo "test2"
	./pa04 testdir/test2 output_test2
	echo "test3"
	./pa04 testdir/test3 output_test3
	echo "test4"
	./pa04 testdir/test4 output_test4
	echo "test5"
	./pa04 testdir/test5 output_test5

clean:
	/bin/rm -f input*
	/bin/rm -f *.o
	/bin/rm -f testgen 
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa04 pa04.prof

