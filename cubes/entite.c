#include <sys/time.h>
#include "vector.h"
#include "entite.h"
#include "world.h"
#include "timer.h"

Vec get_next_step(Entite* entite) {
    Vec vec = sum_vec(&entite->pos, &entite->side);
    norm_vec(&vec);
    return vec;
}

Block* get_block_front(World* world, Entite* entite) {
    Vec vec = get_next_step(entite);
    return get_block_world(world, vec);
}

int move_entite(World* world, Entite* entite) {
    if(timer(&entite->timer_move)) {
        Vec vec = get_next_step(entite);
        Block* block = get_block_front(world, entite);
        if(block->id == 0) {
            entite->pos = vec;
            return 1;
        }
    }
    return 0;
}

