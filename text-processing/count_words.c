#include <stdio.h>

int main(int argc, char * argv[]) {

    if (argc != 2) {
        return 1;
    }

    FILE * an = fopen(argv[1], "r");

    char letter = fgetc(an);
    int counter = 0;
    while (letter != EOF) {
        if (letter == 'a' || letter == 'A') {
            letter = fgetc(an);
            if (letter == 'n' || letter == 'N') {
                letter = fgetc(an);
                if (letter == 'a' || letter == 'A') {
                    letter = fgetc(an);
                    if (letter == 'n' || letter == 'N') {
                        letter = fgetc(an);
                        if (letter == 'a' || letter == 'A') {
                            letter = fgetc(an);
                            if (letter == 's' || letter == 'S') {
                                letter = fgetc(an);
                                counter++;
                            } else {
                                letter = fgetc(an);
                                continue;
                            }
                        } else {
                            letter = fgetc(an);
                            continue;
                        }
                    } else {
                        letter = fgetc(an);
                        continue;
                    }
                } else {
                    letter = fgetc(an);
                    continue;
                }
            } else if (letter == 'a' || letter == 'A') {
                continue;
            } else {
                letter = fgetc(an);
                continue;
            }
        } else {
            letter = fgetc(an);
            continue;
        }
    }
    fclose(an);
    FILE * anwr = fopen(argv[1], "w");
    if (counter < 10) {
        fputc(counter + '0', anwr);
    }
    if (counter >= 10) {
        int n = counter / 10;
        fputc(n + '0', anwr);
        n = counter % 10;
        fputc(n + '0', anwr);
    }
    fclose(anwr);
    return 0;
}