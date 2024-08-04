OUTPUT=ps2
CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
SOURCES=k.c hof.c main.c ui.c


all: codeanalysis ps2

codeanalysis: $(SOURCES)
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 $^
$(OUTPUT): main.o k.o hof.o ui.o
	echo "Running compilation"
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	echo "Building object file main.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

k.o: k.c
	echo "Building object file k.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@

hof.o: hof.c
	echo "Building object file hof.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
ui.o: ui.c
	echo "Building object file ui.o"
	$(CC) $(CFLAGS) -c $^ $(LDLIBS) -o $@
clean:
	rm -rf *.o $(OUTPUT) bin/*
push:
	git commit -a
	git push 
    
