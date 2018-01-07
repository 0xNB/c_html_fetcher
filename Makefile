CC=gcc
CFLAGS=-I .
DEPS=fetchSource.h
OBJ=main.o fetchSource.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
