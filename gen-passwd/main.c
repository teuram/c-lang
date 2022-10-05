#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char rnd_char() {
    int r = rand() % 36;
    return (r / 10) ? r + 97 - 10 : r + 48;
}

void print_rnd(int l) {
    do {
        putchar(rnd_char());
    } while((--l) != 0);
}

int main(int argc, char *argv[]) {

    srand(time(NULL));

    int tho = rand() % 7;

    for(int i = 0; i < 7; i++) {
        if(i == tho) {
            print_rnd(2);
        } else {
            print_rnd(4);
        }
        if(i != 6) {
            putchar('-');
        }
    }

    putchar('\n');

    return 0;
}

