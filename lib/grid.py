"""
grid module
a *grid* is a NxN 2d array of tiles used to represent a sudoku
"""
import sys
import math
import random
import unittest
from tile import *
sys.path.insert(0, '../main')
from sudoku_gui import *


class Grid:
    def __init__(self, n):
        """
        create a new empty grid

        :param n: the size of the sudoku
        """
        self.n = n
        self.table = []

        for i in range(n):
            self.table.append([])
            for j in range(n):
                self.table[i].append(Tile())

    def grid_set_tile(self, i, j, confirmed, value):
        """
        set a given tile in a grid
        will do nothing if the indices are out of range

        :param i: i coordinate of tile
        :param j: j coordinate of tile
        :param confirmed: bool value to be set
        :param value: value to be set
        :return: none
        """
        if (i >= 0) and (i < self.n) and (j >= 0) and (j < self.n):
            self.table[i][j].tile_set(confirmed, value)

    def grid_get_value(self, i, j):
        """
        return the value of a given tile in a grid

        :param i: i coordinate of tile
        :param j: j coordinate of tile
        :return: value of the tile, -1 if the indices are out of range
        """
        if (i >= 0) and (i < self.n) and (j >= 0) and (j < self.n):
            return self.table[i][j].tile_value()
        return -1

    def grid_get_status(self, i, j):
        """
        return the status of a given tile in a grid

        :param i: i coordinate of tile
        :param j: j coordinate of tile
        :return: status of the tile, False if the indices are out of range
        """
        if (i >= 0) and (i < self.n) and (j >= 0) and (j < self.n):
            return self.table[i][j].tile_status()
        return False

    def grid_print(self, play_mode=False):
        """
        print the grid in one of two formats according to the mode

        :param play_mode: if true, print in play mode with coordinate markings
        :return: none
        """
        n = self.n
        # find out how many white spaces a number needs
        length = len(str(n))

        # print the format for play mode
        if play_mode:
            for i in range(length):
                print(" ", end="")
            print(" |", end="")
            for i in range(n):
                print(f"{i:{length}} ", end="")
            print()
            for i in range((length + 1) * n + length + 2):
                print("-", end="")
            print()

        # print the grid itself
        for i in range(n):
            if play_mode:
                print(f"{i:{length}} |", end="")

            for j in range(n):
                self.table[i][j].tile_print(n)
                print(" ", end="")
            print()

    def grid_load(self):
        """
        load a grid from stdin

        :return: true if the grid is loaded successfully, false otherwise
        """
        n = self.n

        # prompt user
        print("Enter your sudoku board:")

        # loop through input
        for i in range(n):
            line = input()
            try:
                numbers = line.split()
                for j in range(n):
                    num = int(numbers[j])
                    if (num > 0) and (num <= n):
                        self.grid_set_tile(i, j, True, num)
                    else:
                        self.grid_set_tile(i, j, False, 0)
            except Exception as e:
                print("Invalid format of entered sudoku board", file=sys.stderr)
                print(e, file=sys.stderr)
                return False

        return True

    def grid_load_string(self, s):
        """
        load a grid from string (row1 row2 row3 ...)

        :param s: string representation of white-space separated sudoku values
        :return: true if the grid is loaded successfully, false otherwise
        """
        n = self.n
        s_split = s.split()
        try:
            for i in range(n):
                for j in range(n):
                    num = int(s_split[i*n+j])
                    if (num > 0) and (num <= n):
                        self.grid_set_tile(i, j, True, num)
                    elif num > n:
                        return False
                    else:
                        self.grid_set_tile(i, j, False, 0)

        except Exception as e:
            print("Invalid format of string representation of sudoku board", file=sys.stderr)
            print(e, file=sys.stderr)
            return False

        return True

    def valid_digits(self, i, j):
        """
        find the potentially valid candidates of a tile

        :param i: i coordinate of the tile
        :param j: j coordinate of the tile
        :return: array of valid candidates
        """
        n = self.n
        invalid = set()
        valid = []

        # add invalid digits to set from row and col
        for k in range(n):
            invalid.add(self.grid_get_value(i, k))
            invalid.add(self.grid_get_value(k, j))

        # add invalid digits to set from block
        box_size = int(math.sqrt(n))
        quad_x = i - (i % box_size)
        for k in range(quad_x, quad_x+box_size):
            quad_y = j - (j % box_size)
            for h in range(quad_y, quad_y+box_size):
                invalid.add(self.grid_get_value(k, h))

        # add the valid digits to array
        for k in range(n+1):
            if k not in invalid:
                valid.append(k)

        return valid

    def grid_solve_helper(self, i, j, sol, grid_frame=None):
        """
        helper function for grid_solve

        :param i: i coordinate of the tile
        :param j: j coordinate of the tile
        :param sol: number of solutions
        :param grid_frame: the grid frame to draw on, default to none (if not in GUI)
        :return: true if a solution is found with the current tile value, false otherwise
        """
        n = self.n
        if j >= n:
            if i == n-1:  # reached the last tile of the grid
                sol += 1  # increment number of solutions
                return sol > 1, sol  # done if multiple solutions found
            else:
                i += 1
                j = 0

        # skip the tile if it is confirmed
        if self.grid_get_status(i, j):
            flag, sol = self.grid_solve_helper(i, j+1, sol, grid_frame)
            return flag, sol

        # get valid candidates for the tile
        valid = self.valid_digits(i, j)

        # if no valid candidates, backtrack
        if len(valid) == 0:
            self.grid_set_tile(i, j, False, 0)

            if grid_frame is not None and sol < 1:  # draw tile
                grid_frame.after(50)
                grid_frame.controller.update()
                grid_frame.insert_a_tile(i, j, 0)
            return False, sol

        # randomly pick a candidate
        k = random.randint(0, len(valid)-1)
        val = valid.pop(k)
        self.grid_set_tile(i, j, False, val)

        if grid_frame is not None and sol < 1:  # draw tile
            grid_frame.after(50)
            grid_frame.controller.update()
            grid_frame.insert_a_tile(i, j, val)

        # while there's no solution for the next tile, try different candidates
        flag, sol = self.grid_solve_helper(i, j+1, sol, grid_frame)
        while not flag:
            # if the no valid candidates, backtrack
            if len(valid) == 0:
                self.grid_set_tile(i, j, False, 0)

                if grid_frame is not None and sol < 1:  # draw tile
                    grid_frame.after(50)
                    grid_frame.controller.update()
                    grid_frame.insert_a_tile(i, j, 0)
                return False, sol

            # randomly pick a candidate
            k = random.randint(0, len(valid)-1)
            val = valid.pop(k)
            self.grid_set_tile(i, j, False, val)

            if grid_frame is not None and sol < 1:  # draw tile
                grid_frame.after(50)
                grid_frame.controller.update()
                grid_frame.insert_a_tile(i, j, val)

            flag, sol = self.grid_solve_helper(i, j+1, sol, grid_frame)

        return True, sol

    def grid_solve(self, grid_frame=None):
        """
        solve a sudoku grid

        :param grid_frame: the grid frame to draw on, default to none (if not in GUI)
        :return: 0 if no solutions are found, 1 if a unique solution is found, 2 if multiple solutions
        """
        _, sol = self.grid_solve_helper(0, 0, 0, grid_frame)
        if sol == 1:
            self.grid_solve_helper(0, 0, 1, grid_frame)
            return 1

        return sol

    def grid_empty_cnt(self):
        """
        return the count of empty tiles in a grid

        :return: the count of empty tiles
        """
        cnt = 0
        n = self.n
        for i in range(n):
            for j in range(n):
                if self.grid_get_value(i, j) == 0:
                    cnt += 1

        return cnt

    def grid_copy(self, other):
        """
        copy the contents of self grid to other grid

        :param other: target grid
        :return: none
        """
        assert isinstance(other, Grid), "grid_copy: param is not a grid\n"
        if self.n != other.n:
            print("grid_copy: dimensions do not match", file=sys.stderr)
        else:
            for i in range(self.n):
                for j in range(self.n):
                    other.grid_set_tile(i, j, self.grid_get_status(i, j), self.grid_get_value(i, j))

    def grid_random_clue(self, pb_frame=None):
        """
        randomly set tiles to zero in a complete grid to produce a sudoku puzzle
        will do nothing if the grid is already incomplete

        :return: none
        """
        if self.grid_empty_cnt() > 0:
            return

        n = self.n
        # set existing tiles to confirmed
        for i in range(n):
            for j in range(n):
                self.grid_set_tile(i, j, True, self.grid_get_value(i, j))

        total_cnt = n * n
        pos = list(range(total_cnt))  # position array of indices

        empty_cnt = 0
        grid_temp = Grid(n)  # a backup grid to store the current grid
        for k in range(total_cnt):
            # randomly select a tile
            h = random.randint(0, len(pos)-1)
            val = pos.pop(h)
            i = int(val/n)
            j = val % n

            self.grid_copy(grid_temp)  # copy the current grid to the backup
            grid_temp.grid_set_tile(i, j, False, 0)  # set a randomly selected tile to 0
            # if unique solution, set the tile to 0 in the original grid
            if grid_temp.grid_solve() == 1:
                self.grid_set_tile(i, j, False, 0)
                empty_cnt += 1

            if pb_frame is not None:
                pb_frame.update_progress((k+1)/total_cnt*100)

    def grid_cmp(self, other):
        """
        compare the value of two grids

        :param other: the other grid
        :return: true if the values are the same, false otherwise
        """
        assert isinstance(other, Grid), "grid_cmp: param is not a grid\n"
        if self.n != other.n:
            return False
        else:
            for i in range(self.n):
                for j in range(self.n):
                    if self.grid_get_value(i, j) != other.grid_get_value(i, j):
                        return False

        return True


# Unit test
class TestGrid(unittest.TestCase):
    def test_numbers(self):
        grid = Grid(9)
        self.assertEqual(grid.grid_solve(), 2)
        grid.grid_random_clue()
        self.assertEqual(grid.grid_solve(), 1)

    def test_load(self):
        grid = Grid(4)
        grid.grid_load_string("1 0 3 4 4 3 0 0 2 0 1 3 0 1 0 2")
        self.assertEqual(grid.grid_get_value(2, 2), 1)
        self.assertEqual(grid.grid_get_status(2, 2), True)
        grid.grid_print()
        self.assertEqual(grid.grid_solve(), 1)
        grid.grid_print()


if __name__ == '__main':
    unittest.main()

