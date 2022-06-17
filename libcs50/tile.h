/*
 * tile.h - header file for CS50 hashtable module
 *
 * A *tile* is a component of a grid containing
 * an integer and a boolean indicating if that
 * tile is confirmed to be correct
 *
 * CS 50
 */

#include <stdio.h>
#include <stdbool.h>

/**************** global types ****************/
typedef struct tile tile_t; // opaque to users of the module

/**************** functions ****************/

/**************** tile_new ****************/
/* Create a new (empty) tile.
 *
 * Caller provides:
 *   Nothing
 * We return:
 *   pointer to the new tile; return NULL if error.
 * We guarantee:
 *   tile is initialized to 0 and false
 * Caller is responsible for:
 *   later calling tile_delete
 */
tile_t *tile_new();

/**************** tile_print ****************/
/* Print a tile.
 *
 * Caller provides:
 *   pointer to a tile and the size of the sudoku
 * We return:
 *   Nothing, but we print the tile's value
 */
void tile_print(tile_t* tile, int n);

/**************** tile_set ****************/
/* sets values of a tile
 *
 * Caller provides:
 *   pointer to a tile and values to set
 * We return:
 *   nothing
 * We guarantee:
 *   tile is set to those values
 */
void tile_set(tile_t* tile, bool confirmed, int value);

/**************** tile_delete ****************/
/* Deletes a tile
 *
 * Caller provides:
 *   pointer to a tile.
 * We return:
 *   Nothing
 * We guarantee:
 *   tile is deleted
 */
void tile_delete(tile_t *tile);

/**************** tile_value ****************/
/* Returns tile value
 *
 * Caller provides:
 *   pointer to a tile
 * We return:
 *   value of the tile's digit
 */
int tile_value(tile_t *tile);

/**************** tile_status ****************/
/* Returns tile value
 *
 * Caller provides:
 *   pointer to a tile
 * We return:
 *   value of the tile's confirmed boolean
 */
bool tile_status(tile_t *tile);