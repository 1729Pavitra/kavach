CC=gcc
OBJ=*.o
PROG=the-sh
OBJ= main.o built_in.o command_list.o conditional.o  execute.o external.o internal.o itos.o parse.o prompt.o redirect.o stack.o tree.o variable.o

the-sh: $(OBJ)
	$(CC) $(OBJ) -o the-sh
	
main.o: main.c cmd.h macros.h variable.h prompt.h

built_in.o: cmd.h macros.h built_in.c

command_list.o: cmd.h command_list.c

conditional.o: conditional.c cmd.h

execute.o: execute.c cmd.h

external.o: cmd.h macros.h variable.h  external.c

internal.o: cmd.h macros.h variable.h internal.c

itos.o:  itos.c

parse.o: parse.c cmd.h macros.h 

prompt.o: macros.h  prompt.h prompt.c

redirect.o: cmd.h redirect.c

stack.o: stack.c stack.h  cmd.h variable.h

tree.o: tree.c cmd.h

variable.o: variable.c cmd.h stack.h variable.h

.PHONY: clean

clean:
	rm -f *.o $(PROG)

install:
	mv the-sh /usr/bin