# CS50 Final Project

## CS50 Spring 2022

### grid

A `grid` consists of a 2D array of `tile`s and an integer `N` storing the size of the grid.  
`N` must be a positive perfect square number.
It starts empty, filled with 0.

### Usage

The *grid* module, defined in `grid.h` and implemented in `grid.c`, implements a 2D array of `tile`s and an integer `N`, and exports the following functions:

```c
grid_t *grid_new(const int N);
void grid_delete(grid_t *grid);
void grid_print(grid_t *grid, bool play_mode);
bool grid_load(grid_t *grid);
bool grid_load_string(grid_t *grid, char *board);
int grid_solve(grid_t *grid);
array_len_t *valid_digits(grid_t *grid, int i, int j);
int grid_empty_cnt(grid_t *grid);
void grid_random_clue(grid_t *grid);
void grid_copy(grid_t *grid1, grid_t *grid2);
void grid_set_tile(grid_t *grid, int i, int j, bool confirmed, int value);
int grid_get_value(grid_t *grid, int i, int j);
bool grid_get_status(grid_t *grid, int i, int j);
```

### Implementation

We implement `grid` as a 2D array of pointers to `tile`s.  
The *grid* is represented as a `struct grid` containing an int `N` and `tile_t*** table`.  

The `grid_delete` method calls the `tile_delete` function. Then the 2D itself is freed.

The `grid_print` method prints with formatting depending on whether it is the play mode and calls the `tile_print` function.

The `grid_load` method loads the sudoku by repeatedly reading form input according to the format specified in `../DESIGN.md`.

The `grid_load_string` method loads the sudoku from a string.

The `grid_solve` method solves a grid based on the algorithm outlined in `../DESIGN.md` and return 0 if there are no solutions; 1 if there is one solution; 2 if there are multiple solutions.

The `valid_digits` method returns a `array_len_t` containing the valid candidates of a given tile in the grid. It reads the relevant row, col and block, adds existing numbers into a counters and add the valid numbers into a `array_len_t`.

The `grid_empty_cnt` method returns the number of empty tiles in a grid by looping through all grids.

The `grid_random_clue` method randomly set tiles to zero in a complete grid to produce a sudoku puzzle. It goes through all tiles, so for a 9*9 grid the number of empty tiles must be larger than 40.

The `grid_copy` method copies the contents of grid1 to grid2. It assumes that neither grid is NULL and their sizes match.

The `grid_set_tile` method sets a given tile by calling `tile_set`.

The `grid_get_value` method returns the value of a tile by calling `tile_value`.

The `grid_get_status` method returns the status of a tile by calling `tile_status`.
