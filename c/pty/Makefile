CC= gcc
EXE= a.out
CFLAGS= -Wall -g
SOURCE= pty.c
DEPS= error.o
HEADERS= apue.h

program: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)

vimmake: $(ERROR) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(ERROR)

clean:
	rm -rf a.out *.o a.dSYM
