# CS50 Sudoku utility library

The modules include those that support the TSE project and those that we created for the sudoku project. We **did not change any of the other source files in this directory.**

## Usage

To build `libcs50.a`, run `make`.

To clean up, run `make clean`.

## Overview

 * `bag` - the **bag** data structure from Lab 3
 * `counters` - the **counters** data structure from Lab 3
 * [`file`](file.html) - functions to read files (includes readlinep)
 * `hashtable` - the **hashtable** data structure from Lab 3
 * `jhash` - the Jenkins Hash function used by hashtable
 * [`memory`](memory.html) - handy wrappers for malloc/free
 * `set` - the **set** data structure from Lab 3
 * [`webpage`](webpage.html) - functions to load and scan web pages
 * `tile` - the **tile** data structure to store a tile in the sudoku
 * `grid` - the **grid** data structure to store a sudoku
 * `array_len` - the **array_len** data structure to store, insert and get a candidate for a tile in a sudoku
 * `number` - a function to check if a number is a perfect square
