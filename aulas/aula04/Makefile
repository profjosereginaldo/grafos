# Makefile modelo para Teoria dos Grafos

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -lm
TARGET = a.out
SRC = *.c
OBJ = *.o

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET) $(OBJ)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
