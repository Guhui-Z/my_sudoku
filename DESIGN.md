# Sudoku Design Spec

## Modified by Guhui 

Based on the version by TEAM ECHO (Qaisar Nawaz, Stefel Smith, Daniel Westphal, Guhui Zhang)

## User Interface

```bash
./sudoku [mode]  
```

## Inputs and Outputs

### The creator

The creator has no inputs besides command-line arguments.  
The creator outputs a randomly generated sudoku in the text format specified below.

- The sudoku must have a unique solution.
- The sudoku must have at least 40 missing numbers for a 9 by 9 sudoku.

### The solver

The solver accepts an input sudoku puzzle in the text format specified below. The input may have multiple possible solutions.  
The solver outputs one possible solution to the puzzle in the text format specified below.

### The sudoku text format

- The grid is represented as 9 lines of text
- Each line contains 9 integers that range from 0 to 9, separated by a white space
- 0 represents a missing number in the grid

## Functional Decomposition Into Modules

### class Tile

1. `__init__`, initializes a new tile, containing the integer value of the tile and a boolean indicating whether the integer value is confirmed
2. `tile_print`, prints the value of the tile
3. `tile_set`, set the value and boolean of the tile
4. `tile_value`, return the value of the tile
5. `tile_status`, return the boolean of the tile

### class Grid

1. `__init__`, initializes a new Grid, containing a 2D array of tiles
2. `grid_print`, prints a grid according to the text format specified above
3. `grid_load`, loads a grid from stdin according to the text format specified above
4. `grid_laod_string`, loads a grid from a string in the format `a_11, a_12, ..., a_19, a_21, a_22, ...`
5. `grid_solve`, finds solutions to a grid (sudoku) by calling grid_solve_helper
6. `grid_solve_helper`, recursively finds solutions to a grid (sudoku) through DFS
7. `valid_digits`, creates a bag storing the possible candidates for a tile in the grid (sudoku)
8. `grid_random_clue`, generates a random sudoku and calls `grid_solve` to determine if the sudoku has a unique solution
9. `grid_set_tile`, `grid_get_value`, `grid_get_status`, setter and getter methods
10. `grid_copy`, copies a grid to another grid
11. `grid_cmp`, compares the values of a grid to those of another grid

### sudoku.py

1. `main`, validates arguments and determines mode
2. `solve`, solve the given sudoku by calling `grid_solve`
3. `create`, generates a random sudoku by calling `grid_generate`

## Pseudo Code

### The creator

```pseudocode
create(int N){
Grid grid = grid_new(N);
grid_generate(grid);
grid_print(grid);
}
```

```pseudocode
grid_generate(Grid grid){
	Loop through rows{
		Loop through columns{
			Add a random valid digit at that location (a digit is valid if it has not appeared in the same box, row, and column)
		}
	}

	while there is still a unique solution (ensure at least 40 missing numbers) {
		remove a random digit from the grid
	}
}
```

```pseudocode
grid_print(Grid grid){
	Loop through rows{
		Loop through columns{
			Print digit at position followed by a white space
		}
		Print new line
	}
}
```

### The solver

```pseudocode
solve(){
Grid grid = grid_new(N);
grid_load(grid);
grid_solve(grid);
grid_print(grid);
}
```

```pseudocode
grid_load(Grid grid){
	Loop through command line input
		Populate corresponding position in grid
}
```

```pseudocode
grid_solve(Grid grid){
	Check if there are any definite values we can fill in and fill those in
grid_solve_helper(grid, 0, 0, N);
}
```

```pseudocode
Bool grid_solve_helper(Grid grid, int i, int j, int N){

	If we’re past the last tile return true;

	Skip over if it is a confirmed number;

	Construct a bag of valid numbers for that tile;

If it is the last tile and there’s a valid number for it return true;

	If theres a valid number for that position{
		Assign it
	}
Else{
	Delete bag
	Return false
}


	While grid_helper_solve on next tile is false{
		Choose a different valid number if possible for position i,j and assign it{
			If no valid numbers left delete bag and return false
}
}

Return true;

}
```

## Data Flow through Modules

## solver 

1. creates a new grid to pass into the following modules
2. `grid_load()`  takes in the initialized grid and stores the entries entered in from stdin 
3. `grid_print()` displays the grid to the user, taking in the created grid from `grid_new()`
4. `grid_solve()` solves the grid using the following helpers

    - We create a list storing the possible valid integers that can be in the tile
    - Then we choose a random possible integer from the list for that tile
	
## creator 

1. creates a new grid to pass into the following modules
2. `grid_generate()` takes in the initialized grid and fills it with a randomly generated sudoku with a unique solution
3. `grid_print()` outputs the grid to the user

## Major data structures

1. class `Grid` which stores the 2D array representing the sudoku, along with key functions including `grid_load()`, `grid_print()`, `grid_solve()` and `grid_random_clue()`
2. class `Tile` which stores a boolean `confirmed` and an integer value representing the value at that tile

    - 0 is used to indicate an empty slot on the board

## Testing plan

1. Test the programs with various forms of incorrect command-line arguments to ensure that the command-line parsing, and validation of those parameters, work correctly.

    1. Test the program with incorrect numbers of arguments
    2. Test the program with incorrect arguments (arguments other than “create”, “solve” or "play")

2. Test the program with various valid and invalid sudokus

    1. Test with incomplete sudokus, e.g., less than 9x9
    2. Test with sudokus with non-numbers, e.g. letters and special characters
    3. Test with sudokus with one solution by checking the return value of solver
    4. Test with sudokus with multiple solutions by checking the return value of solver
   
3. Unit test for each class
