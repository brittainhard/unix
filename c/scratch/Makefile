CC = gcc
EXE = a.out
CFLAGS = -Wall -g
SOURCE = scratch.c
DEPS = potato.o

all: clean scratch

scratch: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)

vimmake: $(ERROR) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(ERROR)

clean:
	rm -rf a.out *.o a.dSYM
