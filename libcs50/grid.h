/*
 * grid.h - header file for CS50 grid module
 *
 * A *grid* is a 9 by 9 2D array of tiles used for sudoku.
 *
 * CS 50
 */

#include <stdio.h>
#include <stdbool.h>
#include "array_len.h"

/**************** global types ****************/
typedef struct grid grid_t; // opaque to users of the module

/**************** functions ****************/

/**************** grid_new ****************/
/* Create a new (empty) grid.
 *
 * Caller provides:
 *   size of grid (N > 0 and N is a perfect square)
 * We return:
 *   pointer to the new grid; return NULL if error.
 * We guarantee:
 *   grid is initialized empty.
 * Caller is responsible for:
 *   later calling grid_delete.
 */
grid_t *grid_new(const int N);

/**************** grid_delete ****************/
/* Delete a grid.
 *
 * Caller provides:
 *   valid pointer to a grid
 * We return:
 *   nothing
 * We guarantee:
 *   grid is deleted.
 */
void grid_delete(grid_t *grid);

/**************** grid_print ****************/
/* Prints a grid in one of two formats according to the mode
 *
 * Caller provides:
 *   valid pointer to a grid.
 *   bool indicating whether the current mode is play.
 */
void grid_print(grid_t *grid, bool play_mode);

/**************** grid_load ****************/
/* Load a grid from stdin.
 *
 * Caller provides:
 *   a pointer to a grid as well as stdin input of a grid.
 * We return:
 *   true if the grid is loaded, false otherwise
 * We guarantee:
 *   grid is initialized.
 */
bool grid_load(grid_t *grid);

/**************** grid_load_string ****************/
/* Load a grid from a string.
 *
 * Caller provides:
 *   a pointer to a grid as well as a string input of a grid.
 * We return:
 *   true if the grid is loaded, false otherwise
 * We guarantee:
 *   grid is initialized.
 */
bool grid_load_string(grid_t *grid, char *board);

/**************** grid_solve ****************/
/* Solve a sudoku grid.
 *
 * Caller provides:
 *   pointer to a grid.
 * We return:
 *   0 if there are no solutions; 1 if there is
 *   one solution; 2 if there are multiple solutions
 * We guarantee:
 *   grid is solved with a valid solution
 */
int grid_solve(grid_t *grid);

/**************** valid_digits ****************/
/* Find valid digits
 *
 * Caller provides:
 *   pointer to a graph and a specified tile (row, col)
 * We return:
 *   pointer to an array_len
 * We guarantee:
 *   array_len contains only valid digits
 * Caller is responsible for:
 *   later calling array_len_delete
 */
array_len_t *valid_digits(grid_t *grid, int i, int j);

/**************** grid_empty_cnt ****************/
/* return the count of empty tiles in a grid
 *
 * Caller provides:
 *   valid pointer to the grid.
 * We return:
 *   -1 if the pointer to the grid is NULL; otherwise the count of empty tiles.
 */
int grid_empty_cnt(grid_t *grid);

/**************** grid_random_clue ****************/
/* randomly set tiles to zero in a complete grid to produce a sudoku puzzle
 *
 * Caller provides:
 *   valid pointer to a complete grid.
 * We do:
 *   go through each tile randomly, 
 *   set tiles in the grid to zero as long as the grid only has a unique solution,
 *   set the tile back to its original value if the grid has more than one solution.
 * Note: 
 *   will do nothing if grid is NULL or is incomplete.
 */
void grid_random_clue(grid_t *grid);

/**************** grid_copy ****************/
/* copy the contents of grid1 to grid2
 *
 * Caller provides:
 *   valid pointers to two grids.
 * We do:
 *   go through each tile in grid1 and copy its status and value to grid2.
 * Note: 
 *   will do nothing if either grid is NULL or if grids' dimensions do not match.
 */
void grid_copy(grid_t *grid1, grid_t *grid2);

/**************** grid_set_tile ****************/
/* set a given tile in a grid
 *
 * Caller provides:
 *   valid pointer to a grid,
 *   row (i) and col (j) of the tile,
 *   the status to be set,
 *   the value to be set.
 * We do:
 *   call tile_set() on given tile with given status and value.
 * Note: 
 *   will do nothing if the grid is NULL or if the index are out of range
 */
void grid_set_tile(grid_t *grid, int i, int j, bool confirmed, int value);

/**************** grid_get_value ****************/
/* return the value of a given tile in a grid
 *
 * Caller provides:
 *   valid pointer to a grid,
 *   row (i) and col (j) of the tile.
 * We return:
 *   the value of the tile.
 * We do:
 *   call tile_value() on given tile.
 * Note: 
 *   will do nothing if the grid is NULL or if the index are out of range
 */
int grid_get_value(grid_t *grid, int i, int j);

/**************** grid_get_status ****************/
/* return the status of a given tile in a grid
 *
 * Caller provides:
 *   valid pointer to a grid,
 *   row (i) and col (j) of the tile.
 * We return:
 *   the status of the tile.
 * We do:
 *   call tile_status() on given tile.
 * Note: 
 *   will do nothing if the grid is NULL or if the index are out of range
 */
bool grid_get_status(grid_t *grid, int i, int j);


/**************** grid_cmp ****************/
/* Compares two grids 
 *
 * Caller provides:
 *   valid pointers to two grid,
 * We return:
 *   false if the grids are different, true if they are the same 
 * We do:
 *   check tile_value() on each tile in each grid
 * Note: 
 *   will do nothing if the grid1 or grid2 is NULL or if the index are out of range
 */
bool grid_cmp(grid_t *grid1, grid_t *grid2);


/**************** grid_fprint ****************/
/* Prints grid contents to a file for parsing
 *
 * Caller provides:
 *   valid pointers to a grid, boolean value determining which file to print to 
 * We return:
 *   Nothing
 * We do:
 *   call tile_value() on each tile in each grid
 * Note: 
 *   will do nothing if the grid is NULL
 */
void grid_fprint(grid_t* grid, bool solved);