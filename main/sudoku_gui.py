import sys
import tkinter as tk
from tkinter.messagebox import showerror
from tkinter import ttk, font
from tkmacosx import Button, Radiobutton


class App(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title('Sudoku game & solver')

        # button configs for later use
        self.button_options = dict(fg="white", bg="darkblue", overbackground="lightslategray", overforeground="white",
                              activebackground="darkblue", activeforeground="white", cursor="hand")

        window_width = 600
        window_height = 600
        # get the screen dimension
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()

        # find the center point
        center_x = int(screen_width/2 - window_width / 2)
        center_y = int(screen_height/2 - window_height / 2)

        # set the position of the window to the center of the screen
        self.geometry(f'{window_width}x{window_height}+{center_x}+{center_y}')

        self.resizable(False, False)
        self.tk.call("wm", "iconphoto", self._w,
                     tk.PhotoImage(file="/Users/zhangguhui/CsCode/CS50/labs/my_sudoku/images/main_icon.gif"))
        self.rowconfigure(0, weight=1)
        self.columnconfigure(0, weight=1)

        self.frames = {"start_frame": StartFrame(self, self), "size_frame": SizeFrame(self, self),
                       "solver_grid_frame": SolverGridFrame(self, self),
                       "play_grid_frame": PlayGridFrame(self, self)}
        self.show_frame("start_frame")

    def show_frame(self, frame_name):
        """
        show the appropriate frame
        :param frame_name: name of frame (key) in self.frames
        :return: none
        """
        self.frames[frame_name].tkraise()


class StartFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)

        self.controller = controller

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
        solver_button_exp = tk.Label(self, text="Input a sudoku puzzle and see how it is solved!", fg="#202020",
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
        self.grid_forget()
        self.controller.show_frame("size_frame")


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

        self.grid_forget()
        if self.controller.mode == "solver":
            self.controller.show_frame("solver_grid_frame")
        elif self.controller.mode == "play":
            self.controller.show_frame("play_grid_frame")


class SolverGridFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)

        self.controller = controller


class PlayGridFrame(tk.Frame):
    def __init__(self, container, controller):
        super().__init__(container)

        self.controller = controller


if __name__ == '__main__':
    app = App()

    app.mainloop()
