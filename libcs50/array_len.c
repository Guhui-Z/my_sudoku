#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "array_len.h"

typedef struct array_len
{
    int N;
    int *digits;
} array_len_t;

array_len_t *array_len_new(int max_size){
    array_len_t *array_len = malloc(sizeof(array_len_t));
    array_len->N = 0;
    array_len->digits = calloc(max_size, sizeof(int));
    return array_len;
}

void array_len_insert(array_len_t *array_len, int digit){
    int N = array_len->N;
    array_len->digits[N] = digit;
    array_len->N+=1;
}

int array_len_get(array_len_t *array_len)
{
    int N = array_len->N;

    if (N == 0){
        return 0;
    }

    int random_index = rand() % N;
    int random_digit = array_len->digits[random_index];
    array_len->digits[random_index] = array_len->digits[N-1];
    array_len->N-=1;

    return random_digit;
}

void array_len_delete(array_len_t *array_len){
    free(array_len->digits);
    free(array_len);
}