#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "k.h"


void add_random_tile(struct game * game) {
    int row, col;
    // find random, but empty tile
    do {
        row = rand() % SIZE;
        col = rand() % SIZE;
    } while (game -> board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if (rand() % 2 == 0) {
        game -> board[row][col] = 'A';
    } else {
        game -> board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            if (game.board[y][x] == 'K') { // if there is any K - game is win
                return true;
            }
        }
    }
    return false;
}

bool is_move_possible(const struct game game) {
    for (size_t y = 0; y < SIZE; y++) {
        for (size_t x = 0; x < SIZE; x++) {
            if (game.board[y][x] == ' ') { // if there is ANY space - you can move
                return true;
            }
            if (x < SIZE - 1) { // is there is same letter in next position - you can move
                if (game.board[y][x] == game.board[y][x + 1]) {
                    return true;
                }
            }
            if (y < SIZE - 1) {
                if (game.board[y][x] == game.board[y + 1][x]) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool is_step_possible(struct game * game, int y, int x, int end_y, int end_x);

bool is_step_possible(struct game * game, int y, int x, int end_y, int end_x) { // check if we can make one step in NEEDED direction
    // we can't take a step beyond the board
    if (end_y < 0 || end_y >= SIZE || end_x < 0 || end_x >= SIZE) {
        return false;
    }
    // we can't step if there is another letter
    if ((game -> board[y][x] != game -> board[end_y][end_x]) && (game -> board[end_y][end_x] != ' ')) {
        return false;
    }
    return true;
}
bool update(struct game * game, int dy, int dx) {
    // check if correct values entered
    if ((dy != 0 && dx != 0) || (dy == 0 && dx == 0) || (dy < -1) || (dy > 1) || (dx < -1) || (dx > 1)) {
        return false;
    }
    // create a variable that will help as to do the for loops
    char alphabet[11] = {
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K'
    };
    int digits[11] = {
        2,
        4,
        8,
        16,
        32,
        64,
        128,
        256,
        512,
        1024,
        2048
    };
    int t = 0;
    int start_y = 0;
    int start_x = 0;
    int step_y = 1;
    int step_x = 1;
    if (dy == 1) { // DOWN
        start_y = SIZE - 1;
        step_y = -1;
    }
    if (dx == 1) { // RIGHT
        start_x = SIZE - 1;
        step_x = -1;
    }
    int move_more;
    do {
        int next_y = 0;
        int next_x = 0;
        move_more = 0;
        for (int y = start_y; y >= 0 && y < SIZE; y += step_y) {
            for (int x = start_x; x >= 0 && x < SIZE; x += step_x) {
                next_y = y + dy;
                next_x = x + dx;
                if (is_step_possible(game, y, x, next_y, next_x) && game -> board[y][x] != ' ') { // only if step is possible and this possition has letter you can move
                    if (game -> board[y][x] == game -> board[next_y][next_x] && isupper(game -> board[y][x]) && isupper(game -> board[next_y][next_x])) {
                        for (int z = 0; z < 10; z++) {
                            if (game -> board[y][x] == alphabet[z]) {

                                game -> board[next_y][next_x] = (alphabet[z + 1]);
                                game -> board[next_y][next_x] = (char) tolower(game -> board[next_y][next_x]);
                                game -> board[y][x] = ' ';
                                game -> score += digits[z + 1];
                            }
                        }
                    } else {
                        game -> board[next_y][next_x] = game -> board[y][x];
                        game -> board[y][x] = ' ';
                    }
                    move_more = 1;
                    t = 1;
                }
            }
        }
    } while (move_more);
    if (t) {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                game -> board[y][x] = (char) toupper(game -> board[y][x]);
            }
        }
    }
    return t;
}