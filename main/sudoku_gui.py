"""
The sudoku program with GUI

Guhui Zhang, 2022
"""

import sys
from math import sqrt
import random
import tkinter as tk
from tkinter.messagebox import showerror, showinfo
from tkinter import ttk
from tkmacosx import Button, Radiobutton
sys.path.insert(0, '../lib')
from grid import *


class App(tk.Tk):
    def __init__(self):
        super().__init__()
        #   declare style variable
        self.s = ttk.Style()
        #   assume that classic theme in use
        self.s.theme_use('classic')

        self.n = 0
        self.mode = ""

        self.title('Sudoku game & solver')
        self.config(bg="white")

        # button configs for later use
        self.button_options = dict(fg="white", bg="darkblue", overbackground="lightslategray", overforeground="white",
                              activebackground="darkblue", activeforeground="white", cursor="hand")

        self.window_width = 600
        self.window_height = 600
        # get the screen dimension
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()

        # find the center point
        center_x = int(screen_width/2 - self.window_width / 2)
        center_y = int(screen_height/2 - self.window_height / 2)

        # set the position of the window to the center of the screen
        self.geometry(f'{self.window_width}x{self.window_height}+{center_x}+{center_y}')

        self.resizable(False, False)

        # set image icon
        self.tk.call("wm", "iconphoto", self._w,
                     tk.PhotoImage(file="/Users/zhangguhui/CsCode/CS50/labs/my_sudoku/images/main_icon.gif"))

        # set background image
        bg_image = tk.PhotoImage(file="/Users/zhangguhui/CsCode/CS50/labs/my_sudoku/images/bg3.gif")
        bg_image = bg_image.subsample(4, 4)
        bg_label = tk.Label(self, image=bg_image)
        bg_label.grid(row=0, column=0) #place(x=0, y=0, relwidth=1, relheight=1)
        bg_label.image = bg_image

        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        self.frames = {"start_frame": StartFrame(self, self),
                       "size_frame": SizeFrame(self, self),
                       "solver_grid_frame": SolverGridFrame(self, self),
                       "play_grid_frame": PlayGridFrame(self, self)}
        self.show_frame("start_frame")

    def show_frame(self, frame_name):
        """
        show the appropriate frame
        :param frame_name: name of frame (key) in self.frames
        :return: none
        """
        self.frames[frame_name].update_frame()
        self.frames[frame_name].tkraise()


class StartFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)

        self.controller = controller
        self.mode = ""

        self.config(bg="white")
        self.rowconfigure(0, weight=1)
        self.rowconfigure(1, weight=1)
        self.rowconfigure(2, weight=1)
        self.rowconfigure(3, weight=1)

        # Label
        main_label = tk.Label(self, text="Sudoku game & solver", font=("herculanum", 40))
        main_label.grid(row=0, column=0, padx=20, pady=20)

        # new game button and explanation
        play_button_exp = tk.Label(self, text="Start a new sudoku game!", font=("herculanum", 20), fg="#202020")
        play_button_exp.grid(row=1, column=0, padx=5, pady=5)
        play_button = Button(self, text="New game", font=("herculanum", 25, "bold"),
                             command=lambda: self.switch_to_size_frame("play"), **self.controller.button_options)
        play_button.grid(row=2, column=0, padx=5, pady=5)

        # for spacing
        blank = tk.Label(self, text="")
        blank.grid(row=3, column=0, padx=5, pady=5)

        # solver button and explanation
        solver_button_exp = tk.Label(self, text="Input a sudoku puzzle \nand see how it is solved!", fg="#202020",
                                     font=("herculanum", 20))
        solver_button_exp.grid(row=4, column=0, padx=5, pady=5)
        solver_button = Button(self, text="Solver", font=("herculanum", 25, "bold"),
                               command=lambda: self.switch_to_size_frame("solver"), **self.controller.button_options)
        solver_button.grid(row=5, column=0, padx=5, pady=5)

        # grid self
        self.grid(row=0, column=0)

    def switch_to_size_frame(self, mode):
        """
        switch to size_frame by calling controller.show_frame()
        :param mode: play or solver
        :return: none
        """
        self.controller.mode = mode
        self.grid_remove()
        self.controller.show_frame("size_frame")

    def update_frame(self):
        pass


class SizeFrame(tk.LabelFrame):
    def __init__(self, container, controller):
        super().__init__(container)

        self.controller = controller

        self.config(text="Select size", font=("herculanum", 25))

        self.rowconfigure(index=0, weight=1)
        self.rowconfigure(index=1, weight=1)
        self.rowconfigure(index=2, weight=1)

        # radio buttons on a label frame
        sudoku_size_options = ['4', '9']#, '16']
        self.sudoku_size_var = tk.IntVar()
        for i, temp in enumerate(sudoku_size_options):
            radio = Radiobutton(self, text=temp, value=temp, variable=self.sudoku_size_var,
                                font=("herculanum", 20), fg='#000000')
            radio.grid(row=i, column=0, padx=5, pady=5)

        # confirm button
        confirm_button = Button(self, text="Confirm", font=("herculanum", 25, "bold"),
                                command=self.switch_to_grid_frame, **self.controller.button_options)
        confirm_button.grid(row=2, column=0, padx=5, pady=5, sticky=tk.E)

        # show grid
        self.grid(row=0, column=0, padx=50, pady=50)

    def switch_to_grid_frame(self):
        self.controller.n = int(self.sudoku_size_var.get())

        self.grid_remove()
        if self.controller.mode == "solver":
            self.controller.show_frame("solver_grid_frame")
        elif self.controller.mode == "play":
            self.controller.show_frame("play_grid_frame")

    def update_frame(self):
        pass


class SolverGridFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)
        self.controller = controller
        self.entries = []
        self.entry_string_vars = []

        self.grid(row=0, column=0)

    def update_frame(self):
        # quit button
        quit_button = Button(self, text="Quit", font=("herculanum", 22, "bold"),
                             command=self.controller.destroy, **self.controller.button_options)
        quit_button.grid(row=0, columnspan=2, pady=5, padx=5, sticky=tk.W)

        n = self.controller.n

        # initialize StringVar
        for i in range(n*n):
            self.entry_string_vars.append(tk.StringVar())

        # set up canvas
        margin = 4
        side = 50 if n == 4 else 40
        canvas_width = canvas_height = 2 * margin + side * n

        canvas = tk.Canvas(self, width=canvas_width, height=canvas_height, bg="white", highlightthickness=0)
        canvas.grid(row=1, columnspan=2, padx=5, pady=5)

        # draw lines
        for i in range(n+1):
            color = "gray" if i % sqrt(n) != 0 else "#CB6A08"
            lw = 1 if i % sqrt(n) != 0 else 2

            x0 = x1 = margin + i * side  # vertical
            y0 = margin
            y1 = canvas_height - margin
            canvas.create_line(x0, y0, x1, y1, fill=color, width=lw)

            x0 = margin
            y0 = y1 = margin + i * side  # horizontal
            x1 = canvas_width - margin
            canvas.create_line(x0, y0, x1, y1, fill=color, width=lw)

        # configure relief=flat entry
        # modified from https://stackoverflow.com/questions/44383730/how-to-get-flat-relief-entry-widget-in-python-ttk
        s = ttk.Style()
        s.theme_use('default')

        # configure relief
        s.configure('SOExample.TEntry', relief='flat', background="white")

        s.layout('SOExample.TEntry', [
            ('Entry.highlight', {
                'sticky': 'nswe',
                'children':
                    [('Entry.border', {
                        'border': '1',
                        'sticky': 'nswe',
                        'children':
                            [('Entry.padding', {
                                'sticky': 'nswe',
                                'children':
                                    [('Entry.textarea',
                                      {'sticky': 'nswe'})]
                            })]
                    })]
            })])

        # draw entries
        for i in range(n):
            for j in range(n):
                entry = ttk.Entry(canvas, width=2, font=("herculanum", 22), style='SOExample.TEntry', justify="center",
                                  textvariable=self.entry_string_vars[i*n+j])
                entry.grid(row=i, column=j)
                canvas.create_window(margin+(j+0.5)*side, margin+(i+.5)*side, window=entry)
                self.entries.append(entry)

        self.clear_sudoku()

        # solve button
        solve_button = Button(self, text="Solve for me", font=("herculanum", 25, "bold"),
                              command=self.solve_sudoku, **self.controller.button_options)
        solve_button.grid(row=2, column=0, pady=5, padx=5)

        # clear button
        clear_button = Button(self, text="Clear", font=("herculanum", 25, "bold"),
                              command=self.clear_sudoku, **self.controller.button_options)
        clear_button.grid(row=2, column=1, pady=5, padx=5)

        self.grid(row=0, column=0)

    def clear_sudoku(self):
        """
        clears the grid and fills it with zeros
        :return: none
        """
        n = self.controller.n
        for i in range(n*n):
            self.entries[i].delete(0, "end")
            self.entries[i].insert(0, "0")

    def solve_sudoku(self):
        """
        reads the grid by calling grid_load_string
        and solves the grid by calling grid_solve
        :return: none
        """
        n = self.controller.n
        input_grid = ' '.join([string_var.get() for string_var in self.entry_string_vars])
        my_grid = Grid(n)
        if not my_grid.grid_load_string(input_grid):
            showerror(title="Error", message="Check your inputs :)")
        else:
            if my_grid.grid_solve(self) == 0:
                showinfo(title="Info", message="No solution found :(")

    def insert_a_tile(self, i, j, num):
        """
        inserts a number into an entry
        :param i: i coordinate of the tile
        :param j: j coordinate of the tile
        :param num: the value of the tile
        :return: none
        """
        n = self.controller.n
        try:
            self.entries[i*n+j].delete(0, "end")
            self.entries[i*n+j].insert(0, num)
        except Exception as e:
            print(f"Error when inserting into entry ({i}, {j})", file=sys.stderr)
            print(e, file=sys.stderr)


class PlayGridFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)
        self.controller = controller
        self.n = self.controller.n
        self.entries = []
        self.entry_string_vars = []

        self.grid(row=0, column=0)

    def update_progress_label(self):
        """
        generate the progress bar label text
        :return: a string for the progress bar label
        """
        return f"Generating sudoku puzzle: {self.pb['value']:.1f}%"

    def update_progress(self, pb_value):
        """
        update the progress bar value and the progress bar label text
        :param pb_value: the progress bar value, given by grid.random_clue()
        :return: none
        """
        self.pb["value"] = pb_value
        self.pb_label["text"] = self.update_progress_label()
        self.controller.update()

    def update_frame(self):
        self.n = self.controller.n

        # progress bar
        self.pb = ttk.Progressbar(self, orient="horizontal", mode="determinate", length=200)
        self.pb.grid(row=0, column=0, padx=5, pady=5)

        # progress bar label
        self.pb_label = tk.Label(self, text=self.update_progress_label(), font=("herculanum", 25))
        self.pb_label.grid(row=1, column=0, padx=5, pady=5)

        self.update()

        # create a grid puzzle
        self.puzzle_grid = Grid(self.n)
        self.puzzle_grid.grid_solve()

        # save the answer to answer grid
        self.answer_grid = Grid(self.n)
        self.puzzle_grid.grid_copy(self.answer_grid)

        # generate grid puzzle
        self.puzzle_grid.grid_random_clue(self)

        # save the clues
        self.clues = [(i, j) for i in range(self.n) for j in range(self.n) if not self.puzzle_grid.grid_get_status(i, j)]

        self.grid(row=0, column=0)

        self.draw_sudoku()

    def draw_sudoku(self):
        self.pb.destroy()
        self.pb_label.destroy()

        # initialize StringVar
        for i in range(self.n*self.n):
            self.entry_string_vars.append(tk.StringVar())

        # set up canvas
        margin = 4
        side = 50 if self.n == 4 else 40
        canvas_width = canvas_height = 2 * margin + side * self.n

        canvas = tk.Canvas(self, width=canvas_width, height=canvas_height, bg="white", highlightthickness=0)
        canvas.grid(row=1, columnspan=2, padx=5, pady=5)

        # draw lines
        for i in range(self.n+1):
            color = "gray" if i % sqrt(self.n) != 0 else "#CB6A08"
            lw = 1 if i % sqrt(self.n) != 0 else 2

            x0 = x1 = margin + i * side  # vertical
            y0 = margin
            y1 = canvas_height - margin
            canvas.create_line(x0, y0, x1, y1, fill=color, width=lw)

            x0 = margin
            y0 = y1 = margin + i * side  # horizontal
            x1 = canvas_width - margin
            canvas.create_line(x0, y0, x1, y1, fill=color, width=lw)

        # configure relief=flat entry
        # modified from https://stackoverflow.com/questions/44383730/how-to-get-flat-relief-entry-widget-in-python-ttk
        s = ttk.Style()
        s.theme_use('default')

        # configure relief
        s.configure('Clue.TEntry', relief='flat', background="white", foreground="darkred")

        s.layout('Clue.TEntry', [
            ('Entry.highlight', {
                'sticky': 'nswe',
                'children':
                    [('Entry.border', {
                        'border': '1',
                        'sticky': 'nswe',
                        'children':
                            [('Entry.padding', {
                                'sticky': 'nswe',
                                'children':
                                    [('Entry.textarea',
                                      {'sticky': 'nswe'})]
                            })]
                    })]
            })])

        s.configure('Input.TEntry', relief='flat', background="white")
        s.layout('Input.TEntry', [
            ('Entry.highlight', {
                'sticky': 'nswe',
                'children':
                    [('Entry.border', {
                        'border': '1',
                        'sticky': 'nswe',
                        'children':
                            [('Entry.padding', {
                                'sticky': 'nswe',
                                'children':
                                    [('Entry.textarea',
                                      {'sticky': 'nswe'})]
                            })]
                    })]
            })])

        # draw entries
        for i in range(self.n):
            for j in range(self.n):
                num = self.puzzle_grid.grid_get_value(i, j)
                if num != 0:  # clue tile
                    entry = ttk.Entry(canvas, width=2, font=("herculanum", 20, "underline"), style='Clue.TEntry',
                                      justify="center", textvariable=self.entry_string_vars[i*self.n+j])
                    entry.grid(row=i, column=j)
                    canvas.create_window(margin+(j+0.5)*side, margin+(i+.5)*side, window=entry)
                    entry.delete(0, "end")
                    entry.insert(0, num)
                    entry.config(state="readonly")
                else:  # to be filled tile
                    entry = ttk.Entry(canvas, width=2, font=("herculanum", 20), style='Input.TEntry', justify="center",
                                      textvariable=self.entry_string_vars[i*self.n+j])

                    entry.grid(row=i, column=j)
                    canvas.create_window(margin+(j+0.5)*side, margin+(i+.5)*side, window=entry)
                    entry.delete(0, "end")
                    entry.insert(0, num)

                self.entries.append(entry)

        # clue button
        clue_button = Button(self, text="Reveal a tile", font=("herculanum", 25, "bold"),
                             command=self.reveal_clue, **self.controller.button_options)
        clue_button.grid(row=2, column=0, pady=5, padx=5)

        # clear button
        clear_button = Button(self, text="Clear", font=("herculanum", 25, "bold"),
                              command=self.clear_sudoku, **self.controller.button_options)
        clear_button.grid(row=2, column=1, pady=5, padx=5)

        # check button
        check_button = Button(self, text="Check answers", font=("herculanum", 25, "bold"),
                              command=self.check_sudoku, **self.controller.button_options)
        check_button.grid(row=3, column=0, pady=5, padx=5)

        # solve button
        solve_button = Button(self, text="Solve for me", font=("herculanum", 25, "bold"),
                              command=self.solve_sudoku, **self.controller.button_options)
        solve_button.grid(row=3, column=1, pady=5, padx=5)

        self.grid(row=0, column=0)

    def clear_sudoku(self):
        """
        clears the grid and fills it with zeros
        :return: none
        """
        for i in range(self.n):
            for j in range(self.n):
                self.entries[i*self.n+j].delete(0, "end")
                self.entries[i*self.n+j].insert(0, self.puzzle_grid.grid_get_value(i, j))

    def solve_sudoku(self):
        """
        reads the grid by calling grid_load_string
        and solves the grid by calling grid_solve
        :return: none
        """
        temp_grid = Grid(self.n)
        self.puzzle_grid.grid_copy(temp_grid)
        temp_grid.grid_print()
        temp_grid.grid_solve()
        temp_grid.grid_print()
        self.puzzle_grid.grid_copy(temp_grid)
        if temp_grid.grid_solve(self) == 0:
                showinfo(title="Info", message="No solution found :(")

    def insert_a_tile(self, i, j, num):
        """
        inserts a number into an entry
        :param i: i coordinate of the tile
        :param j: j coordinate of the tile
        :param num: the value of the tile
        :return: none
        """
        try:
            self.entries[i*self.n+j].delete(0, "end")
            self.entries[i*self.n+j].insert(0, num)
        except Exception as e:
            print(f"Error when inserting into entry ({i}, {j})", file=sys.stderr)
            print(e, file=sys.stderr)

    def check_sudoku(self):
        """
        checks whether the user_grid is correct
        :return: none
        """
        user_grid = Grid(self.n)
        input_grid = ' '.join([string_var.get() for string_var in self.entry_string_vars])
        if not user_grid.grid_load_string(input_grid):
            showerror(title="Error", message="Check your inputs :)")
        else:
            correct = True
            for i in range(self.n):
                for j in range(self.n):
                    if user_grid.grid_get_value(i, j) != self.answer_grid.grid_get_value(i, j):
                        self.entries[i*self.n+j].delete(0, "end")
                        self.entries[i*self.n+j].insert(0, 0)
                        correct = False

            if correct:
                showinfo(title="", message="Congratulations!\nYou solved the puzzle!!")
            else:
                showinfo(title="", message="Uh oh...\nIncorrect solution. We've kept the correct tiles. Try again!")

    def reveal_clue(self):
        """
        randomly selects a non confirmed tile and insert into its entry
        :return: none
        """
        temp = random.randint(0, len(self.clues)-1)
        i, j = self.clues.pop(temp)
        num = self.answer_grid.grid_get_value(i, j)
        self.insert_a_tile(i, j, num)


if __name__ == '__main__':
    app = App()

    app.mainloop()
