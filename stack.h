#ifndef FINALPROJECT_STACK_H
#define FINALPROJECT_STACK_H

#include "utils.h"

struct Stack {
    struct Point **cells;
    int capacity;
    int length;
};

struct Stack *stack_init(int capacity);

void push_cell(struct Stack *stack, struct Point *point);

struct Point *pop_cell(struct Stack *stack);

#endif //FINALPROJECT_STACK_H
