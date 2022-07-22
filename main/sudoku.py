"""
The sudoku program using the command line as user interface
Usage: python sudoku.py [mode]
[mode] can be create, solver or play

Guhui Zhang, 2022
"""

import sys
sys.path.insert(0, '../lib')
import random
import number
from grid import *


def get_sudoku_size():
    """
    reads the size of the sudoku from stdin,
    checks whether the number is a positive perfect square integer

    :return: the inputted size of the sudoku; -1 if the number is invalid
    """
    try:
        n = int(input('Enter the size of the sudoku (4, 9, 16, ...): '))
    except Exception as e:
        print('Invalid input: must be an integer', file=sys.stderr)
        print(e, file=sys.stderr)
        return -1

    if (n <= 0) or (not number.is_perfect_square(n)):
        print('Invalid input: must be a positive perfect square', file=sys.stderr)
        return -1

    print(f'Sudoku size: {n}')
    return n


def play_grid(n, grid_answer, grid_puzzle, grid_user):
    """
    implements the play mode

    :param n: the size of the sudku
    :param grid_answer: the grid containing the answer to the sudoku puzzle
    :param grid_puzzle: the grid containing the sudoku puzzle
    :param grid_user: the grid containing the user input to the puzzle
    :return: none
    """
    empty_cnt = grid_puzzle.grid_empty_cnt()
    wrong_cnt = empty_cnt
    print(f'Empty tiles count: {empty_cnt}')

    # stores the clues; intended for giving a clue to the user
    clues = [(i, j) for i in range(n) for j in range(n) if not grid_puzzle.grid_get_status(i, j)]

    while wrong_cnt > 0:  # while the puzzle is not correctly filled
        while empty_cnt > 0:  # while the puzzle is not filled
            line = input("Enter your next step (row col num), or type 'clue' or 'q':")
            if line == 'q':
                print('Quit program')
                return

            if line == 'clue':  # gives a random clue and fill it in the user grid
                temp = random.randint(0, len(clues)-1)
                i, j = clues.pop(temp)
                num = grid_answer.grid_get_value(i, j)
                print(f'Clue: {i} {j} {num}')
                grid_user.grid_set_tile(i, j, False, num)
            else:
                try:  # the input should be row col num
                    args = [int(arg) for arg in line.split()]
                    i = args[0]
                    j = args[1]
                    num = args[2]
                except Exception as e:
                    print('Invalid input. Try again', file=sys.stderr)
                    print(e, file=sys.stderr)
                    return

            if (i < 0) or (i >= n):
                print(f'Row {i} must be between [0, {n-1}]. Try again', file=sys.stderr)
                continue

            if (j < 0) or (j >= n):
                print(f'Column {j} must be between [0, {n-1}]. Try again', file=sys.stderr)
                continue

            if (num < 1) or (num > n):
                print(f'Number {num} must be between [1, {n}]. Try again', file=sys.stderr)
                continue

            if grid_user.grid_get_status(i, j):
                print(f'Tile ({i}, {j}) is a fixed clue. Try again', file=sys.stderr)

            # store the previous number in the specified tile
            prev_num = grid_user.grid_get_status(i, j)
            # set the value in the user grid
            grid_user.grid_set_tile(i, j, False, num)

            # increment empty_cnt if a nonzero tile is set to zero
            if (prev_num != 0) and (num == 0):
                empty_cnt += 1
            # decrement empty_cnt if a zero tile is set to nonzero
            elif (prev_num == 0) and (num != 0):
                empty_cnt -= 1

            correct_num = grid_answer.grid_get_value(i, j)
            # decrement wrong_cnt if an incorrect tile is set to correct
            if (prev_num != correct_num) and (num == correct_num):
                grid_puzzle.grid_set_tile(i, j, False, num)
                wrong_cnt -= 1
            # increment wrong_cnt if a correct tile is set to incorrect
            elif (prev_num == correct_num) and (num != correct_num):
                grid_puzzle(i, j, False, 0)
                wrong_cnt += 1

            grid_user.grid_print(play_mode=True)

        if wrong_cnt == 0:
            print('Success! You solved the sudoku!')
        else:
            print("Uh oh...Incorrect solution. We've kept the correct tiles. Try again!")

            # restart game
            # copy puzzle grid (that has correct user input) to the user grid
            grid_puzzle.grid_copy(grid_user)
            grid_user.grid_print(play_mode=True)
            empty_cnt = grid_puzzle.grid_empty_cnt()
            wrong_cnt = empty_cnt
            print(f'Empty tiles count: {empty_cnt}')


argc = len(sys.argv)
if argc != 2:  # check number of arguments
    print('Usage: python sudoku.py mode', file=sys.stderr)
    exit(1)

if sys.argv[1] == 'create':
    print('Sudoku mode: create')
    n = get_sudoku_size()
    if n == -1:
        exit(2)

    grid = Grid(n)
    grid.grid_solve()
    grid.grid_random_clue()
    grid.grid_print()

elif sys.argv[1] == 'solver':
    print('Sudoku mode: solver')
    n = get_sudoku_size()
    if n == -1:
        exit(2)

    grid = Grid(n)
    if not grid.grid_load():
        exit(3)

    sol = grid.grid_solve()
    if sol == 0:
        print('Sudoku solution not found')
    else:
        print(f'{sol} solution(s) found:')
        grid.grid_print()

elif sys.argv[1] == 'play':
    n = get_sudoku_size()
    grid_puzzle = Grid(n)  # stores the puzzle
    grid_answer = Grid(n)  # stores the answer
    grid_user = Grid(n)  # stores the user input

    grid_puzzle.grid_solve()
    grid_puzzle.grid_copy(grid_answer)

    grid_puzzle.grid_random_clue()
    grid_puzzle.grid_print(play_mode=True)
    grid_puzzle.grid_copy(grid_user)

    play_grid(n, grid_answer, grid_puzzle, grid_user)

else:
    print('Unknown mode. Mode can be solver or create or play', file=sys.stderr)
    exit(4)
