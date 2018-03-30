CC = gcc

CFLAGS = -Wall -Wextra -pedantic -g 

default: solver

solver: solver.c rubix.c rubix.h 
	$(CC) $(CFLAGS) solver.c rubix.c rubix.h -o solver
