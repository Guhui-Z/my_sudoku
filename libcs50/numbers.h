/*
 * numbers.h - header file for CS50 numbers module
 *
 * Implements functions related to numbers
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool type
#include <string.h>  // memcpy, memset

/**************** is_perfect_square ****************/
/* Checks if a number is a perfect square.
 *
 * Caller provides:
 *   an integer
 * We return:
 *   true if the number is a perfect positive square, false otherwise
 */
bool is_perfect_square(int number);