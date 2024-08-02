# Text to Byte Block Converter

This project involves converting short text into byte code, grouping it into blocks, and performing the reverse operation.
## Encoding Example

Let's encode the string "Ahoj!". The characters to encode are: 'A', 'h', 'o', 'j', '!', '\0'. We encode these characters in binary based on their values in the ASCII table, including the null terminator ('\0').

### Step-by-Step Process

1. **Convert Characters to Binary:**
   - Each character is converted to its binary representation based on its ASCII value. This produces a byte for each character.

2. **Generate a Two-Dimensional Array:**
   - For the string "Ahoj!", the binary values are arranged in a two-dimensional array, with each byte on a new line.

### Example Encoding

- **String:** "Ahoj!"
- **Characters:** 'A', 'h', 'o', 'j', '!', '\0'
- **Binary Representation:**

| Character | Binary       |
|-----------|--------------|
| A         | 01000001     |
| h         | 01101000     |
| o         | 01101111     |
| j         | 01101010     |
| !         | 00100001     |
| \0        | 00000000     |

### Arranging in Blocks

Based on the encoded bytes, we create blocks with predefined numbers of rows and columns. Characters are stored vertically in the blocks, moving from left to right and from top to bottom according to the offset.

#### Example with 2 Rows and 3 Columns

For 2 rows (2\*8 bits) and 3 columns, the string "Ahoj!" is stored as follows:

|   | 1st Column | 2nd Column | 3rd Column |
|---|------------|------------|------------|
| 1 | A          | h          | o          |
| 2 | j          | !          | \0         |

**Blocks:**

|   | 1st Column | 2nd Column | 3rd Column |
|---|------------|------------|------------|
| 1 | 0          | 0          | 0          |
| 2 | 1          | 1          | 1          |
| 3 | 0          | 1          | 1          |
| 4 | 0          | 0          | 0          |
| 5 | 0          | 1          | 1          |
| 6 | 0          | 0          | 1          |
| 7 | 0          | 0          | 1          |
| 8 | 1          | 0          | 1          |

|   | 1st Column | 2nd Column | 3rd Column |
|---|------------|------------|------------|
| 1 | 0          | 0          | 0          |
| 2 | 1          | 0          | 0          |
| 3 | 1          | 1          | 0          |
| 4 | 0          | 0          | 0          |
| 5 | 1          | 0          | 0          |
| 6 | 0          | 0          | 0          |
| 7 | 1          | 0          | 0          |
| 8 | 0          | 1          | 0          |

#### Example with 2 Rows and 4 Columns

For 2 rows (2\*8 bits) and 4 columns, the string "Ahoj!" is stored as follows:

|   | 1st Column | 2nd Column | 3rd Column | 4th Column |
|---|------------|------------|------------|------------|
| 1 | A          | h          | o          | j          |
| 2 | !          | \0         | \0         | \0         |

**Blocks:**

|   | 1st Column | 2nd Column | 3rd Column | 4th Column |
|---|------------|------------|------------|------------|
| 1 | 0          | 0          | 0          | 0          |
| 2 | 1          | 1          | 1          | 1          |
| 3 | 0          | 1          | 1          | 1          |
| 4 | 0          | 0          | 0          | 0          |
| 5 | 0          | 1          | 1          | 1          |
| 6 | 0          | 0          | 1          | 0          |
| 7 | 0          | 0          | 1          | 1          |
| 8 | 1          | 0          | 1          | 0          |

|   | 1st Column | 2nd Column | 3rd Column | 4th Column |
|---|------------|------------|------------|------------|
| 1 | 0          | 0          | 0          | 0          |
| 2 | 0          | 0          | 0          | 0          |
| 3 | 1          | 0          | 0          | 0          |
| 4 | 0          | 0          | 0          | 0          |
| 5 | 0          | 0          | 0          | 0          |
| 6 | 0          | 0          | 0          | 0          |
| 7 | 0          | 0          | 0          | 0          |
| 8 | 1          | 0          | 0          | 0          |

## Functions

### `void encode_char(const char character, bool bits[8])`

Encodes a character into its binary representation.

**Parameters:**
- `const char character`: The character whose ASCII value is encoded from decimal to binary.
- `bool bits[8]`: An array of true or false values representing the binary bits. Its size is 8 because each character can be encoded to 8 bits.

**Description:**
- This function does not return any value.
- It fills the `bits` array with true (1) or false (0) values representing the ASCII notation of the character value in binary.

### `char decode_byte(const bool bits[8])`

Decodes a byte (8 bits) into its corresponding character.

**Parameters:**
- `const bool bits[8]`: An array of true or false values representing the binary bits. Its size is 8 because each character can be encoded to 8 bits.

**Returns:**
- A character corresponding to the ASCII value represented by the binary `bits` array.

**Functions Call Example:**
```
bool bits1[8];
encode_char('A', bits1);
for(int i = 0; i < 8; i++){
    printf("%d", bits1[i]);
}
printf("\n");
// prints: 01000001

bool bits2[8] = {0,1,0,0,0,0,0,1};
printf("%c\n", decode_byte(bits2));
// prints: A
```

### `void encode_string(const char string[], bool bytes[strlen(string)+1][8])`

Encodes a string into its binary representation.

**Parameters:**
- `const char string[]`: The string to be encoded into bytes.
- `bool bytes[strlen(string)+1][8]`: A two-dimensional array where each row represents a byte (8 bits).

**Description:**
- This function does not return any value.
- It populates the `bytes` array with true (1) or false (0) values representing the binary encoding of each character in the string, including the null terminator.

### `void decode_bytes(const int rows, bool bytes[rows][8], char string[rows])`

Decodes an array of bytes (8 bits) into a string.

**Parameters:**
- `const int rows`: The number of rows in the `bytes` array and the number of characters in `string`, including the null terminator.
- `bool bytes[rows][8]`: A two-dimensional array where each row represents a byte (8 bits).
- `char string[rows]`: The string to be formed by decoding the data in the `bytes` array.

**Description:**
- This function does not return any value.
- It fills the `string` array with characters by decoding the binary data in the `bytes` array.

**Functions Call Example:**
```
char* text = "Hello, how are you?";
const int len = strlen(text);
bool bytes1[len+1][8];
encode_string(text, bytes1);
for(int j = 0; j <= len; j++){
    printf("%c: ", text[j]);
    for(int i = 0; i < 8; i++){
        printf("%d", bytes1[j][i]);
    }
    printf("\n");
}
// prints:
// H: 01001000
// e: 01100101
// l: 01101100
// l: 01101100
// o: 01101111
// ,: 00101100
//  : 00100000
// h: 01101000
// o: 01101111
// w: 01110111
//  : 00100000
// a: 01100001
// r: 01110010
// e: 01100101
//  : 00100000
// y: 01111001
// o: 01101111
// u: 01110101
// ?: 00111111
// : 00000000

bool bytes2[7][8] = {
    {0,1,0,0,1,0,0,0},
    {0,1,1,0,0,1,0,1},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,0,0},
    {0,1,1,0,1,1,1,1},
    {0,0,1,0,0,0,0,1},
    {0,0,0,0,0,0,0,0}
};
char string[7];
decode_bytes(7, bytes2, string);
printf("%s\n", string);
// prints: Hello!
```

### `void bytes_to_blocks(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8])`

Groups an array of bytes into blocks.

**Parameters:**
- `const int cols`: Number of columns for the blocks.
- `const int offset`: Number of row groups for the blocks (modifies the number of rows for blocks).
- `bool blocks[offset*8][cols]`: A two-dimensional array for blocks with a well-defined number of columns and rows.
- `const int rows`: Number of rows (string length including the null terminator).
- `bool bytes[rows][8]`: A two-dimensional array where each row represents a byte (8 bits).

**Description:**
- This function does not return any value.
- It fills the `blocks` array with blocks of bytes that contain the binary codes for the individual characters of the string.

### `void blocks_to_bytes(const int cols, const int offset, bool blocks[offset*8][cols], const int rows, bool bytes[rows][8])`

Converts blocks of bytes back into an array of bytes.

**Parameters:**
- `const int cols`: Number of columns for the blocks.
- `const int offset`: Number of row groups for the blocks (modifies the number of rows for blocks).
- `bool blocks[offset*8][cols]`: A two-dimensional array for blocks with a well-defined number of columns and rows.
- `const int rows`: Number of rows (string length including the null terminator).
- `bool bytes[rows][8]`: A two-dimensional array where each row represents a byte (8 bits).

**Description:**
- This function does not return any value.
- It fills the `bytes` array with the binary codes for the individual characters of the string from the `blocks` array.

**Functions Call Example:**
```
int length = 4+1, cols = 3, offset = 2;
bool bytes1[4+1][8] = {
    {0,1,0,0,0,0,0,1},
    {0,1,1,0,1,0,0,0},
    {0,1,1,0,1,1,1,1},
    {0,1,1,0,1,0,1,0},
    {0,0,0,0,0,0,0,0}
};
bool blocks1[offset*8][cols];
bytes_to_blocks(cols, offset, blocks1, length, bytes1);
for(int j = 0; j < offset*8; j++){
    for(int i = 0; i < cols; i++){
        printf("%d ", (blocks1[j][i] == true) ? 1 : 0);
    }
    printf("\n");
    if(j % 8 == 7){
        printf("\n");
    }
}
// prints:
// 0 0 0 
// 1 1 1 
// 0 1 1 
// 0 0 0 
// 0 1 1 
// 0 0 1 
// 0 0 1 
// 1 0 1 
// 
// 0 0 0 
// 1 0 0 
// 1 0 0 
// 0 0 0 
// 1 0 0 
// 0 0 0 
// 1 0 0 
// 0 0 0

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
bool bytes2[length][8];
blocks_to_bytes(3, 2, blocks2, length, bytes2);
for(int j = 0; j < length; j++){
    for(int i = 0; i < 8; i++){
        printf("%d", bytes2[j][i]);
    }
    printf("\n");
}
// prints:
// 01000001
// 01101000
// 01101111
// 01101010
// 00000000
```

## How to Compile and Run

1. Compile the program:
   ```sh
   gcc -o qr qr.c
2. Run the program:
   ```sh
   ./qr

