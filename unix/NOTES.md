To include the error header file, run `gcc ls.c -o a.out ../error.o`.

To build the object file, run `gcc -Wall -g -c -o error.o error.c`.

To build with an arbitrary c file, run `make program SOURCE=potato.c`

These things are in the makefiles directory.
