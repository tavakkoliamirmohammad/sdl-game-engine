#ifndef FINALPROJECT_MAP_HANDLING_H
#define FINALPROJECT_MAP_HANDLING_H

#include "board.h"
#include "file_handling.h"

char **map_initialize(char *map_file);

struct Board *create_board(struct LinkedList *rules, struct FileData *map_file);

char **map_init(int row, int col);

char *get_controls(struct LinkedList *rules);

void symbol_analyzer(char symbol, struct LinkedList *rules, struct Board *board, int x, int y);

void show_board(struct Board *board);

struct Board *init_board(void);

int get_player_ammo(struct LinkedList *rules);

char get_deathblock_shape(struct LinkedList *rules);

char get_puts_key(struct LinkedList *rules);

int raindb_count(struct LinkedList *rules);

#endif //FINALPROJECT_MAP_HANDLING_H
