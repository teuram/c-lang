#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define DELAY 35000

void on_start(void) __attribute__ ((constructor));
void on_exit(void) __attribute__ ((destructor));

void on_start(void) {
    // code on start
}
void on_exit(void) {
    // code on exit
}

void mvprint(int x, int y, char* str) {
    printf("\033[%d;%dH%s", y, x, str);
}

int main(int argc, char *argv[]) {


    struct termios old, new;

    tcgetattr(STDIN_FILENO, &old);

    cfmakeraw(&new);
    new.c_cc[VTIME] = 0;
    new.c_cc[VMIN] = 0;
    new.c_lflag &= ~ECHO;

    tcsetattr(fileno(stdin), TCSANOW, &new);

    int i = 0;

    system("clear");
    puts("\033[?25l"); // off visible cursor

    while(1) {

        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);

        int y = w.ws_row;
        int x = w.ws_col;

        int ch = getchar();

        if(ch == 'q') {
            break;
        }

        char str[32];
        sprintf(str, "%d %d %d", i++, x, y);
        mvprint(8, 4, str);

        fflush(stdout);

        usleep(DELAY);
    }

    tcsetattr(fileno(stdin), TCSANOW, &old);


    return 0;
}

