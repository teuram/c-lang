#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
// #include <dirent.h>
#include <sys/ioctl.h>

#include <ncurses.h>

#include "params.h"
#include "vector.h"
#include "entite.h"
#include "player.h"
#include "world.h"
#include "timer.h"

#define DELAY 50000

void save_game();

void on_start(void) {
    // code
    // set_raw_mode();

    initscr();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(FALSE);
    // raw();
    timeout(1);
}


void on_exit(void) {
    // code
    // set_normal_mode();
    endwin();
}

World* world;
Player* player;
int cenDisplX, cenDisplY;
int width, height;

void draw() {
    mvprintw(cenDisplY, cenDisplX * 2, "[]");

    int drawX, drawY;

    const int rad = 20; // diameter = rad * 2 + 1
    for(int x = player->entite.pos.x - rad ; x < player->entite.pos.x + rad; x++) {
        for(int y = player->entite.pos.y - rad; y < player->entite.pos.y + rad; y++) {

            if(player->entite.side.y == -1) {
                drawY = y - player->entite.pos.y + cenDisplY;
                drawX = (x - player->entite.pos.x + cenDisplX) * 2;
            }
            if(player->entite.side.y == 1) {
                drawY = player->entite.pos.y - y + cenDisplY;
                drawX = (player->entite.pos.x - x + cenDisplX) * 2;
            }
            if(player->entite.side.x == -1) {
                drawY = x - player->entite.pos.x + cenDisplY;
                drawX = (player->entite.pos.y - y + cenDisplX) * 2;
            }
            if(player->entite.side.x == 1) {
                drawY = player->entite.pos.x - x + cenDisplY;
                drawX = (y - player->entite.pos.y + cenDisplX) * 2;
            }

            if(get_block_world(world, new_vec(x, y))->id == 1) {
                mvprintw(drawY, drawX, "::");
            }
            if(get_block_world(world, new_vec(x, y))->id == 10) {
                mvprintw(drawY, drawX, "##");
            }

        }
    }

    char side_of_the_world[6];
    if(player->entite.side.y == -1) {
        sprintf(side_of_the_world, "North");
    }
    if(player->entite.side.y == 1) {
        sprintf(side_of_the_world, "South");
    }
    if(player->entite.side.x == -1) {
        sprintf(side_of_the_world, "West");
    }
    if(player->entite.side.x == 1) {
        sprintf(side_of_the_world, "East");
    }

    mvprintw(0, 0, "chank:\t[%d, %d]\n\rchank size: %d\n\rcompas:\t%s\n", player->entite.pos.x / CHANK_SIZE, player->entite.pos.y / CHANK_SIZE, CHANK_SIZE, side_of_the_world);

    Block* blk = get_block_front(world, &player->entite);
    if(blk->id != 0) {
        mvprintw(5, 0, "heal: %d", blk->heal);
    }

}

void update() {
    int ch = getch();

    switch(ch) {

        case KEY_LEFT:
            if(player->entite.side.y == -1) {
                set_vec(&player->entite.side, -1, 0);
            } else if(player->entite.side.x == -1) {
                set_vec(&player->entite.side, 0, 1);
            } else if(player->entite.side.y == 1) {
                set_vec(&player->entite.side, 1, 0);
            } else /* player->entite.side.x == 1 */ {
                set_vec(&player->entite.side, 0, -1);
            }
            clear();

            break;

        case KEY_RIGHT:
            if(player->entite.side.y == -1) {
                set_vec(&player->entite.side, 1, 0);
            } else if(player->entite.side.x == 1) {
                set_vec(&player->entite.side, 0, 1);
            } else if(player->entite.side.y == 1) {
                set_vec(&player->entite.side, -1, 0);
            } else /* player->entite.side.x == -1 */ {
                set_vec(&player->entite.side, 0, -1);
            }
            clear();

            break;

        case KEY_UP:

            if(move_entite(world, &player->entite)) {
                clear();
            }
            break;

        case 'e':
            {
                Block* blk = get_block_front(world, &player->entite);
                if(blk->id != 0) {
                    blk->heal--;
                    set_is_not_save(world, get_next_step(&player->entite));
                    if(blk->heal == 0) {
                        blk->id = 0;

                        clear();
                    }
                }

                break;
            }

        case 'r':
            {
                Block* blk = get_block_front(world, &player->entite);
                if(blk->id == 0) {
                    blk->id = 10;
                    blk->heal = 8;
                    set_is_not_save(world, get_next_step(&player->entite));

                    clear();
                }

                break;
            }

        case 'q':
            save_game();
            on_exit();
            clear();
            exit(0);

    }
}

void save_game() {
    for(int iy = 0; iy < WORLD_SIZE; iy++) {
        for(int ix = 0; ix < WORLD_SIZE; ix++) {
            if(world->chanks[iy][ix] != NULL) {
                if(world->chanks[iy][ix]->is_not_save) {
                    save_chank(world, world->chanks[iy][ix], new_vec(ix, iy));
                    world->chanks[iy][ix]->is_not_save = 0;
                    mvprintw(10, 0, "save game");
                }
            }
        }
    }
    save_player(world, player);
}

Timer time_save;

void auto_save() {
    if(timer(&time_save)) {
        save_game();
    }
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        puts("usage: cubes <path to world> <username>\n\n");
        exit(0);
    }

    printf("open %s\n", argv[1]);

    world = load_world(argv[1]);
    player = load_player(world, argv[2]);

    on_start();

    time_save.cycle = 5 * 1000;

    while(1) {
        struct winsize w;
        ioctl(0, TIOCGWINSZ, &w);

        height = w.ws_row;
        width = w.ws_col;

        cenDisplX = width / 4;
        cenDisplY = height / 2;

        auto_save();
        update();

        draw();
        refresh();

        usleep(DELAY);

    }

    deconstructor_player(player);
    deconstructor_world(world);

    on_exit();

    return 0;
}
