# My Sudoku UI design plan

## Landing page

- Title  
    "Sudoku game & solver"
- New game button
    - text: New game
    - command: ask for sudoku size
    - Explanation: Start a new sudoku game!
- Solver button
    - text: Solver
    - command: ask for sudoku size
    - Explanation: Input a sudoku puzzle and see how it is solved!
- Size radio button
    - options: 4, 9, 16 (solver only)
    - command: save selected size

## New game page

- N by N grid entry (?)
    - different colors for clue and user input
    - different thickness for tile borders
    - highlight when focused or active
    - command: insert user input, if it is valid; backspace is delete
- Clue button
    - text: Clue
    - image: light bulb
    - command: randomly reveals a tile
- Solve button:
    - text: Solve this for me
    - image: ?
    - command: solve the puzzle, same as solver
- Restart button:
    - text: New game
    - image: undo
    - command: ask for sudoku size
- message boxes:
    - invalid input
    - when completely filled, correct answer, New game button and Home button 
    - or incorrect answer

## Solver page

- N by N grid entry (?)
    - different colors for clue and user input
    - different thickness for tile borders
    - highlight when focused or active
    - command: insert user input, if it is valid; backspace is delete
- Solve button:
    - text: Solve this for me
    - image: ?
    - command: solve the puzzle