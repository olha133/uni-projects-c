#include <stdio.h>

int main(int argc, char * argv[]) {

    if (argc != 3) {
        return 1;
    }

    FILE * word = fopen(argv[1], "r");

    char array1[500]; // array1 with almost the same context but larger

    int letter = fgetc(word);
    int i = 0; // size of array2
    while (letter != EOF) { // copy input to array1
        array1[i] = letter;
        letter = fgetc(word);
        i++;
    }

    char array2[i]; // array2 with SAME context
    for (int z = 0; z < i; z++) {
        array2[z] = array1[z];
    }
    int y = 0;
    for (; y < i + 1; y++) { // find START for array3
        if (array2[y] == 'S' && array2[y + 1] == 'T' && array2[y + 2] == 'A' && array2[y + 3] == 'R' && array2[y + 4] == 'T') {
            if (array2[y + 5] == ' ') {
                y++;
            }
            break;
        }
    }

    int s = 0;
    for (; s < i + 1; s++) { // find STOP for array3
        if (array2[s] == 'S' && array2[s + 1] == 'T' && array2[s + 2] == 'O' && array2[s + 3] == 'P') {
            break;
        }
    }
    int size = s - (y + 5); // size for array3
    char array3[size]; // array with the same context from START to STOP
    for (int u = 0; u < size; u++) { // fill array3
        array3[u] = array2[y + 5];
        y++;
    }

    fclose(word);

    FILE * output = fopen(argv[2], "w");

    int c = 0;
    int q = 0;
    int q2 = 0;
    while (c < size) { // do step by step in array3
        if (c == size - 1) {
            break;
        }
        c++;
        if (array3[c] == ' ') {
            while (array3[c] == ' ') {
                if (c == size - 1) {
                    break;
                }
                c++;
            }
            q2 = 2;
            while (array3[c] != ' ') { // fill file with symbols
                if (q > 0 && q2 == 2) { // put ' ' if needed
                    fputc(' ', output);
                }
                fputc(array3[c], output);
                if (c == size - 1) {
                    break;
                }
                c++;
                q2 = 1;;
            }
            q++;
            while (array3[c] == ' ') {
                if (c == size - 1) {
                    break;
                }
                c++;
            }
        }
    }

    fclose(output);

    return 0;
}