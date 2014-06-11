TARGET = kavach
INSTALL_PATH = /usr/bin
CC=gcc
INCLUDE_DIR=src/include
.PHONY: clean uninstall


SOURCES = src/main.c src/built_in.c src/command_list.c src/execute.c src/external.c src/internal.c src/parse.c src/prompt.c src/redirect.c src/variable.c


#OBJECTS = build/main.o build/built_in.o build/command_list.o build/execute.o build/external.o build/internal.o build/parse.o build/prompt.o build/redirect.o build/variable.o

OBJECTS = $(subst .c,.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o kavach
	
%.o : %.c
	$(CC) -I $(INCLUDE_DIR) -c $< -o $@


clean:
	rm -f $(OBJECTS) $(TARGET)

install: $(TARGET)
	mv $(TARGET) $(INSTALL_PATH)

uninstall:
	rm $(INSTALL_PATH)/$(TARGET) -f
