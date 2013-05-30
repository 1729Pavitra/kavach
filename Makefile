CC=gcc
.PHONY: clean uninstall

SOURCES = src/main.c src/built_in.c src/command_list.c src/conditional.c  src/execute.c src/external.c src/internal.c src/itos.c src/parse.c src/prompt.c src/redirect.c src/stack.c src/tree.c src/variable.c

OBJECTS = $(subst .c,.o,$(SOURCES))
TARGET = the-sh
INSTALL_PATH = /usr/bin

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o the-sh
	
%.o : %.c
	$(CC) -c $< -o $@


clean:
	rm -f i$(OBJECTS) $(TARGET)

install: $(TARGET)
	mv $(TARGET) $(INSTALL_PATH)

uninstall:
	rm $(INSTALL_PATH)/$(TARGET) -f
