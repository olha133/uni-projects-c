# Arduino Mastermind

## Overview

**Arduino Mastermind** is an implementation of the classic code-breaking game, **Mastermind**, using an Arduino microcontroller. The game is designed to challenge players to guess a hidden number combination within a limited number of attempts. It features interactive gameplay with buttons, an LCD display, and RGB LEDs for feedback.

---

## Rules of the Game

1. At the beginning of the game, a secret combination of colored pins is placed under the "roof" by the first player (the game logic in this case).
    - Typically, the combination consists of **4 pins**, but this can vary based on difficulty.
2. The second player’s goal is to **guess the combination** (both the numbers and their order).
3. After each guess, the first player evaluates it:
    - For each correct digit in the correct position, the player receives a **red peg**.
    - For each correct digit in the wrong position, the player receives a **blue peg**.
4. The guessing player **wins** by guessing the entire combination (receiving 4 red and blue pegs).
5. The guessing player **loses** if they fail to guess the combination within the allowed number of attempts.

---

## Sample Game

To understand gameplay, here’s an example sequence:

**Secret combination**: `9347`

| Attempt | Guess  | Feedback |
|---------|--------|----------|
| 1       | `1234` | `0A2B`   |
| 2       | `5678` | `0A1B`   |
| 3       | `9012` | `1A0B`   |
| 4       | `9340` | `3A0B`   |
| 5       | `9345` | `3A0B`   |
| 6       | `9346` | `3A0B`   |
| 7       | `9347` | `4A0B`   |

**Feedback Legend:**
- **A** = Correct digit and correct position (red peg).
- **B** = Correct digit but wrong position (blue peg).

---

## Game Interaction

The game provides interactive communication via a **two-line LCD display** and user input through buttons.

### Example Gameplay Walkthrough

1. **Welcome Screen**  
   When the game powers on, the following message is displayed:  
   ```text
   Welcome to MasterMind
   Guess secret code.
2. **Starting the Game**   
   The player is prompted to enter their guess:
   ```text
   Try it now:
   Your guess: 0000
3. **Adjusting the Guess**   
   Players use the buttons connected to BTN_1_PIN and BTN_2_PIN to adjust each digit of their guess. The LCD updates in real-time:
   ```text
   Try it now:
   Your guess: 1234
4. **Confirming the Guess**   
   When the player presses the button connected to BTN_ENTER_PIN, the game evaluates the guess. The result is displayed on the LCD, and the RGB LEDs provide visual feedback:
   ```text
   01: 1234 0A2B
   Your guess: 0000
5. **Subsequent Guesses**     
   After each evaluation, the player is prompted to enter the next guess:
   ```text
   02: 5678 0A1B
   Your guess: 0000
6. **Reviewing History**   
   Players can review their guess history by holding down a combination of buttons. The LCD shows the previous moves, and the RGB LEDs indicate the feedback for those moves:
   ```text
   01: 1234 0A2B
   Your guess: 0000
# Arduino Mastermind Modules

## LCD Module

This module manages the LCD display functionality. Its performance depends on the specific type of LCD display used, and it will not be directly checked by external reviewers. All related functions and their definitions can be found in the `lcd_wrapper.h` header file.

### Key Function: `lcd_init()`

- **Purpose**: Initializes the LCD display.
- **Usage**: Call this function as needed from the `setup()` function.
- **Notes**:  
  - If your library requires global variables for LCD functionality, declare them in the `lcd_wrapper.cpp` file.  
  - All work and function calls related to the LCD display should be implemented exclusively in the `lcd_wrapper.cpp` file (module).

---

## Mastermind Module

This module contains the core logic for the Mastermind game.

### Task #1: Function `generate_code()`

This function generates the secret code that the player needs to guess. The generated code consists of digits and adheres to the specified rules.

#### Parameters:
- `bool repeat`  
  - If `true`, digits in the code can be repeated.  
  - If `false`, digits cannot repeat.
- `int length`  
  - Specifies the length of the generated code.  
  - If `length < 1`, the function returns `NULL`.

#### Return Value:
- A reference to the generated string if successful.  
- `NULL` if the string cannot be generated (e.g., invalid parameters).  
- `NULL` if `repeat = false` and `length > 10` (since digits cannot repeat).

---

### Example Usage

```cpp
char* code = NULL;

// Code will be generated as a sequence of non-repeating digits with a length of 4
code = generate_code(false, 4);
// code = "1234";
free(code);

// Code will be generated as a sequence of repeating digits with a length of 5
code = generate_code(true, 5);
// code = "65656";
free(code);

// No code will be generated (invalid length)
code = generate_code(true, -10);
// code = NULL;
```
### Task #2: Function `get_score()`

The `get_score()` function evaluates the player's current guess by determining:
1. The number of digits correctly guessed in the correct positions (`peg_a`).
2. The number of digits correctly guessed but in incorrect positions (`peg_b`).

#### Parameters
- `char* secret`  
  Reference to the secret code that the player needs to guess. (Input parameter)
- `char* guess`  
  Reference to the player's current guess. (Input parameter)
- `int* peg_a`  
  Reference to the number of digits guessed correctly in the correct positions. (Output parameter)
- `int* peg_b`  
  Reference to the number of digits guessed correctly but in incorrect positions. (Output parameter)

#### Return Value
- The function does not return any value.

### Example Usage
```cpp
int peg_a;
int peg_b;

get_score("9347", "1234", &peg_a, &peg_b);
assert(peg_a == 0 && peg_b == 2);

get_score("9347", "9348", &peg_a, &peg_b);
assert(peg_a == 3 && peg_b == 0);

get_score("9347", "1256", &peg_a, &peg_b);
assert(peg_a == 0 && peg_b == 0);

get_score("9347", "9436", &peg_a, &peg_b);
assert(peg_a == 1 && peg_b == 2);
```
#### Task #3: Functions `turn_off_leds()` and `render_leds()`

#### Overview
These functions are designed to control RGB LEDs during gameplay:

- **`turn_off_leds()`**: Turns off all RGB LEDs.
- **`render_leds()`**: Lights up RGB LEDs based on the player's guess evaluation:
  - **Red LED**: Lights up for each digit guessed correctly in the correct position.
  - **Blue LED**: Lights up for each digit guessed correctly but in the wrong position.

#### Function: `turn_off_leds()`
- **Purpose**: Turns off all RGB LEDs.
- **Parameters**: None.
- **Return Value**: None.

---

#### Function: `render_leds()`
- **Purpose**: Lights up RGB LEDs to reflect the evaluation of the player's guess.

#### Parameters
- `const int peg_a`  
  Number of digits guessed correctly in the correct position.
- `const int peg_b`  
  Number of digits guessed correctly but in the wrong position.

#### Return Value
- The function does not return any value.

---

### Note
- LEDs are not associated with specific digit positions. The player cannot deduce positional information from the LEDs. For example, the first RGB LED lighting up does **not** mean the first digit was guessed correctly.

---

### Example Usage
```cpp
turn_off_leds();

render_leds(2, 1);
// Two LEDs will light up red, one will light up blue, and the remaining LEDs will remain off.
```
#### Task #4: Function `render_history()`

#### Overview
The `render_history()` function is used to display a specific entry from the history of guesses along with its evaluation.

---

#### Parameters
- **`char* secret`**  
  Reference to the number combination to be guessed. (Input parameter)

- **`char** history`**  
  Reference to the history of guesses.

- **`const int entry`**  
  The index of the position in the history to be displayed.

---

#### Return Value
The function does not return any value.

---

### Example Usage
```cpp
// Let's have the following history dynamically allocated and initialized
char** history = {
    "1234",
    "5678",
    "9012"
};

// Then we can render it
render_history("9347", history, 2);
// Renders and evaluates the guess "9012"
```
#### Task #5: Function `play_game()`

#### Overview
The `play_game()` function represents the entire game process, from start to finish. It includes the game loop within itself and does not rely on the Arduino `loop()` function. This design avoids the need for excessive use of global variables, promoting cleaner and more maintainable code.

---

#### Parameters
- **`char* secret`**  
  A reference to a string representing the secret code to be guessed in the current game.

---

#### Return Value
The function does not return any value.

---

### Example Usage
```cpp
void loop() {
    // Generate a secret code with no repeating digits, length 4
    char* code = generate_code(false, 4);

    // Play the game with the generated code
    play_game(code);

    // Free the allocated memory for the code
    free(code);
}
```
