#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include "a_star_search.h"
#include "heap.h"
#include "artificial_opp.h"
#include "utils.h"
#include "stack.h"
#include "score.h"

bool found_dest;
bool **ClosedList;
struct MinHeap *OpenList;
struct CellDetail **cell_details;

extern char empty_cell;

double calculate_h_value(struct Point *src, struct Point *dest) {
    // calculate heuristic (euclidean distance)value
    return sqrt(pow(src->x - dest->x, 2) + pow(src->y - dest->y, 2));
}

int is_destination(struct Point *loc, struct Point *dest) {
    // return whether the destination is reached
    return point_equality(loc, dest);
}

int is_unblocked(struct Board *board, struct Point *loc) {
    return (!is_blocked(board, loc) && !player_exists(board->player, loc));

}

struct Point *a_star_search(struct Board *board, struct Point *dest) {// free target cell
    if (is_empty(OpenList) || found_dest || board == NULL) {
        return NULL;
    }
    struct Cell *target_cell;
    target_cell = heap_extract_min(OpenList);
    int cell_x, cell_y;
    cell_x = target_cell->point->x;
    cell_y = target_cell->point->y;
    ClosedList[cell_x][cell_y] = true;
    double new_g, new_h, new_f;
    // 1st successor (North)
    struct Point *north_loc;
    north_loc = create_point(cell_x - 1, cell_y);
    if (inside_board(board, north_loc)) {
        if (is_destination(north_loc, dest)) {
            cell_details[cell_x - 1][cell_y].parent_i = cell_x;
            cell_details[cell_x - 1][cell_y].parent_j = cell_y;
            found_dest = true;
            return trace_path(board, dest);
        }
        else if (ClosedList[cell_x - 1][cell_y] == false && access_allowed(board, north_loc) &&
                 !score_exists(board->scores_vector, north_loc)) {
            new_g = cell_details[cell_x][cell_y].g + 1.0;
            new_h = calculate_h_value(north_loc, dest);
//            printf("(north) new g %f new h: %f\n", new_g, new_h);
            new_f = new_g + new_h;
            if (cell_details[cell_x - 1][cell_y].f == DBL_MAX || new_f < cell_details[cell_x - 1][cell_y].f) {
                heap_insert_key(OpenList, new_f, cell_x - 1, cell_y);
                cell_details[cell_x - 1][cell_y].f = new_f;
                cell_details[cell_x - 1][cell_y].g = new_g;
                cell_details[cell_x - 1][cell_y].h = new_h;
                cell_details[cell_x - 1][cell_y].parent_i = cell_x;
                cell_details[cell_x - 1][cell_y].parent_j = cell_y;
            }
        }
    }
    // 2nd successor (South)
    struct Point *south_loc;
    south_loc = create_point(cell_x + 1, cell_y);
    if (inside_board(board, south_loc)) {
        if (is_destination(south_loc, dest)) {
            cell_details[cell_x + 1][cell_y].parent_i = cell_x;
            cell_details[cell_x + 1][cell_y].parent_j = cell_y;
            found_dest = true;
            return trace_path(board, dest);
        }
        else if (ClosedList[cell_x + 1][cell_y] == false && access_allowed(board, south_loc) &&
                 !score_exists(board->scores_vector, south_loc)) {
            new_g = cell_details[cell_x][cell_y].g + 1.0;
            new_h = calculate_h_value(south_loc, dest);
//            printf("(South) new h: %f\n", new_h);
            new_f = new_g + new_h;
//            printf("south f value %f\n", new_f);
            if (cell_details[cell_x + 1][cell_y].f == DBL_MAX || new_f < cell_details[cell_x + 1][cell_y].f) {
                heap_insert_key(OpenList, new_f, cell_x + 1, cell_y);
                cell_details[cell_x + 1][cell_y].f = new_f;
                cell_details[cell_x + 1][cell_y].g = new_g;
                cell_details[cell_x + 1][cell_y].h = new_h;
                cell_details[cell_x + 1][cell_y].parent_i = cell_x;
                cell_details[cell_x + 1][cell_y].parent_j = cell_y;
            }
        }
    }
    // 3rd successor (West)
    struct Point *west_loc;
    west_loc = create_point(cell_x, cell_y - 1);
    if (inside_board(board, west_loc)) {
        if (is_destination(west_loc, dest)) {
            cell_details[cell_x][cell_y - 1].parent_i = cell_x;
            cell_details[cell_x][cell_y - 1].parent_j = cell_y;
            found_dest = true;
            return trace_path(board, dest);
        }
        else if (ClosedList[cell_x][cell_y - 1] == false && access_allowed(board, west_loc) &&
                 !score_exists(board->scores_vector, west_loc)) {
            new_g = cell_details[cell_x][cell_y].g + 1.0;
            new_h = calculate_h_value(west_loc, dest);
//            printf("(west) new g %f new h: %f\n", new_g, new_h);
            new_f = new_g + new_h;
//            printf("west f value %f\n", new_f);
            if (cell_details[cell_x][cell_y - 1].f == DBL_MAX || new_f < cell_details[cell_x][cell_y + 1].f) {
                heap_insert_key(OpenList, new_f, cell_x, cell_y - 1);
                cell_details[cell_x][cell_y - 1].f = new_f;
                cell_details[cell_x][cell_y - 1].g = new_g;
                cell_details[cell_x][cell_y - 1].h = new_h;
                cell_details[cell_x][cell_y - 1].parent_i = cell_x;
                cell_details[cell_x][cell_y - 1].parent_j = cell_y;
            }
        }
    }
    // 4th successor (East)
    struct Point *east_loc;
    east_loc = create_point(cell_x, cell_y + 1);
    if (inside_board(board, east_loc)) {
        if (is_destination(east_loc, dest)) {
            cell_details[cell_x][cell_y + 1].parent_i = cell_x;
            cell_details[cell_x][cell_y + 1].parent_j = cell_y;
            found_dest = true;
            return trace_path(board, dest);
        }
        else if (ClosedList[cell_x][cell_y + 1] == false && access_allowed(board, east_loc) &&
                 !score_exists(board->scores_vector, east_loc)) {
            new_g = cell_details[cell_x][cell_y].g + 1.0;
            new_h = calculate_h_value(east_loc, dest);
//            printf("(east) new g %f new h: %f\n", new_g, new_h);
            new_f = new_g + new_h;
//            printf("east f value %f\n", new_f);
            if (cell_details[cell_x][cell_y + 1].f == DBL_MAX || new_f < cell_details[cell_x][cell_y + 1].f) {
                heap_insert_key(OpenList, new_f, cell_x, cell_y + 1);
                cell_details[cell_x][cell_y + 1].f = new_f;
                cell_details[cell_x][cell_y + 1].g = new_g;
                cell_details[cell_x][cell_y + 1].h = new_h;
                cell_details[cell_x][cell_y + 1].parent_i = cell_x;
                cell_details[cell_x][cell_y + 1].parent_j = cell_y;
            }
        }
    }

    return NULL;

}

void a_star_initialize(struct Board *board, struct Point *src) {
    OpenList = initialize_min_heap(board->row * board->col);
    found_dest = false;
    int row_index, col_index;
    ClosedList = (bool **) malloc(board->row * sizeof(bool *));
    cell_details = (struct CellDetail **) malloc(board->row * sizeof(struct CellDetail *));
    for (row_index = 0; row_index < board->row; ++row_index) {
        ClosedList[row_index] = (bool *) malloc(board->col * sizeof(bool));
        cell_details[row_index] = (struct CellDetail *) malloc(board->col * sizeof(struct CellDetail));
    }
    for (row_index = 0; row_index < board->row; ++row_index) {
        for (col_index = 0; col_index < board->col; ++col_index) {
            cell_details[row_index][col_index].f = DBL_MAX;
            cell_details[row_index][col_index].g = DBL_MAX;
            cell_details[row_index][col_index].h = DBL_MAX;
            cell_details[row_index][col_index].parent_i = -1;
            cell_details[row_index][col_index].parent_j = -1;
            ClosedList[row_index][col_index] = false;
        }
    }
    cell_details[src->x][src->y].f = 0.0;
    cell_details[src->x][src->y].g = 0.0;
    cell_details[src->x][src->y].h = 0.0;
    cell_details[src->x][src->y].parent_i = src->x;
    cell_details[src->x][src->y].parent_j = src->y;
    heap_insert_key(OpenList, 0.0, src->x, src->y);
}


struct Point *trace_path(struct Board *board, struct Point *dest) {
    int row;
    row = dest->x;
    int col;
    col = dest->y;
    struct Stack *stack;
    stack = stack_init((board->row * board->col) + 1);
    while (!(cell_details[row][col].parent_i == row
             && cell_details[row][col].parent_j == col)) {
        push_cell(stack, create_point(row, col));
        int temp_row;
        temp_row = cell_details[row][col].parent_i;
        int temp_col;
        temp_col = cell_details[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    struct Point *temp;
    temp = create_point(row, col);
    push_cell(stack, temp);
    if (stack->length == 1) {
        return pop_cell(stack);
    }
    pop_cell(stack);
    struct Point *res;
    res = pop_cell(stack);
    while (stack->length != 0) {
        pop_cell(stack);
    }
    return res;
}

void a_star_close(struct Board *board) {
//    OpenList = initialize_min_heap(board->row * board->col);
    int row_index, col_index;
    for (row_index = 0; row_index < board->row; ++row_index) {
        free(ClosedList[row_index]);
        free(cell_details[row_index]);
    }
    free(cell_details);
    free(ClosedList);
    free(OpenList->pCell);
    free(OpenList);
}