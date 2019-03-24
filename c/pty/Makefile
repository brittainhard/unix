CC= gcc
EXE= pty
TEST_EXE= a.out
CFLAGS= -Wall -g
SOURCE= pty.c
DEPS= open.o fork.o

all: clean pty
test: clean test_exe
pty: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)
test_exe: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TEST_EXE) $(DEPS)
vimmake: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(TEST_EXE) -o $(EXE) $(DEPS)
open:
	gcc -Wall -g -c -o open.o open.c
fork:
	gcc -Wall -g -c -o fork.o fork.c
clean:
	rm -rf a.out *.o a.dSYM
