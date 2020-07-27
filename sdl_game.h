#ifndef FINALPROJECT_SDL_GAME_H
#define FINALPROJECT_SDL_GAME_H

#include "player.h"
#include "board.h"
#include "file_handling.h"
#include "token2.h"

enum directions get_dir(int key_hit, struct Player *player);

int game_play(struct FileData *rules_data, struct FileData *map_data);

int is_player_key(int key_hit, struct Player *player);

int is_available(char *controls, int key);

void attack(int direction, int range, struct Board *board, struct Player *player);

struct Point *get_closest_score(struct Board *board, struct Opponent *opponent);

void put_death_block(struct LinkedList *rules, struct Board *board);

void check_collision(struct Board *board);

void check_for_target(struct Board *board);

int is_action_command(struct TokenVector *token);

struct Point *get_closest_score(struct Board *board, struct Opponent *opponent);

#endif //FINALPROJECT_SDL_GAME_H
