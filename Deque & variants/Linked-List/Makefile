default: prog

interfaces.o: interfaces.c interfaces.h
              gcc -Wall -ansi -pedantic-errors -c interfaces.c

prog: interfaces.o main.c
      gcc -Wall -ansi -pedantic-errors -o prog interfaces.o  main.c structs.h

clean:
          rm interfaces.o

cleanall: clean
          rm prog
