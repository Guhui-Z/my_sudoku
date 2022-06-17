import tkinter as tk


# container that holds everything 
root = tk.Tk()
root.title("Sudoku")

canvas = tk.Canvas(root, height=500, width=500)
canvas.grid()

#functions

"""
It reads the solved.txt file and updates the GUI with the solved values
"""
def solve_board():
   
    #delete entries
    for i in range(0, len(entries)):
        entries[i].delete(0)

    # update grid from solver output 

    file = open("solved.txt", "r")
    i = 0
    while i != len(entries):
        e = file.read(1)
        if e != ' ' and e != '\n':
            root.after(10)
            root.update()
            entries[i].insert(0, e)
            entries[i].config({"background" : "grey"})
            root.after(10)
            root.update()
            entries[i].config({"background" : "white"})
            i+=1
    
    file.close()

# buttons
solve = tk.Button(root, text="Solve", activebackground='gray', fg='red', command=solve_board)
solve.grid()



# Creating a grid of 81 cells, each with an entry box.
entries = []
N = 9
for i in range(1,N+1):
    for j in range(1,N+1):
        if ((i in (1,2,3,7,8,9)) and j in (4,5,6)  or (i in (4,5,6) and j in (1,2,3,7,8,9) )): 
            color="green"  
        else:
            color="white"
        cell = tk.Frame(canvas, highlightbackground=color, highlightcolor=color, highlightthickness=2, 
                        width=50, height=50, padx=3, pady=3, background='grey')
        cell.grid(row=i, column=j)

        entry = tk.Entry(cell, justify='center')
        entry.place(height=40, width=40)
        entries.append(entry)


#fill in grid from file
file = open("start.txt", "r")

i = 0
while i != len(entries):
    e = file.read(1)
    if e != ' ' and e != '\n':
        if e != '0':
            entries[i].insert(0, e)
        entries[i].config({"background" : "grey"})
        root.after(10)
        root.update()
        entries[i].config({"background" : "white"})
        if e == '0':
            entries[i].config({"foreground": "red"})
        i+=1
 
file.close()




root.mainloop()