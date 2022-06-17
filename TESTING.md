# Testing

# UNIT TESTING 
We test the modules in grid.c using unit testing to ensure proper functionality:

## Solver 
### Two solutions 
```bash
./unittest
Testing solver...
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
```

### Result
```bash
PASS test solver
```

### Unique Solution
```bash
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
```

### Result 
```bash
PASS test solver
```
## Creator
```bash
Testing creator...
Printing sudoku board:
7 9 2 4 1 8 6 5 3 
6 4 3 9 7 5 2 8 1 
1 8 5 2 3 6 7 4 9 
3 1 7 6 4 2 5 9 8 
9 5 6 3 8 1 4 2 7 
8 2 4 5 9 7 1 3 6 
4 7 8 1 5 9 3 6 2 
2 3 9 7 6 4 8 1 5 
5 6 1 8 2 3 9 7 4 
Printing sudoku board:
0 0 0 4 0 8 0 5 0 
0 0 3 9 0 0 2 8 0 
1 0 0 2 0 0 0 0 0 
0 0 0 0 0 0 5 9 0 
0 5 0 0 0 0 0 0 0 
0 0 0 0 9 7 1 3 0 
0 0 8 0 5 0 3 0 0 
0 0 9 0 0 0 0 0 0 
0 0 1 0 0 3 0 7 4 
```

## UNIT TESTING RESULT 
```bash
PASS all test cases
```

# FUZZ TESTING

```bash
./fuzzsudoku 7
```

### Result
```bash
Generating 7 sudoku boards... 
Passed test 0
Passed test 1
Passed test 2
Passed test 3
Passed test 4
Passed test 5
Passed test 6
```


# Argument Testing 
## No arguments
```bash
./sudoku 
```

#### Result
```bash
Usage: ./sudoku mode
```

## Wrong number of arguments
```bash
./sudoku solver create
```
#### Result
```bash
Usage: ./sudoku mode
```
## Unkown mode
```bash
./sudoku not_a_mode
```

#### Result 
```bash
Unknown mode. Mode can be solver or create or play
```


## Not a perfect square 
```bash
./sudoku solver 
Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 3
```

#### Result 
```bash
Invalid input: must be a positive perfect square
```

## Non numeric char
```bash
 ./sudoku solver 
 Sudoku mode: solver
Enter the size of the sudoku (4, 9, 16, ...): 9
Sudoku size: 9
Enter your sudoku board:
1 2 0 4 5 6 0 8 9
a 0 c d e f g h i
```

#### Result 
```bash
Invalid format of entered sudoku board
```
## Valid tests

### One solution 
```bash
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
```

#### Result
```bash
1 Sudoku solution(s) found
Printing sudoku board:
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

## Two solutions 
```bash
udoku mode: solver
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
```

#### Result 
```bash
2 Sudoku solution(s) found
Printing sudoku board:
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

# Valgrind

## Make Valgrind

We tested our program with valgrind extensively to ensure that there were no memory leaks or errors.

You can run `make valgrind` to run a valgrind on the create and solver modes. Make sure the server is running!
