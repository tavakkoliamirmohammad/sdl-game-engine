#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct Stack *stack_init(int capacity) {
    struct Stack *stack = (struct Stack *) malloc(sizeof(struct Stack));
    stack->cells = (struct Point **) malloc(capacity * sizeof(struct Point*));
    stack->length = 0;
    stack->capacity = capacity;
    return stack;
}

void push_cell(struct Stack *stack, struct Point *point) {
    if (stack->length >= stack->capacity) {
        return;
    }
    (stack->cells)[stack->length] = point;
    ++(stack->length);
}

struct Point *pop_cell(struct Stack *stack) {
    if (stack->length <= 0) {
        return NULL;
    }
    // **************freeee*******************
    --(stack->length);
    return (stack->cells)[stack->length];
}