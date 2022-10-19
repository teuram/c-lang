#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct termios old, new;

void set_raw_mode(void) {

    tcgetattr(STDIN_FILENO, &old);
    cfmakeraw(&new);
    new.c_cc[VTIME] = 0;
    new.c_cc[VMIN] = 0;
    new.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &new);
    system("clear");
    puts("\033[?25l"); // invisible cursor
}

void set_normal_mode(void) {

    tcsetattr(fileno(stdin), TCSANOW, &old);
    puts("\033[?25h"); // visible cursor

}

void clear() {
    puts("\033[1;1H\033[2J");
}

void mvprintw(int x, int y, char str[]) {
    static char st[64];
    sprintf(st, "\033[%d;%dH%s", y, x, str);
    puts(st);
}

void set_cur(int x, int y) {
    char st[16];
    sprintf(st, "\033[%d;%dH", y, x);
    puts(st);
}

