# Makefile for CS50 Sudoku
#
# CS 50, Spring 2022

.PHONY: all valgrind clean


############## default: make all libs and programs ##########
all: 
	make -C libcs50
	make -C sudoku


############## clean  ##########
clean:
	rm -f *~
	make -C libcs50 clean
	make -C sudoku clean

test:
	make -C sudoku test

valgrind:
	make -C sudoku valgrind