"""
Implements functions related to numbers
"""

import math
import unittest


def is_perfect_square(number):
    """
    check if number is perfect square
    modified from https://www.includehelp.com/c-programs/c-program-to-check-number-is-perfect-square-or-not.aspx

    :param number: a positive integer
    :return: bool: true if the number is a perfect square, false otherwise
    """
    assert isinstance(number, int) and number > 0, "is_perfect_square: invalid number\n"

    f_root = math.sqrt(number)
    i_root = int(f_root)

    return i_root == f_root


# Unit test
class TestNumbers(unittest.TestCase):
    def test_numbers(self):
        self.assertTrue(is_perfect_square(4))
        self.assertTrue(is_perfect_square(100))
        self.assertFalse(is_perfect_square(3))
        with self.assertRaises(AssertionError):
            is_perfect_square("0")
        with self.assertRaises(AssertionError):
            is_perfect_square(-1)
        with self.assertRaises(AssertionError):
            is_perfect_square(10.45)


if __name__ == '__main':
    unittest.main()
