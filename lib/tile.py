"""
tile module
a *tile* is a component of a grid
containing an integer and a boolean indicating if that tile is confirmed to be correct

Guhui Zhang, 2022
"""

class Tile:
    def __init__(self):
        self.confirmed = False
        self.value = 0

    def tile_print(self, n):
        """
        print formatted tile value

        :param n: the size of the sudoku
        :return: none
        """
        print(f"{self.value:n}", end="")

    def tile_set(self, confirmed, value):
        """
        set a tile's value and status

        :param confirmed: the bool to be set
        :param value: the int to be set
        :return: none
        """
        self.confirmed = confirmed
        self.value = value

    def tile_value(self):
        """
        get a tile's value

        :return: the tile's value
        """
        return self.value

    def tile_status(self):
        """
        get a tile's status

        :return: the tile's status (confirmed)
        """
        return self.confirmed

