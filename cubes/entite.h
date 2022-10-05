
#ifndef ENTITE_H
#define ENTITE_H

#include "world.h"
#include "timer.h"

struct entite {
    Vec pos;
    Vec side;
    Timer timer_move;
} typedef Entite;

Vec get_next_step(Entite* entite);

Block* get_block_front(World* world, Entite* entite);

int move_entite(World* world, Entite* entite);


#endif

