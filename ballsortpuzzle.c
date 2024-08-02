#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ballsortpuzzle.h"


void generator(const int rows,
    const int columns, char field[rows][columns]) {
    srand(time(NULL));

    char symbol[10][rows];

    for (int x = 0; x < rows; x++) {
        symbol[0][x] = '@';
        symbol[1][x] = '*';
        symbol[2][x] = '+';
        symbol[3][x] = '^';
        symbol[4][x] = '#';
        symbol[5][x] = '&';
        symbol[6][x] = '>';
        symbol[7][x] = '<';
        symbol[8][x] = '=';
        symbol[9][x] = '~';
    }

    int free_space1 = rand() % columns;

    int free_space2;

    do {
        free_space2 = rand() % columns;
    } while (free_space1 == free_space2);

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            if (x == free_space1 || x == free_space2) {
                field[y][x] = ' ';
                continue;
            }
            int a;
            int b;
            do {
                a = rand() % (columns - 2);
                b = rand() % rows;
                field[y][x] = symbol[a][b];
            } while (symbol[a][b] == '_');
            symbol[a][b] = '_';
        }
    }
}

void down_possible(const int rows,
    const int columns, char field[rows][columns], int x, int y) {

    int symbolX;
    int t = 0;
    for (int hor = 0; hor < rows; hor++) {
        if (field[hor][x - 1] != ' ') {
            symbolX = hor;
            break;
        }
        if (hor == rows - 1) {
            t = 1;
            break;
        }
    }

    if (t == 0) {
        for (int hor2 = 0; hor2 < rows; hor2++) {
            if (field[hor2][y - 1] != ' ') {
                if (field[hor2][y - 1] == field[symbolX][x - 1] && hor2 > 0) {
                    field[hor2 - 1][y - 1] = field[symbolX][x - 1];
                    field[symbolX][x - 1] = ' ';
                    break;
                } else if (field[hor2][y - 1] != field[symbolX][x - 1]) {
                    t = 1;
                    break;
                } else if (field[0][y - 1] != ' ') {
                    t = 1;
                    break;
                }
            }
            if (hor2 == rows - 1 && field[rows - 1][y - 1] == ' ') {
                field[hor2][y - 1] = field[symbolX][x - 1];
                field[symbolX][x - 1] = ' ';
            }
        }
    }
    if (t == 1) {
        printf("Can't move!\n");
    }
}

bool check(const int rows,
    const int columns, char field[rows][columns]) {
    int t = 0;
    int t2;

    for (int x = 0; x < columns; x++) {
        t2 = 0;
        for (int y = 0; y < rows - 1; y++) {
            if (field[y][x] == ' ') {
                break;
            }

            if (field[y][x] == field[y + 1][x]) {
                t2++;

                if (t2 == rows - 1) {
                    t++;
                    break;
                }
            } else {
                return false;
            }
        }
    }

    if (t == columns - 2) {
        return true;
    }
    return false;
}

void game_field(const int rows,
    const int columns, char field[rows][columns]) {

    printf("\n    (_ _)");
    for (int i = 1; i < columns; i++) {
        printf("    (_ _)");
    }
    for (int i = 0; i < rows; i++) {
        printf("\n %d", i + 1);

        for (int j = 0; j < columns; j++) {
            printf("  | %c |  ", field[i][j]);
        }
    }
    printf("\n");
    for (int i = 0; i < columns; i++) {
        printf("    +_ _+");
    }
    printf("\n      1");
    for (int i = 1; i < columns; i++) {
        printf("        %d", i + 1);
    }
}

void ball_sort_puzzle(const int rows,
    const int columns, char field[rows][columns]) {
    generator(rows, columns, field);
    game_field(rows, columns, field);
    printf("\n\n\n");
    printf("Hi there!\nI tried very hard during the creation of this game, so I want you to play it.\n\nNow I will tell you all the Rules:\n\nYour task is to put all the same symbols into the flask.\n\nYou can not :\n1. Move a symbol into a flask with another symbol.\n2. Move a symbol into a full flask.\n3. Try to move the symbol from an empty flask.\n4. Move the symbol to the flask from which it was taken.\n\nHave a nice game!\n\n");
    while (!check(rows, columns, field)) {
        int x;
        int y;
        printf("\n\nWhat: ");

        scanf("%d", & x);

        printf("\nWhere: ");

        scanf("%d", & y);
        if (x == y) {
            printf("\nPosition can't be the same!");
        } else {
            down_possible(rows, columns, field, x, y);
            game_field(rows, columns, field);
        }
    }
    printf("\nYou won!\n");
}
