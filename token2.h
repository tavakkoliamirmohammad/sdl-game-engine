#include <stdio.h>
#include "linked_list.h"
#include "file_handling.h"

#ifndef TOKEN2_H
#define TOKEN2_H


enum token_type {
    SOLIDBLOCK = 0,
    DEATHBLOCK,
    MOVEBLOCK,
    RPOINT,
    WALL,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    CHARACTER,
    TIME,
    TARGET,
    OBJECT,
    OPP,
    ATTACK,
    PUT,
    RAINDB,
    EXIT

};

struct TokenVector {
    struct LinkedList *info;
    enum token_type type;
};

struct TokenVector *get_line_info(char *line);

int extract_num(char *input, int index);

int get_token_type(char *keyword);

void print_token_vector(struct TokenVector *);

struct TokenVector **init_vector(void);

struct TokenVector *init_vector_pointer(void);


void *reallocation(void *ptr, size_t size);

int getmin(int a, int b);

char *realloc_char(char *s, size_t size, int);

int get_keyword_parameters(char *keyword);


#endif