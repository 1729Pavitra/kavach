CC=gcc
.PHONY: clean uninstall

SOURCES = main.c built_in.c command_list.c conditional.c  execute.c external.c internal.c itos.c parse.c prompt.c redirect.c stack.c tree.c variable.c

OBJECTS = $(subst .c,.o,$(SOURCES))
TARGET = the-sh
INSTALL_PATH = /usr/bin

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o the-sh
	
%.o : %.c
	$(CC) -c $<


clean:
	rm -f *.o $(TARGET)

install: $(TARGET)
	mv $(TARGET) $(INSTALL_PATH)

uninstall:
	rm $(INSTALL_PATH)/$(TARGET) -f
