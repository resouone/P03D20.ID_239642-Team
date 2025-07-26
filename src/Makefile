CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = graph.c lexer.c parser.c evaluator.c
OBJ = $(SRC:.c=.o)
BIN = ../build/graph

all: $(BIN)

$(BIN): $(SRC)
	mkdir -p ../build
	$(CC) $(CFLAGS) -o $(BIN) $(SRC) -lm

clean:
	rm -f *.o
	rm -f ../build/graph
