CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -g
SOURCES = helpers.c string.c dict.c dict_helpers.c main.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = dictionary

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)

run: 
	./dictionary

runGDB: 
	gdb ./dictionary

runVal: 
	valgrind --leak-check=full -s ./dictionary
