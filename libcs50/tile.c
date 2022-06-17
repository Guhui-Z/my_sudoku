/*
 * counters.c - CS50 'counter' module
 *
 * see counters.h for more information.
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "tile.h"
#include "memory.h"

/**************** global types ****************/

typedef struct tile
{
    bool confirmed; // if the value is confiemd to be value
    int value;      // value at that spot in the grid
} tile_t;

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
tile_t *tile_new()
{
    tile_t *tile = malloc(sizeof(tile_t));
    tile->confirmed = false;
    tile->value = 0;
    return tile;
}


void tile_print(tile_t *tile, int n){
    printf("%*d", n, tile->value);
}

void tile_set(tile_t *tile, bool confirmed, int value){
    tile->confirmed = confirmed;
    tile->value = value;
}

int tile_value(tile_t *tile){
    return tile->value;
}

bool tile_status(tile_t *tile){
    return tile->confirmed;
}

void tile_delete(tile_t *tile){
    free(tile);
}