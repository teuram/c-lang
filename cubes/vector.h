
#ifndef VECTOR_H
#define VECTOR_H

struct vector {
    int x, y;
} typedef Vec;

void norm_vec(Vec* vec);

Vec new_vec(int x, int y);

void set_vec(Vec* vec, int x, int y);

Vec sum_vec(Vec* a, Vec* b);

Vec div_vec(Vec a, int i);

#endif

