#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

#include "world.h"
#include "vector.h"
#include "params.h"


Block* constructor_block(int id) {
    Block* block = NULL;
    block = malloc(sizeof(Block));
    block->id = id;
    return block;
}

void deconstructor_block(Block* block) {
    free(block);
    block = NULL;
}

Chank* constructor_chank() {
    Chank* chank = NULL;
    chank = malloc(sizeof(Chank));

    for(int ix = 0; ix < CHANK_SIZE; ix++) {
        for(int iy = 0; iy < CHANK_SIZE; iy++) {
            chank->blocks[iy][ix] = constructor_block(0);
        }
    }

    return chank;
}

void deconstructor_chank(Chank* chank) {
    for(int ix = 0; ix < CHANK_SIZE; ix++) {
        for(int iy = 0; iy < CHANK_SIZE; iy++) {
            deconstructor_block(chank->blocks[iy][ix]);
        }
    }

    free(chank);
    chank = NULL;
}

World* constructor_world() {
    World* world = NULL;
    world = malloc(sizeof(World));

    for(int ix = 0; ix < WORLD_SIZE; ix++) {
        for(int iy = 0; iy < WORLD_SIZE; iy++) {
            world->chanks[iy][ix] = NULL;
        }
    }

    return world;
}

World* load_world(char* path) {

    struct stat st;
    if(stat(path, &st) == -1) {
        printf("world \"%s\" is not contains. create? (y/n): ", path);
        if(getchar() != 'y') {
            printf("exit\n");
            exit(0);
        }
        mkdir(path, 0700);
    }

    World* world = constructor_world();
    world->path = path;

    return world;
}

Chank* gen_chank() {
    Chank* chank = NULL;
    chank = constructor_chank();

    for(int iy = 0; iy < CHANK_SIZE; iy++) {
        for(int ix = 0; ix < CHANK_SIZE; ix++) {
            int id = (rand() % 256 > 225) ? 1 : 0;
            chank->blocks[iy][ix]->id = id;
            if(id == 1)
                chank->blocks[iy][ix]->heal = 4;
        }
    }

    return chank;
}

void save_chank(World* world, Chank* chank, Vec pos) {

    FILE* fd = NULL;
    char fileName[1024];

    sprintf(fileName, "%s/%08x%08x", world->path, pos.x, pos.y);

    if((fd = fopen(fileName, "wb")) == NULL) { 
        printf("error opening file of chank %08x%08x for writing\n", pos.x, pos.y); 
        exit(2);
    }

    for(int iy = 0; iy < CHANK_SIZE; iy++) {
        for(int ix = 0; ix < CHANK_SIZE; ix++) {
            fwrite(chank->blocks[iy][ix], sizeof(Block), 1, fd);
        }
    }
    //printf("save chank %08x%08x\n", x, y);
}

Chank* load_chank(World* world, Vec pos) {

    Chank* chank = NULL;
    FILE* fd = NULL;

    char fileName[1024];

    sprintf(fileName, "%s/%08x%08x", world->path, pos.x, pos.y);

    if((fd = fopen(fileName, "rb")) == NULL) {
        //printf("chank %08x%08x is not exist\n", x, y);
        chank = gen_chank();
        //printf("generate chank %08x%08x\n", x, y);
        save_chank(world, chank, pos);
        //printf("chank %08x%08x is loaded\n", x, y);
        return chank;
    }

    chank = constructor_chank();

    //printf("chank %08x%08x is contains\n", x, y);
    for(int iy = 0; iy < CHANK_SIZE; iy++) {
        for(int ix = 0; ix < CHANK_SIZE; ix++) {
            fread(chank->blocks[iy][ix], sizeof(Block), 1, fd);
        }
    }
    //printf("chank %08x%08x is loaded\n", x, y);

    return chank;
}

Chank* get_chank_world(World* world, Vec pos) {

    return world->chanks[pos.y / CHANK_SIZE][pos.x / CHANK_SIZE];
}

void set_is_not_save(World* world, Vec pos) {
    get_chank_world(world, pos)->is_not_save = 1;
}

Block* get_block_world(World* world, Vec pos) {

    norm_vec(&pos);

    if(get_chank_world(world, pos) == NULL) {
        Vec vec = div_vec(pos, CHANK_SIZE);
        Chank* chank = load_chank(world, vec);
        world->chanks[vec.y][vec.x] = chank;
    }

    return world->chanks[pos.y / CHANK_SIZE][pos.x / CHANK_SIZE]->blocks[pos.y % CHANK_SIZE][pos.x % CHANK_SIZE];
}

void deconstructor_world(World* world) {

    for(int iy = 0; iy < CHANK_SIZE; iy++) {
        for(int ix = 0; ix < CHANK_SIZE; ix++) {
            if(world->chanks[iy][ix] != NULL) {
                deconstructor_chank(world->chanks[iy][ix]);
            }
        }
    }
    free(world->path);
    free(world);
    world = NULL;
}
