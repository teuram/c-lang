

#ifndef TREE_H
#define TREE_H

typedef struct {
    char string[64];
    char transcription[256];
    char value[256];
} Data;

typedef struct Node;

typedef struct {
    Node* left;
    Node* right;
    char sha256[32];
    Data* data;
} Node;



#endif
