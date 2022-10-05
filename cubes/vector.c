#include <stdlib.h>

#include "vector.h"
#include "params.h"

void norm_vec(Vec* vec) {
    const int s = CHANK_SIZE * WORLD_SIZE;
    if(vec->x < 0) vec->x = s + vec->x % s;
    if(vec->x > s - 1) vec->x = vec->x % s;
    if(vec->y < 0) vec->y = s + vec->y % s;
    if(vec->y > s - 1) vec->y = vec->y % s;
}

Vec new_vec(int x, int y) {
    Vec vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

void set_vec(Vec* vec, int x, int y) {
    vec->x = x;
    vec->y = y;
}

Vec sum_vec(Vec* a, Vec* b) {
    Vec vec;
    vec.x = a->x + b->x;
    vec.y = a->y + b->y;
    return vec;
}

Vec div_vec(Vec a, int i) {
    Vec vec = a;
    vec.x /= i;
    vec.y /= i;
    return vec;
}


