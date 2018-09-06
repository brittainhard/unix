CC = gcc
EXE = a.out
CFLAGS = -Wall -g
DEPS = error.o
HEADERS = apue.h

program: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)

clean:
	rm -rf a.out *.o a.dSYM
