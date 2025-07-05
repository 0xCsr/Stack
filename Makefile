CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11 -g
TARGET = stack_app
SRC = main.c stack.c person.c array.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) *.o

.PHONY: all clean

