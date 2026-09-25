CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99

TARGET = main

SRCS = main.c dag.c ../pratica01/grafo_lista.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run