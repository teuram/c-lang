#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node Node;

struct node {
    Node* left;     // zero
    Node* right;    // one
    unsigned int id;
    char name[256];
} typedef Node;

Node* c_node(unsigned int id, char name[]) {
    Node* node = malloc(sizeof(Node));
    if(node == NULL) {
        perror("error: from c_node(), allocation error");
        exit(1);
    }
    node->id = id;
    strcpy(node->name, name);
    return node;
}

void de_node(Node* node) {
    if(node == NULL) {
        return;
    }
    if(node->left != NULL) {
        de_node(node->left);
    }
    if(node->right != NULL) {
        de_node(node->right);
    }
    free(node);
    node = NULL;
}

void add(Node* node, unsigned int id, char name[]) {

    if(id < node->id) {
        if(node->left == NULL) {
            node->left = c_node(id, name);
        } else {
            add(node->left, id, name);
        }
        return;
    }

    if(id > node->id) {
        if(node->right == NULL) {
            node->right = c_node(id, name);
        } else {
            add(node->right, id, name);
        }
        return;
    }

    printf("warning: from add(), element with id %d is contains, ignored", id);

}


char* searth(Node* node, unsigned int id) {

    if(id < node->id) {
        if(node->left == NULL) {
            return NULL;
        } else {
            return searth(node->left, id);
        }
    }

    if(id > node->id) {
        if(node->right == NULL) {
            return NULL;
        } else {
            return searth(node->right, id);
        }
    }

    return node->name;
}

void list(Node* node) {

    if(node->left != NULL) {
        list(node->left);
    }

    if(node->right != NULL) {
        list(node->right);
    }

    printf("id: %u\tname: %s\r\n", node->id, node->name);
}

int main(void) {

    Node* tree = c_node(511, "air");

    add(tree, 280, "stone");
    add(tree, 281, "dark-stone");
    add(tree, 700, "dirt");

    unsigned int id;
    printf("enter id of block: ");
    scanf("%u", &id);

    char* name = searth(tree, id);

    if(name == NULL) {
        printf("block does not exist\n");
        list(tree);
    } else {
        printf("name of block with id %u is %s\r\n", id, searth(tree, id));
    }

    de_node(tree);

    return 0;
}
