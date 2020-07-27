#ifndef FINALPROJECT_A_STAR_SEARCH_H
#define FINALPROJECT_A_STAR_SEARCH_H

#include "board.h"

struct CellDetail {
    double f, g, h; // g = cost_value, h = heuristic_value, f = g + h
    int parent_i, parent_j;
};

double calculate_h_value(struct Point *src, struct Point *dest);

int is_destination(struct Point *loc, struct Point *dest);

struct Point *a_star_search(struct Board *board, struct Point *dest);

void a_star_initialize(struct Board *board, struct Point *src);

struct Point *trace_path(struct Board *board, struct Point *dest);

void a_star_close(struct Board *board);

int is_unblocked(struct Board *board, struct Point *loc);

#endif //FINALPROJECT_A_STAR_SEARCH_H
