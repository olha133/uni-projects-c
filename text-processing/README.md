# Text Processing Project

This project includes two programs: `count_words.c` and `every_second.c`. Each program performs specific text file manipulations as described below.

## Count the Words

### Description

`count_words.c` - counts the number of times the sequence of characters "ananas" appears in the input file. The result will be written to the same file, overwriting the original contents.

### Note

- Case does not matter when counting and comparing words.
- It is forbidden to use any library functions (strlen(), strcpy(), strcmp(), etc.) in the program.
- Only the following functions are allowed:
  - `fopen()` for initializing file work
  - `fclose()` to exit from the file
  - `fgetc()` to read from a file
  - `fputc()` to write to a file

### Usage

The program will take one argument: the name of the I/O file.

**Example:**

```
$ ls
bananas.txt count_words
$ ./count_words bananas.txt
$ ls
bananas.txt count_words
```
If the content of the bananas.txt file is as follows:

```
Bananas are edible fruits, botanically berries. In some countries, bAnAnAs used for cooking are called plantains, distinguishing them from dessert bananaS. The fruits grow in clusters hanging from the top of the plant. Almost all modern edible seedless BANANAS come from two wild species of Musa acuminata and Musa balbisiana. The scientific names of most cultivated bananas are Musa acuminata, Musa balbisiana, and Musa X paradisiaca, depending on their genomic constitution.
```
After running the program, the contents of the bananas.txt file will be:
```
5
```
## Every Other Word

### Description

`every_second.c` is a C program that processes an input file to create an output file containing every other word from the input file, between the words `START` and `STOP`. The program takes two command line arguments: the input file name and the output file name. 
The program reads the input file and begins storing every second word after encountering the word `START`. The process stops once the word `STOP` is found. The words in the output file are separated by spaces.

### Note

- The program differentiates between uppercase and lowercase characters.
- It is forbidden to use any library functions (strlen(), strcpy(), strcmp(), etc.) in the program.
- Only the following functions are allowed:
  - `fopen()` for initializing file work
  - `fclose()` to close the file
  - `fgetc()` to read from the file
  - `fputc()` to write to the file

### Usage

The program requires two arguments:
1. The input file name
2. The output file name
**Example:**
```
$ ls
every_second input.txt
$ ./every_second input.txt output.txt
$ ls
every_second input.txt output.txt
```
After running the program, if input.txt contains:

```
Hello start START Hello Kitty, say, how are you doing today? STOP
```
The output.txt will contain:

```
Kitty, how you today?
```
## How to Compile and Run
1. Compile the programs:
```
gcc -o count_words count_words.c
gcc -o every_second every_second.c
```
2. Run the programs:

For count_words.c:
```
./count_words <input_file>
```
For every_second.c:
```
./every_second <input_file> <output_file>
```
