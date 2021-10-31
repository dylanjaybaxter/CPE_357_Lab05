CC = gcc
CFLAGS = -Wall -g -ansi
LD = gcc
LDFLAGS = -g

all: mypwd dir.o

mypwd: mypwd.o dir.o
	$(LD) $(LDFLAGS) -o mypwd mypwd.o dir.o

mypwd.o: mypwd.c
	$(CC) $(CFLAGS) -c -o mypwd.o mypwd.c
dir.o: dir.c dir.h
	$(CC) $(CFLAGS) -c -o dir.o dir.c

clean: mypwd
	rm mypwd.o dir.o

debug: mypwd
	gdb mypwd

valgrind: mypwd
	valgrind -s --leak-check=full --show-leak-kinds=all ./mypwd