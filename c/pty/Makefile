CC= gcc
EXE= pty
TEST_EXE= a.out
CFLAGS= -Wall -g
SOURCE= main.c
DEPS= ptyopen.o ptyfork.o error.o driver.o loop.o

all: clean pty
test: clean test_exe

pty: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(EXE) $(DEPS)
test_exe: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TEST_EXE) $(DEPS)
vimmake: $(DEPS) $(SOURCE)
	$(CC) $(CFLAGS) $(TEST_EXE) -o $(EXE) $(DEPS)
clean:
	rm -rf a.out *.o a.dSYM
