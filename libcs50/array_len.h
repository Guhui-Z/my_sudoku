/*
 * array_len.h - header file for CS50 counters module
 *
 * A "array_len" is a struct that contains an array and its length.
 *
 * CS50
 */
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/**************** global types ****************/
typedef struct array_len array_len_t; // opaque to users of the module

/**************** array_len_new ****************/
/* mnakes a new array_len struct
 *
 * Caller provides:
 *   the max size of the array
 * We return:
 *   a pointer to a new array_len struct, NULL if error
 */
array_len_t *array_len_new(int max_size);

/**************** array_len_get ****************/
/*
 * Caller provides:
 *   pointer to a valid array_len
 * We return:
 *   a random digit in the array, 0 if there are no entries
 */
int array_len_get(array_len_t *array_len);

/**************** array_len_get ****************/
/*
 * Inserts a digit into the struct
 * 
 * Caller provides:
 *   pointer to a valid array_len and a digit to insert
 * We return:
 *   Nothing
 */
void array_len_insert(array_len_t *array_len, int digit);

/**************** array_len_delete ****************/
/*
 * Deletes the struct
 *
 * Caller provides:
 *   pointer to a valid array_len
 * We return:
 *   Nothing
 */
void array_len_delete(array_len_t *array_len);