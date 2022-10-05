
INSTALL_PACH=~/.local/bin/
FILES=main.c
OUT=gen-passwd

CFLAGS=-Wall -std=c99
LDFLAGS=

all:
	gcc $(CFLAGS) -o ${OUT} ${FILES} $(LDFLAGS)
	./${OUT}

clean:
	rm -f ${OUT}

install:
	cp ${OUT} ${INSTALL_PACH}


