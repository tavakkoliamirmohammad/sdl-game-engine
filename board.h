#ifndef BOARD_H
#define BOARD_H

#include "utils.h"
#include "blocks.h"
#include "player.h"
#include "board.h"
#include "target.h"
#include "score.h"
#include "object.h"
#include "artificial_opp.h"
#include "linked_list.h"

struct Board {
    struct BlockVector *blocks_vector; // array of blocks
    struct BlockVector *raining_blocks;
    struct ScoreVector *scores_vector; // array of scores
    struct Player *player;
    struct OpponentVector *opponent_vector;
    struct LinkedList *block_shapes;
    struct LinkedList *score_shapes;
    struct LinkedList *player_shapes;
    struct LinkedList *opponent_shapes;
    struct Target *target;
    struct Object *object;
    char wall;
    char **map; // board representation
    int row, col, raining_block_count;
    double time;
};


void delay(unsigned int ms);

void set_position(int x, int y);

void hidecursor(void);

int is_blocked(struct Board *board, struct Point *loc);

struct Score *is_score(struct Board *board, struct Point *loc);

void add_score(struct Board *board, struct Player *player);

struct Point *rand_generator(struct Board *board);

struct Point *rand_death_loc(struct Board *board);

int is_cell_empty(struct Board *board, struct Point *loc);

char *get_board_cell(struct Board *board, struct Point *loc);

struct Player *get_board_player(struct Board *board, int index);

struct Point *moving_allowed(struct Board *board, struct Point *loc, enum directions dir);

struct Point *move(struct Board *board, struct Player *player, enum directions dir);

void set_board_cell(struct Board *board, struct Point *loc, char symbol);

int inside_board(struct Board *board, struct Point *loc);

void remove_score(struct Board *board, struct Score *score);

void score_fill(struct Board *board, char shape, int value, int count);

int access_allowed(struct Board *board, struct Point *loc);

void check_for_deathblock(struct Board *board, struct Player *player);

void init_board_raindb(struct Board *board, char shape);

void rain_death_block(struct Board *board, char shape);

struct Block *get_moving_block(struct Board *board, struct Point *loc);

void move_block(struct Board *board);

int is_opponent(struct Board *board, struct Point *loc);

int is_ord_blocked(struct Board *board, struct Point *loc);

int is_rain_block(struct Board* board, struct Point* loc);

struct Point *moving_block_access_allowed(struct Board *board, struct Point *loc, enum directions dir);

void
initialize_board(struct Board *board, struct LinkedList *blocks, struct LinkedList *scores, struct LinkedList *players,
                 struct LinkedList *block_shapes, struct LinkedList *score_shapes, struct LinkedList *player_shapes,
                 char wall,
                 char **map, int row, int col);

void free_board(struct Board *board);

#endif