#include <stdlib.h>
#include "blocks.h"


struct BlockVector *push_block(struct BlockVector *block_vector, struct Block *block) {
    int len;
    if (block == NULL) {
        return block_vector;
    }
    if (block_vector == NULL) {
        block_vector = (struct BlockVector *) malloc(sizeof(struct BlockVector));
        block_vector->length = 1;
    }
    else {
        len = block_vector->length;
        block_vector->length += 1;
        block_vector = (struct BlockVector *) my_realloc(block_vector, (len + 1) * sizeof(struct BlockVector));
    }
    if (block_vector->length == 1) {
        block_vector->blocks = (struct Block **) malloc(sizeof(struct Block *));
    }
    else {
        len = block_vector->length;
        block_vector->blocks = (struct Block **) my_realloc(block_vector->blocks, (len + 1) * sizeof(struct Block *));
    }
    (block_vector->blocks)[block_vector->length - 1] = (struct Block *) malloc(sizeof(struct Block));
    (block_vector->blocks)[block_vector->length - 1] = copy_block(block);
    return block_vector;
}

struct Block *create_block(char shape,struct Point *loc,enum block_type type){
    struct Block *block = (struct Block *)malloc(sizeof(struct Block));
    block -> shape = shape;
    block -> location = loc;
    block -> type = type;
    return block;
}

struct Block *copy_block(struct Block *block) {
    struct Block *new_block = (struct Block *) malloc(sizeof(struct Block));
    new_block->location = create_point(block->location->x, block->location->y);
    new_block->shape = block->shape;
    new_block->type = block->type;
    return new_block;
}

int block_equality(struct Block *block1, struct Block *block2) {
    return point_equality(block1->location, block2->location) && block1->type == block2->type &&
           block1->shape == block2->shape;
}

struct Block *search_block(struct BlockVector *block_vector, struct Point *loc) {
    int index;
    for (index = 0;block_vector != NULL && index < block_vector->length; ++index) {
        if (point_equality((block_vector->blocks)[index] -> location,loc)){
            return (block_vector->blocks)[index];
        }
    }
    return NULL;
}

void remove_block(struct BlockVector *block_vector,struct Block *block){
    int index;
    for (index = 0;block_vector != NULL && index < block_vector -> length;++index){
        if (block_equality(block,(block_vector->blocks)[index])){
            free((block_vector -> blocks)[index] -> location);
            free((block_vector -> blocks)[index]);
            shift_block(block_vector,index + 1);
            --(block_vector -> length);
            break;
        }
    }
}

void shift_block(struct BlockVector *block_vector,int index){
    int i;
    for (i = index;block_vector != NULL && i < block_vector -> length;++i){
        (block_vector -> blocks)[i - 1] = (block_vector -> blocks)[i];
    }
}

void free_block(struct Block *block){
    free(block->location);
    free(block);
}

void free_block_vector(struct BlockVector *blockVector){
    if(blockVector == NULL){
        return;
    }
    int i;
    for(i = 0; i < blockVector->length; ++i){
        free_block((blockVector->blocks)[i]);
    }
    free(blockVector);
}
