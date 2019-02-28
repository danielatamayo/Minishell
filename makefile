G = 	# debug option here
CC = gcc 	# compiler
# EXEC = parent child functions
CFLAGS=-I.
DEPS = minishell.h
OBJ = minishell.o functions.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

minishell: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)









# target
# all: $(EXEC)
# parent : parent.o \
	$(CC) -o parent parent.o \
parent.o : parent.c \
	$(CC) -c parent.c \
child : child.o \
	$(CC) -o child child.o \
child.o : child.c \
	$(CC) -c child.c
# clean: \
	/bin/rm -f *.o core $(EXEC)

