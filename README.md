# CS50 Spring 2022, Sudoku final project
## TEAM ECHO, Qaisar Nawaz, Stefel Smith, Daniel Westphal, Guhui Zhang

GitHub usernames: qaisarnwz, StefelS, dewestphal, Guhui-Z

## HOW TO PLAY 
Choose a mode: create, solver, play

## Entering a board
We enter the board from stdin in the format: 

```text
a11 ... a1n
.        .
.        .
.        .
an1 ... ann
```

where n is the size of the sudoku board.

## Reading the board 

0 is used to represent an empty slot on the board. 

## Compiling

To build, simply type `make`.

For fuzztesting, type `make all`.

For testing, `make test`.

## Extra credits

Our group implemented the following functionalities for extra credits:

- variable size sudoku; the size can be any positive perfect square number.
- a play mode where a random sudoku is generated and users can input (row, col, num) to fill the sudoku. Once a sudoku is filled, the correct user-inputted numbers are kept and the incorret ones are deleted. The new sudoku continues to prompt for user input, until all inputs are correct (sudoku is solved).
- a GUI of the solver mode that shows the solution of a given sudoku. We read in the files outputted by our soduku solver and parse each character in the file using a python script. We then enumerate over a grid to update the tile entries with the solved values.
- a TCP server/client model using the Berkeley sockets API, where the client sends the server the size of the sudoku board and the server sends back a sudoku board to solve as a string.

