CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm

SRC = main.c cmdexecution.c
OBJ = $(SRC:.c=.o)
EXECUTABLE = xtremeshell

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c cmdexecution.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(EXECUTABLE) $(OBJ)
