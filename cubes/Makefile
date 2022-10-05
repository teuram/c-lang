
BIN=cubes
CFLAGS=-Wall -std=c99


all: main.o
	-gcc $(CFLAGS) -lncurses main.o vector.o entite.o player.o world.o timer.o -o ${BIN}


main.o: main.c params.h player.o entite.o world.o vector.o timer.o
	-gcc $(CFLAGS) -c main.c


player.o: player.c vector.o entite.o
	-gcc $(CFLAGS) -c player.c


entite.o: entite.c vector.o world.o timer.o
	-gcc $(CFLAGS) -c entite.c

timer.o: timer.c
	-gcc $(CFLAGS) -c timer.c


world.o: world.c params.h vector.o
	-gcc $(CFLAGS) -c world.c


vector.o: vector.c params.h
	-gcc $(CFLAGS) -c vector.c


clean:
	-rm ${BIN}
	-rm *.o


