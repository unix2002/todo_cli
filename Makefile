CC = gcc
CFLAGS = -std=c11 -Wextra -Wpedantic
LDFLAGS = -lncurses -fsanitize=address
SRC = $(wildcard *.c)
HEADERS = $(wildcard *.h)

all: todo_cli

todo_cli: $(SRC)
	$(CC) -o $@ $^ $(CFLAGS) 

clean:
	rm -f *~ *.o todo_cli
