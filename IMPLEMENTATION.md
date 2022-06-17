# Soduku Implementation Spec

## Pseudo code

### main

0. Execute from the command line to start the program with a certain mode.
1. Prompt the user for the size of the board, only taking in perfect squares using the `is_perfect_square` method.
2. Check the mode and call the relevant functions.

### Solver

1. In `grid_new` we allocate space for all members of the `grid_t` struct. The grid is represented by 3 nested pointer arrays. The first member **table** represents the whole soduku board and has N pointers to corresponding to the N square sections on the board. Each square then has N `tile_t` strcts that holds the possible valid numbers in that slot.

2. Next, load the grid in from **stdin**. Using the sscanf function we check for valid input defined in README and DESIGN docs. We loop through the tiles in the grid struct and assign them in the same order inputed by the user. 

3. Once a valid grid is submitted we pass the grid into `grid_solve`. We keep track of the number of possible solutions in a sol variable and pass the grid into our recursive helper and start solving via backtracking:
    * if we have not yet reached the end of the row and we have not yet reached a solutioin by the end of the grid continue searching for valid solutions in each tile (base cases).
        1. Starting at the top left tile, check if we have already found a possible or actual valid integer entry. 
            * if we have then recursively move onto the i + 1 tile
        2. If we have not yet made a guess as to the valid entry, create a `array_len*` that stores the possible valid entries by checking the row *i* and column *j* of tile *( i , j )*.
        3. get a random number from the bag and stor in in the current tile. Recursivle traverse the grid and as long as the next tile is solvable move forward, if it isn't pick a new random value for the tile and try to move forward again. 
        4. Once we reach the end we can add to our solution count and delete the bag 
3. interate through grid by calling `grind_print`, looping through each tile in each table and priting out the values to **stdout**
4. delete the table and free all allocated memory.

## Detailed APIs, interfaces, function prototypes and their parameters

### APIs

The sudoku uses the following APIs:

#include "../libcs50/tile.h"
#include "../libcs50/grid.h"
#include "../libcs50/memory.h"
#include "../libcs50/file.h"
#include "../libcs50/numbers.h"

- `../libcs50/tile.h` has the *tile* data structure
- `../libcs50/grid.h` has the *grid* data structure
- `../libcs50/array_len.h` has the *array_len* data structure
- `../libcs50/numbers.h` has a function to check if the number is a perfect square
- `../libcs50/memory.h` with function `assertp`
- `../libcs50/file.h` contains functions to read from a file

### Function prototypes

The sudoku has the following function prototypes:

```C
void play_grid(int N, grid_t *grid_answer, grid_t *grid_puzzle, grid_t *grid_user);
grid_t *get_grid();
int get_sudoku_size();
```

## Data structures

The querier makes use of the following data structures:

- `counters_t` from `counters.h`
- `index` from `index.h`, a hashtable with char *keys and `counters_t` items
- struct `twocts` of two counters
- struct `search_result` of (doc_id, score) pairs
- struct `search_result_all`, an array of struct `search_result` (doc_id, score) and an int of the number of items in the array

## Error handling and recovery

- The sudoku exits with an error message and non-zero exit status if it encounters an unrecoverable error, including:

1. failure to allocate memory
2. invalid command-line arguments
3. invalid sudoku size
4. invalid sudoku
5. failure to open or connect to socket
6. unknown host

The sudoku play mode ignores and continues if it encounters an invalid user input

# Soduku Server Implementation Spec

## Pseudo code

### main

1. Open socket
2. Bind socket to port
3. Listen for client
4. Accept client
    5. Read input
        6. If valid input
            7. Create sudoku board
            8. Write sudoku board to client

### Creator

1. Initialize a new `grid_t*` by calling `grid_new` and pass the grid into `grid_solve` in order to produce a fnal solved grid.
    1. We recursively loop through the entire grid struct, initially with every value at zero, to find any possible solutioin via backtracking.

2. While we still have a unique solution, set the value of random tiles to 0.
    1. go through the solved grid and make the status of each entry true
    2. save the total count of the grid and use that value to create a positioin array of size **total_cnt**. In the entries of the position array store the location of the tiles.
    3. Loop through the position array and shuffle the array randomly
    4. Create a temporary grid and copy the old grid into this one. Pick indexes from the position array that represents the locations of tiles to visit in a random order.
        1. While we are not at the end of the grid, if there is still only one solution to the temp board, get a random position from the position array to set to 0 and change the status to false.
        2. increment the deleted values count.
    5. delete the temp compy of the grid and the original grid.
