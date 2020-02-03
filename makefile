CC = gcc
CFLAGS = -ansi -Wall -pedantic -I$(IDIR)

IDIR = ./includes/
SRCDIR = ./src/

OBJ = main.o name.o title.o binary.o search.o principals.o
DEPS = $(IDIR)name.h $(IDIR)binary.h $(IDIR)search.h $(IDIR)principals.h $(IDIR)title.h
SOURCES = $(SRCDIR)*.c

all: a3

%.o: $(SRCDIR)%.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

a3: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run:
	./a3

clean:
	rm *o a3