#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "hof.h"

void sort_list(struct player list[], int size);
void sort_list(struct player list[], int size) {
    struct player tempor;
    // www.cprogrammingnotes.com/question/sorting-structure-array.html
    for (int y = 0; y < size - 1; y++) {
        for (int x = 0; x < (size - y - 1); x++) {
            if (list[x].score < list[x + 1].score) {
                tempor = list[x];
                list[x] = list[x + 1];
                list[x + 1] = tempor;
            }
            if (list[x].score == list[x + 1].score) {
                tempor = list[x];
                list[x] = list[x + 1];
                list[x + 1] = tempor;
            }
        }
    }
}

int load(struct player list[]) {
    FILE * fl = fopen(HOF_FILE, "r");
    if (fl == NULL) {
        return -1;
    }
    int long_of;
    if (fl != NULL) {
        fseek(fl, 0, SEEK_END);
        long_of = (int) ftell(fl);
        if (long_of == 0) {
            fclose(fl);
            return 0;
        }
    }
    fseek(fl, 0, SEEK_SET);
    int size = 0;
    char c;
    for (c = (char) getc(fl); c != EOF; c = (char) getc(fl)) {
        if (c == '\n') {
            size += 1;
        }
    }
    if (size > 10) {
        size = 10;
    }
    fseek(fl, 0, SEEK_SET);
    for (int i = 0; i < size; i++) {
        fscanf(fl, "%s %d", list[i].name, & list[i].score);
    }

    fclose(fl);
    sort_list(list, size);
    return size;
}
bool save(const struct player list[], int size) {
    FILE * fl = fopen(HOF_FILE, "w");
    if (fl == NULL) {
        return false;
    }
    for (int x = 0; x < size; x++) {
        fprintf(fl, "%s %d\n", list[x].name, list[x].score);
    }

    fclose(fl);
    return true;
}

bool add_player(struct player list[], int * size,
    const struct player player) {
    int t = 0;

    if ( * size < 10) {
        strcpy(list[ * size].name, player.name);
        list[ * size].score = player.score;
        * size += 1;
        sort_list(list, * size);
        t = 1;
    } else if ( * size == 10) {
        for (int x = 0; x < 10; x++) {
            if (player.score >= list[x].score) { // find out if score is big enought
                strcpy(list[9].name, player.name);
                list[9].score = player.score;
                sort_list(list, * size);
                t = 1;
                break;
            } else {
                t = 0;
            }
        }
    }
    return t;
}