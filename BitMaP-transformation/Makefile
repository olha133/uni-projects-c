OUTPUT=ps4
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
SOURCES=bmp.c main.c transformations.c


all: codeanalysis ps4

codeanalysis: $(SOURCES)
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 $^
$(OUTPUT): bmp.o main.o transformations.o
	echo "Running compilation"
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

bmp.o: bmp.c
	echo "Building object file bmp.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

transformations.o: transformations.c
	echo "Building object file transformations.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
clean:
	rm -rf *.o $(OUTPUT) bin/*
