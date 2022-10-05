
#ifndef PLAYER_H
#define PLAYER_H

struct player {
    Entite entite;
    unsigned long uuid;
    char name[16];
} typedef Player;

Player* constructor_player(char name[]);

void save_player(World* world, Player* player);

Player* load_player(World* world, char player_name[]);

void deconstructor_player(Player* player);

#endif

