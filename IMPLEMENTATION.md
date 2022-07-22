# Soduku Implementation Spec

## Modified by Guhui

Based on the version by TEAM ECHO (Qaisar Nawaz, Stefel Smith, Daniel Westphal, Guhui Zhang)

## Pseudo code

### main

0. Execute from the command line to start the program with a certain mode.
1. Prompt the user for the size of the board, only taking in perfect squares using the `is_perfect_square` method.
2. Check the mode and call the relevant functions.

### Solver

1. Initialize a grid.

2. Next, load the grid in from **stdin**. Using try-except we check for valid input defined in README and DESIGN docs. We loop through the tiles in the grid and assign them in the same order inputted by the user. 

3. Once a valid grid is submitted we pass the grid into `grid_solve`. We keep track of the number of possible solutions in a sol variable and pass the grid into our recursive helper and start solving via backtracking:
    * if we have not yet reached the end of the row and we have not yet reached a solution by the end of the grid continue searching for valid solutions in each tile (base cases).
        1. Starting at the top left tile, check if we have already found a possible or actual valid integer entry. 
            * if we have then recursively move onto the j + 1 tile
        2. If we have not yet made a guess as to the valid entry, create a list that stores the possible valid entries by checking the row *i*, column *j* and the block of tile *( i , j )*.
        3. get a random number from the list and store it in the current tile. Recursively traverse the grid and as long as the next tile is solvable move forward; if it isn't, pick a new random value for the tile and try to move forward again. 
        4. Once we reach the end we can add to our solution count
3. iterate through grid by calling `grid_print`, looping through each tile in each table and printing out the values to **stdout**

### Creator

1. Initialize a new `grid` and pass the grid into `grid_solve` in order to produce a solved grid.
    1. We recursively loop through the entire grid struct, initially with every value at zero, to find any possible solution via backtracking.

2. While we still have a unique solution, set the value of random tiles to 0.
    1. go through the solved grid and make the status of each entry true
    2. save the total count of the grid and use that value to create a position array of size **total_cnt**. In the entries of the position array store the location of the tiles.
    3. while we have not visited all the tiles
        1. Create a temporary grid and copy the original grid into this one (since `grid_solve` modifies the grid)
        2. Pick indexes from the position array that represents the locations of tiles to visit in a random order.
        3. Set the tile corresponding to the index to zero in the temp grid
        4. Call `grid_solve` to check the number of solutions to the temp grid
        5. if there is still only one solution to the temp board, set the tile in the original grid to zero and change status to false
        6. else set the tile back to its original value
    4. delete the temp copy of the grid
    
## Detailed APIs and data structures

The sudoku uses the following APIs and data structures

- `../lib/tile.py` has the *tile* data structure
- `../lib/grid.py` has the *grid* data structure
- `../lib/number.py` has a function to check if the number is a perfect square

## Error handling and recovery

- The sudoku exits with an error message and non-zero exit status if it encounters an unrecoverable error, including:

1. invalid command-line arguments
2. invalid sudoku size
3. invalid sudoku

The sudoku play mode ignores and continues if it encounters an invalid user input
