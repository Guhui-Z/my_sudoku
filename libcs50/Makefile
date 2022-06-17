# Makefile for CS50 library
#   Builds and compiles all these utility functions into a library.
#
# If you prefer our data-structure implementation over your own, 
# modify the rule for `$(LIB)`:
# $(LIB): libcs50-given.a
#	cp libcs50-given.a $(LIB)
#
# CS50, Spring 2022

# object files, and the target library
OBJS = bag.o counters.o file.o hashtable.o jhash.o memory.o set.o tile.o grid.o array_len.o numbers.o
LIB = libcs50.a

# add -DNOSLEEP to disable the automatic sleep after web-page fetches
#               (students, please do not use -DNOSLEEP!)
# add -DMEMTEST for memory tracking report in indexer
# (and run `make clean; make` whenever you change this)
FLAGS = # -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb -lm $(FLAGS)
CC = gcc

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
bag.o: bag.h
numbers.o: numbers.h
counters.o: counters.h
file.o: file.h
set.o: set.h
hashtable.o: hashtable.h set.h jhash.h 
jhash.o: jhash.h
memory.o: memory.h
set.o: set.h
array_len.o: array_len.h
tile.o: tile.h memory.h
grid.o: grid.h tile.h memory.h file.h array_len.h hashtable.h counters.h bag.h



.PHONY: clean unit 

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o
	rm -f $(PROG) unittest

# unit test 
unittest: grid.c tile.c set.c jhash.c bag.c hashtable.c counters.c file.c memory.c unittest.h
	$(CC) $(CFLAGS) -DUNIT_TEST grid.c tile.c jhash.c bag.c hashtable.c set.c counters.c file.c memory.c -lm -o $@

unit: unittest
	./unittest
