
PROG = sudoku sudoku_server fuzzsudoku
OBJS = sudoku.o sudoku_server.o fuzzsudoku.o
LIBS = ../libcs50/libcs50.a

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../lib
CC = gcc
MAKE = make


.PHONY: all clean test valgrind

all: sudoku sudoku_server fuzzsudoku

sudoku.o: ../libcs50/grid.h ../libcs50/tile.h ../libcs50/numbers.h
sudoku_server.o: ../libcs50/grid.h ../libcs50/memory.h ../libcs50/numbers.h
fuzzsudoku.o: ../libcs50/grid.h ../libcs50/tile.h

sudoku: sudoku.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

sudoku_server: sudoku_server.o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

fuzzsudoku: fuzzsudoku.o $(LIBS)
	$(CC) $(CFLAGS) $^ -lm -o $@


test: fuzzsudoku
	./fuzzsudoku 7 > testing.out

valgrind: sudoku
	echo "9" | valgrind ./sudoku create
	echo -e "9\n9 0 6 0 7 0 4 0 3 \n0 0 0 4 0 0 2 0 0 \n0 7 0 0 2 3 0 1 0 \n5 0 0 0 0 0 1 0 0 \n0 4 0 2 0 8 0 6 0 \n0 0 3 0 0 0 0 0 5 \n0 3 0 7 0 0 0 5 0 \n0 0 7 0 0 5 0 0 0 \n4 0 5 0 1 0 7 0 8" | valgrind ./sudoku solver

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f $(PROG)
	rm -f *~ *.txt


