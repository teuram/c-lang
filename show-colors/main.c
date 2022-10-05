#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    putchar('\n');

    int i = 0;
    while(i < 256) {
        printf("\033[48;5;%dm%3d\033[0m ", i, i);
        fflush(stdout);
        i++;
        if(i % 8 == 0) {
            putchar('\n');
        }
    }

    return 0;
}

