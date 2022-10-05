
FILES=main.c
OUT=rename-files

CFLAGS=-g -Wall
LDFLAGS=

all:
	gcc $(CFLAGS) -o ${OUT} ${FILES} $(LDFLAGS)

clean:
	rm -f ${OUT}

install:
	cp ${OUT} ${HOME}/.local/bin/
	exit

