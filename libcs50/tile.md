# CS50 Final Project

## CS50 Spring 2022

### tile

A `tile` consists of a bool `confirmed` and an integer `value`.

### Usage

The *tile* module, defined in `tile.h` and implemented in `tile.c`, exports the following functions:

```c
tile_t *tile_new();
void tile_print(tile_t* tile, int n);
void tile_set(tile_t* tile, bool confirmed, int value);
void tile_delete(tile_t *tile);
int tile_value(tile_t *tile);
bool tile_status(tile_t *tile);
```

### Implementation

The *tile* is represented as a `struct tile` containing a bool `confirmed` and an integer `value`.

The `tile_delete` method frees the tile.

The `tile_print` method prints the number with appropriate whitespace based on the parameter `N` (size of sudoku).

The `tile_set` method updates the tile with the given bool and int.

The `tile_value` method returns the value of the tile.

The `tile_status` method returns the bool value of the tile.
