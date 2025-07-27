CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRC = graph.c lexer.c parser.c evaluator.c
BUILDDIR = ../build

all: graph

	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(SRC) -o $(BUILDDIR)/graph

clean:
	rm -f *.o
	rm -f ../build/graph
