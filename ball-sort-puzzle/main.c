#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void generator(const int rows, const int columns, char field[rows][columns]);
void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y);
bool check(const int rows, const int columns, char field[rows][columns]);
void game_field(const int rows, const int columns, char field[rows][columns]);
void ball_sort_puzzle(const int rows, const int columns, char field[rows][columns]);

int main() {

    int rows = 6;
    int columns = 5;
    char field[rows][columns];
    ball_sort_puzzle(rows, columns, field);
}
