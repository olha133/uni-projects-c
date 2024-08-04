#include <stdio.h>
#include "k.h"
#include "k.c"
#include "ui.h"
#include "ui.c"
#include "hof.h"
#include "hof.c"


int main() {
    struct game game = {
        .board = {
            {' ', 'C', ' ', 'G'},
            {' ', 'J', ' ', 'F'},
            {'G', 'J', 'J', ' '},
            {' ', ' ', 'C', 'J'}},
        .score = 8288};
    int dy;
    int dx;
    do {
        render(game);
        printf("Move: ");
        scanf("%d %d", & dy, & dx);
        printf("YES OR NO: %d\n", update( & game, dy, dx));

        add_random_tile( & game); // for arena
        if (is_game_won(game)) {
            printf("YOU WON\n"); // for arena
            break;
        }
    } while (is_move_possible(game));

    struct player ls[5] = {
        {.score = 1915, .name = "Olia"},
        {.score = 876, .name = "Mark"},
        {.score = 23489, .name = "Dasha"},
        {.score = 3938, .name = "Sasha"},
        {.score = 98, .name = "Maks"},
    };
    struct player hof[10];
    printf("Result of lod: %d\n", load(hof));
    for (int i = 0; i < load(hof); i++) {
        printf("%s %d\n", hof[i].name, hof[i].score);
    }

    printf("%d", save(ls, 5));
    // 2

    struct player list[10];
    struct player player = {
        .name = "john",
        .score = 80000
    };
    int size = load(list);
    for (int x = 0; x < size; x++) {
        printf("%s %d\n", list[x].name, list[x].score);
    }
    bool result = add_player(list, & size, player);
    printf("Result: %d\n", result);
    for (int x = 0; x < size; x++) {
        printf("%s %d\n", list[x].name, list[x].score);
    }
    return 0;
}