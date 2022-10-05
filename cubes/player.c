#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

#include <sys/stat.h>

#include "vector.h"
#include "entite.h"
#include "player.h"

Player* constructor_player(char name[]) {
    srand(time(NULL));

    Vec pos = new_vec(0, 0);
    norm_vec(&pos);

    Player* player = NULL;
    player = malloc(sizeof(Player));

    player->entite.pos = pos;
    player->entite.side = new_vec(0, -1);
    player->entite.timer_move.cycle = 50; // 1000 / 50 = 20 block per second
    player->uuid = rand();

    sprintf(player->name, "%s", name);

    return player;
}

void save_player(World* world, Player* player) {
    FILE* fd = NULL;

    char file_name[1024];
    sprintf(file_name, "%s/player-data/%lx", world->path, player->uuid);

    if((fd = fopen(file_name, "wb")) == NULL) {
        exit(2);
    }

    fwrite(player, sizeof(Player), 1, fd);

    fclose(fd);
}

Player* load_player(World* world, char player_name[]) {
    Player* player = NULL;
    player = malloc(sizeof(Player));

    struct dirent *de;
    DIR *dr = NULL;

    char file_name[1024];

    sprintf(file_name, "%s/player-data/", world->path);

    if((dr = opendir(file_name)) == NULL) {

        struct stat st;
        if (stat(file_name, &st) == -1) {
            mkdir(file_name, 0700);
        }
        dr = opendir(file_name);

        // puts("directory is not exist\n");
        // exit(2);
    }
    // memset(file_name, 0, 1024);

    FILE* fd = NULL;

    while((de = readdir(dr)) != NULL) {
        sprintf(file_name, "%s/player-data/%s", world->path, de->d_name);

        if((fd = fopen(file_name, "rb")) == NULL) {
            puts("file is not exist\n");
            exit(2);
        }

        fread(player, sizeof(Player), 1, fd);

        if(strcmp(player->name, player_name) == 0) {
            return player;
        }
        fclose(fd);
    }

    closedir(dr);
    free(player);

    return constructor_player(player_name);
}

void deconstructor_player(Player* player) {
    free(player);
    player = NULL;
}
