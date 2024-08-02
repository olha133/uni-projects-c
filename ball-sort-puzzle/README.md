# Ball Sort Puzzle

This project is a ball sort puzzle game implemented in C. The game involves moving characters around a playing field following specific rules. The main functionality is provided by functions located in the `ballsortpuzzle.c` file, with their declarations in the `ballsortpuzzle.h` file. The main program is located in the `main.c` file.

## Function Descriptions

### `void generator(const int rows, const int columns, char field[rows][columns])`

**Parameters:**
- `const int rows` - Number of rows in the field
- `const int columns` - Number of columns in the array
- `char field[rows][columns]` - Two-dimensional array in which the characters will be stored

**Description:**
This function randomly generates a two-dimensional array of characters. The generated array must follow these rules:
- There must always be 2 empty columns.
- Each character can occur just as many times as the height of the column (which is the number of rows).
- Characters must be generated randomly, with no already filled columns.

**Notes:**
- The player (foreground) indexes from the number 1, and from their point of view, the playing field starts at the top left.
- The game (background) indexes from number 0, and from its point of view, the playing field also starts at the top left.

### `void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)`

**Parameters:**
- `const int rows` - Number of rows in the array
- `const int columns` - Number of columns in the array
- `char field[rows][columns]` - The array in which the characters are stored
- `int x` - Number of the column from which we want to move the character
- `int y` - Number of the column where we want to move the character

**Description:**
This function is used to move characters around the board. It ensures the character cannot be moved to another character other than itself. It also handles situations where the character is moved to the bottom of the column. If a player attempts to make an unauthorized move, the function will do nothing and warn the player.

**Notes:**
- When placing a character in a column, it must be placed at the bottom of the column.
- A player must not choose the same column to move, for example from column 2 to column 2.

### `bool check(const int rows, const int columns, char field[rows][columns])`

**Parameters:**
- `const int rows` - Number of rows in the field
- `const int columns` - Number of columns in the array
- `char field[rows][columns]` - The array in which the characters are stored

**Description:**
This function returns `true` if all characters in the columns are the same. It returns `false` if all characters are not the same. If there is only one character in a column, this situation is not considered to be the end state of the game. All characters in each column must be the same up to the top.

### `void ball_sort_puzzle()`

**Description:**
This function controls the entire operation of the game. It uses the `check()`, `down_possible()`, `generator()`, and `game_field()` functions. First, the game field is generated, then it is rendered, and a user interface is added in the form of a dialog. The player is asked for the column to move the character from and to, and this information is passed to the `down_possible()` function. After each move, the game state is checked with the `check()` function.

## Files

- `ballsortpuzzle.c` - Contains the implementation of all the game functions.
- `ballsortpuzzle.h` - Contains the declarations of the game functions.
- `main.c` - Contains the main program that runs the game.

## How to Compile and Run

1. Compile the program:
   ```sh
   gcc -o ballsortpuzzle main.c ballsortpuzzle.c
2. Run the program:
   ```sh
   ./ballsortpuzzle
