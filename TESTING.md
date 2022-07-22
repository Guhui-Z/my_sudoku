# Testing

# UNIT TESTING 
We test the modules in `number.py`, `tile.py` and `grid.py` by running the unit tests. All unit tests are passed.

## INTEGRATION TESTING (sudoku.py)

### Argument Testing

#### No arguments

```bash
$ python sudoku.py
Usage: python sudoku.py mode
```

#### Wrong number of arguments

```bash
 $ python sudoku.py solver create
Usage: python sudoku.py mode
```

#### Unkown mode

```bash
 $ python sudoku.py not_a_mode
Unknown mode. Mode can be solver or create or play
```

### Not a perfect square

```bash
python sudoku.py create
Sudoku mode: create
Enter the size of the sudoku (4, 9, 16, ...): 3
Invalid input: must be a positive perfect square
```

### Non numeric char

```bash
$ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
1 2 0 4 5 6 0 8 9
a 0 c d e f g h
Invalid format of entered sudoku board
invalid literal for int() with base 10: 'a'
```

### Solver

#### One solution 

```bash
 $ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
0 0 0 2 6 0 7 0 1
6 8 0 0 7 0 0 9 0
1 9 0 0 0 4 5 0 0
8 2 0 1 0 0 0 4 0
0 0 4 6 0 2 9 0 0
0 5 0 0 0 3 0 2 8
0 0 9 3 0 0 0 7 4
0 4 0 0 5 0 0 3 6
7 0 3 0 1 8 0 0 0
1 solution(s) found:
4 3 5 2 6 9 7 8 1 
6 8 2 5 7 1 4 9 3 
1 9 7 8 3 4 5 6 2 
8 2 6 1 9 5 3 4 7 
3 7 4 6 8 2 9 1 5 
9 5 1 7 4 3 6 2 8 
5 1 9 3 2 6 8 7 4 
2 4 8 9 5 7 1 3 6 
7 6 3 4 1 8 2 5 9
```

#### Two solutions 

```bash
$ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
9 0 6 0 7 0 4 0 3
0 0 0 4 0 0 2 0 0 
0 7 0 0 2 3 0 1 0
5 0 0 0 0 0 1 0 0 
0 4 0 2 0 8 0 6 0 
0 0 3 0 0 0 0 0 5
0 3 0 7 0 0 0 5 0 
0 0 7 0 0 5 0 0 0 
4 0 5 0 1 0 7 0 8
2 solution(s) found:
9 2 6 5 7 1 4 8 3 
3 5 1 4 8 6 2 7 9 
8 7 4 9 2 3 5 1 6 
5 8 2 3 6 7 1 9 4 
1 4 9 2 5 8 3 6 7 
7 6 3 1 9 4 8 2 5 
2 3 8 7 4 9 6 5 1 
6 1 7 8 3 5 9 4 2 
4 9 5 6 1 2 7 3 8
```

### No solutions

```bash
$ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
9 0 6 0 7 0 4 0 3
0 0 0 4 0 0 2 0 0 
0 7 0 0 2 3 0 1 0
5 0 0 0 0 0 1 0 0 
0 4 0 2 0 8 0 6 0 
0 0 3 0 0 0 0 0 5
0 3 0 7 0 0 0 5 0 
0 0 7 0 0 5 0 0 0 
4 0 5 0 1 0 7 0 3
Sudoku solution not found
```

### Creator

```bash
 $ python sudoku.py create
Sudoku mode: create
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
0 0 0 8 0 7 0 0 0 
9 0 6 0 0 0 0 0 0 
0 8 0 0 0 9 1 0 3 
0 0 1 0 0 0 3 0 0 
0 0 4 0 8 0 2 0 0 
0 5 0 7 0 0 0 0 0 
6 0 0 3 0 0 0 0 0 
0 4 0 6 7 0 0 0 0 
0 1 7 0 0 0 0 6 9 
~/CsCode/CS50/labs/my_sudoku/main (main) $ python sudoku.py solver
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
0 0 0 8 0 7 0 0 0 
9 0 6 0 0 0 0 0 0 
0 8 0 0 0 9 1 0 3 
0 0 1 0 0 0 3 0 0 
0 0 4 0 8 0 2 0 0 
0 5 0 7 0 0 0 0 0 
6 0 0 3 0 0 0 0 0 
0 4 0 6 7 0 0 0 0 
0 1 7 0 0 0 0 6 9 
1 solution(s) found:
1 3 5 8 4 7 9 2 6 
9 7 6 1 3 2 4 8 5 
4 8 2 5 6 9 1 7 3 
8 9 1 2 5 6 3 4 7 
7 6 4 9 8 3 2 5 1 
2 5 3 7 1 4 6 9 8 
6 2 8 3 9 5 7 1 4 
5 4 9 6 7 1 8 3 2 
3 1 7 4 2 8 5 6 9 
```