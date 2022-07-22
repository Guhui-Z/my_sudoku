# Sudoku

## Modified by Guhui

Based on CS50 Spring 2022, Sudoku final project by TEAM ECHO (Qaisar Nawaz, Stefel Smith, Daniel Westphal, Guhui Zhang)  
The project was originally written in C. I re-implemented it in Python to add more functionalities and a GUI.

## Command Line Interface

`main/sudoku.py` implements a command line interface.

```bash
Usage: Usage: python sudoku.py [mode]
```

`mode` can be `create`, `solver` or `play`

### Format

The sudoku board should be entered in the format

- The grid is represented as 9 lines of text
- Each line contains 9 integers that range from 0 to 9, separated by a white space
- 0 represents a missing number in the grid

```text
a11 ... a1n
.        .
.        .
.        .
an1 ... ann
```

where n is the size of the sudoku board.

### Example

```bash
$ python sudoku.py create
Sudoku mode: create
Enter the size of the sudoku (4, 9, 16, ...): 4
Sudoku size: 4
0 3 0 0 
0 0 0 0 
0 2 1 0 
0 0 4 0 
$ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 4
Sudoku size: 4
Enter your sudoku board:
0 3 0 0 
0 0 0 0 
0 2 1 0 
0 0 4 0 
1 solution(s) found:
1 3 2 4 
2 4 3 1 
4 2 1 3 
3 1 4 2 
$ python sudoku.py play
Enter the size of the sudoku (4, 9, 16, ...): 4
Sudoku size: 4
  |0 1 2 3 
-----------
0 |0 0 0 0 
1 |0 0 2 0 
2 |0 3 0 0 
3 |2 0 1 0 
Empty tiles count: 12
Enter your next step (row col num), or type 'clue' or 'q':1 1 1
  |0 1 2 3 
-----------
0 |0 0 0 0 
1 |0 1 2 0 
2 |0 3 0 0 
3 |2 0 1 0 
Enter your next step (row col num), or type 'clue' or 'q':clue
Clue: 1 3 4
  |0 1 2 3 
-----------
0 |0 0 0 0 
1 |0 1 2 4 
2 |0 3 0 0 
3 |2 0 1 0 
Enter your next step (row col num), or type 'clue' or 'q':q
Quit program
```

## GUI 

`main/sudoku_gui.py` implements a command line interface.

### New Game

Play around with a randomly generate sudoku.

![](https://github.com/Guhui-Z/my_sudoku/blob/main/new_game.gif =300x300)

### Solver

Input a sudoku and see how it is solved.

![](https://github.com/Guhui-Z/my_sudoku/blob/main/solver.gif =300x300)

## Files

`lib/` contains modules used by the sudoku program
- `number.py` has a function to check if the number is a perfect square
- `tile.py` has the *tile* data structure
- `grid.py` has the *grid* data structure (consisting of *tiles*)

`main/` contains
- `sudoku.py`
- `sudoku_gui.py`
