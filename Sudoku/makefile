CC = gcc
CFLAGS = -I.
DEPS = libsudoku.h
OBJ = main.o
LIBS = -L. -lsudoku -lpthread

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

sudoku: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f *.o *~ core sudoku

build: sudoku

run: build
	LD_LIBRARY_PATH=./ ./sudoku 45

debug: $(OBJ)
	$(CC) -g -o sudoku $(OBJ) $(LIBS)

