# Alpha-2048

Alpha-2048 is inspired by the classic game [2048](https://en.wikipedia.org/wiki/2048_(video_game)), with one key difference: instead of numbers, you play with letters on the tiles. The game is played on a 4x4 field, just like the original.

## How to Play
- **Objective**: The goal of the game is to merge tiles until you create a tile with the letter 'K'.
- **Tiles**: Each new turn begins with the generation of a random tile, either 'A' or 'B'.
- **Movement**: You can move tiles in four directions (up, down, left, right) by providing input through standard input. When moved, tiles slide as far as possible in the given direction. If two tiles with the same letter collide, they merge into the next letter in the alphabet. For example, two 'C' tiles merge to form a 'D' tile.
- **Scoring**: Players earn points each time tiles are merged. The exact scoring system is detailed below.

### Game Rules
1. Each move shifts all tiles in the selected direction as far as they can go.
2. Tiles merge if two tiles with the same letter collide, forming the next letter in the sequence (A → B → C...).
3. After each move, a new random tile ('A' or 'B') is added to the board.
4. The game ends when a tile with the letter 'K' appears on the board.
5. A merged tile cannot merge again in the same move.

## Game Ending
- **Win Condition**: The game is won when a tile with the letter 'K' appears on the board.
- **Loss Condition**: If no moves are possible and the 'K' tile has not been created, the game ends.

## Scoring
The player's score increases each time tiles merge. The scoring system rewards consecutive merges during a single move.

## Code Overview

### Module K
The main module of the game. It includes all necessary functions and data types to run Alpha-2048, including:
- **struct game**: A structure representing the game state.
- **update()**: Updates the board after each move.
- **is_move_possible()**: Checks if any moves are still possible.
- **is_game_won()**: Checks if the game has been won.
- **add_random_tile()**: Adds a random tile ('A' or 'B') to the board.

---


### SIZE Macro
- Defines the size of the game field as `4`.

---


### `struct game`
The `struct game` data type represents the current state of the game. It includes:
- `board`: A 2D array representing the game field.
- `score`: The current score of the player.

---


### `is_game_won(const struct game game)`
- **Parameters**: 
  - `const struct game game`: The current state of the game.
- **Returns**: 
  - `true` if the letter 'K' is on the board.
  - `false` otherwise.

### Example Code Snippets
```
// game is won
struct game game = {
    .board = {
        {'A', 'B', 'C', 'D'},
        {'E', 'F', 'G', 'H'},
        {'I', 'J', 'K', 'A'},
        {'B', 'C', 'D', 'E'}
    },
    .score = 0
};

printf("is won: %d\n", is_game_won(game));
// stdout: 1
```
```
// game is not won
struct game game = {
    .board = {
        {'A', ' ', ' ', ' '},
        {' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'A'},
        {'B', ' ', ' ', ' '}
    },
    .score = 0
};

printf("is won: %d\n", is_game_won(game));
// stdout: 0
```
### `bool is_move_possible(const struct game game)`
- **Parameters**:
  - `const struct game game`: The current state of the game represented as a `struct game`.
- **Returns**:
  - `true` if a valid move can still be made.
  - `false` if no further moves are possible.

This function checks whether the player can make any more moves on the board. If no moves are possible, the game is over.

---

### `bool update(struct game *game, int dy, int dx)`
- **Parameters**:
  - `struct game *game`: A reference to the current game state.
  - `int dy`: The movement in the y-axis, which can be:
    - `-1`: Move up.
    - `0`: No vertical movement.
    - `1`: Move down.
  - `int dx`: The movement in the x-axis, which can be:
    - `-1`: Move left.
    - `0`: No horizontal movement.
    - `1`: Move right.
- **Returns**:
  - `true` if the game state has changed (i.e., tiles have moved or merged).
  - `false` if the game state remains unchanged or the move was invalid (e.g., attempting to move in more than one direction or in no direction at all).

This function handles the game logic of moving the tiles. It checks if tiles should slide or merge based on the provided direction. Invalid moves are ignored, and the function will return `false` in such cases.

---

### `struct player`
This data type represents an entry in the **Hall of Fame** for the top ten players. It contains the following fields:
- **`name`**: The name of the player.
- **`score`**: The player's score achieved during the game.

---

### `int load(struct player list[])`
- **Parameters**:
  - `struct player list[]`: A reference to an array that holds the top ten players. The array has a fixed length of 10.
- **Returns**:
  - The number of players retrieved from the file (up to 10).
  - `-1` if there is an error while loading the file.

This function loads the Hall of Fame from a text file, storing the top ten players and their scores in the provided `list[]`. The file must follow the format:
```NAME SCORE```, where `NAME` is the player's name (a sequence of non-space characters) and `SCORE` is their score as an integer, separated by a space. The function returns the number of players loaded from the file, or `-1` if the loading fails.

---

### `bool save(struct player list[], int size)`
- **Parameters**:
  - `struct player list[]`: A reference to the current list of the top ten players. The list is represented as a one-dimensional array with a maximum of 10 entries of type `struct player`.
  - `int size`: The actual number of players in the Hall of Fame, which can be less than 10 if the Hall of Fame has fewer entries.
- **Returns**:
  - `true` if the Hall of Fame is successfully saved to disk.
  - `false` if the save operation fails.

---

### `bool add_player(struct player list[], int* size, const struct player player)`
- **Parameters**:
  - `struct player list[]`: A reference to the current list of the top ten players.
  - `int* size`: A pointer to the actual number of players in the Hall of Fame, which can be fewer than 10 if the Hall of Fame is not full.
  - `const struct player player`: The player to be added to the Hall of Fame, if their score qualifies them.
- **Returns**:
  - `true` if the player is successfully added to the Hall of Fame.
  - `false` if the player does not qualify for the Hall of Fame.

This function inserts a player into the Hall of Fame based on their score. If the player's score qualifies for the Hall of Fame, the list is updated to include the player in the correct order.

#### Rules for Adding a Player:
1. **Score Comparison**: The new player's score is compared to existing entries in the Hall of Fame. If the player has a score equal to or higher than any current entry, they will be inserted into the correct position.
2. **Tie-breaking**: If the new player's score is equal to an existing player's score, the new player is placed before the existing one.
3. **List Update**: If adding the new player causes the list to exceed 10 players, the lowest-ranked player (10th) is removed from the Hall of Fame.
4. **Size Update**: If the new player is successfully added, the size of the Hall of Fame (`*size`) is updated accordingly.
