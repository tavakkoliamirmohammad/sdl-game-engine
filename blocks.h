#ifndef BLOCKS_H
#define BLOCKS_H

#include "utils.h"

enum block_type {
    SOLID, DEATH, MOVE

};

struct Block {
    char shape;
    struct Point *location;
    enum block_type type;
};


struct BlockVector {
    struct Block **blocks;
    unsigned int length;
};

struct BlockVector *push_block(struct BlockVector *blocks, struct Block *block);

struct Block *copy_block(struct Block *block);

struct Block *create_block(char shape, struct Point *loc, enum block_type type);

int block_equality(struct Block *block1, struct Block *block2);

struct Block *search_block(struct BlockVector *block_vector, struct Point *loc);

void remove_block(struct BlockVector *block_vector, struct Block *block);

void shift_block(struct BlockVector *block_vector, int index);

void free_block(struct Block *block);

void free_block_vector(struct BlockVector *blockVector);

#endif