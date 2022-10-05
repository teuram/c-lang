

#ifndef WORLD_H
#define WORLD_H

#include "params.h"
#include "vector.h"

struct block {
    int id;
    int heal;
} typedef Block;

struct chank {
    Block* blocks[CHANK_SIZE][CHANK_SIZE];
    int is_not_save;
} typedef Chank;

struct world {
    char* path;
    Chank* chanks[WORLD_SIZE][WORLD_SIZE];
} typedef World;

Block* constructor_block(int id);

void deconstructor_block(Block* block);

Chank* constructor_chank();

void deconstructor_chank(Chank* chank);

World* constructor_world();

World* load_world(char* path);

Chank* gen_chank();

void save_chank(World* world, Chank* chank, Vec pos);

Chank* load_chank(World* world, Vec pos);

Chank* get_chank_world(World* world, Vec pos);

void set_is_not_save(World* world, Vec pos);

Block* get_block_world(World* world, Vec pos);

void deconstructor_world(World* world);


#endif

