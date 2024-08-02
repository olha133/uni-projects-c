#include <stdio.h>
#include <stdbool.h>
#include <string.h>


void encode_char(const char character, bool bits[8]) {
    char my_char = character; // put character into variable
    int to_ascii = (int) my_char; // // symbol to ASCII table

    for (int i = 7; i >= 0; i--) { // filling an array with binary code
        bits[i] = to_ascii % 2;
        to_ascii = to_ascii / 2;
    }
}

char decode_byte(const bool bits[8]) {
    int to_ascii = 0;
    int B = 128;
    for (int i = 0; i < 8; i++) {
        if (bits[i] == 1) {
            to_ascii = to_ascii + B;
        }
        B = B / 2;
    }

    char my_char = (char) to_ascii;

    return my_char;
}

void encode_string(const char string[], bool bytes[strlen(string) + 1][8]) {
    bool bits[8];
    int y = 0;

    for (int i = 0; i < strlen(string) + 1; i++) {
        encode_char(string[i], bits);
        for (int x = 0; x < 8; x++) {
            bytes[y][x] = bits[x];
        }
        y++;
    }
}

void decode_bytes(const int rows, bool bytes[rows][8], char string[rows]) {
    bool bits[8];
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < 8; x++) {
            bits[x] = bytes[y][x];
        }
        string[y] = decode_byte(bits);
    }
}

void bytes_to_blocks(const int cols,
    const int offset, bool blocks[offset * 8][cols],
        const int rows, bool bytes[rows][8]) {
    int k = 0;
    int c = 0;
    for (int f = 0; f < offset; f++) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < cols; y++) {
                if ((y + c) >= rows) {
                    blocks[x + k][y] = false;
                } else {
                    blocks[x + k][y] = bytes[y + c][x];
                }
            }
        }
        k = k + 8;
        c = c + cols;
    }
}

void blocks_to_bytes(const int cols,
    const int offset, bool blocks[offset * 8][cols],
        const int rows, bool bytes[rows][8]) {
    int k = 0;
    int c = 0;

    for (int f = 0; f < offset; f++) {
        for (int x = 0; x < cols; x++) {
            if ((x + c) >= rows) {
                break;
            } else {
                for (int y = 0; y < 8; y++) {
                    bytes[x + c][y] = blocks[y + k][x];
                }
            }
        }
        k = k + 8;
        c = c + cols;
    }
}

int main() {
    /*int lenght = 4+1;
    bool blocks2[2*8][3] = {
    {0,0,0},
    {1,1,1},
    {0,1,1},
    {0,0,0},
    {0,1,1},
    {0,0,1},
    {0,0,1},
    {1,0,1},
    {0,0,0},
    {1,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0},
    {1,0,0},
    {0,0,0}
    };

    bool bytes2[lenght][8];
    blocks_to_bytes(3,2, blocks2,lenght,bytes2);
    for ( int j = 0; j < lenght; j++){
        for( int i = 0; i < 8; i++ ) {
            printf("%d",  bytes2[j][i]);
        }
    printf("\n");


    }*/
}