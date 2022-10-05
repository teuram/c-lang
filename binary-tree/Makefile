
OUT=hash-tree

CFLAGS=-Wall

all: main.o sha256.o
	gcc $(CFLAGS) main.o sha256.o -o ${OUT}

main.o: main.c
	gcc $(CFLAGS) -c main.c

sha256.o: sha256.c
	gcc $(CFLAGS) -c sha256.c

clean:
	rm -f *.o ${OUT}


