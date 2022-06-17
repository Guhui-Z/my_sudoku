/*
 * numbers.c - CS50 'numbers' module
 *
 * see numbers.h for more information.
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // bool type
#include <string.h>  // memcpy, memset
#include <math.h>

// check if number is perfect square
// modified from https://www.includehelp.com/c-programs/c-program-to-check-number-is-perfect-square-or-not.aspx
bool is_perfect_square(int number)
{
    int i_root;
    float f_root;

    f_root = sqrt((double)number);
    i_root = f_root;

    return (i_root == f_root);
}