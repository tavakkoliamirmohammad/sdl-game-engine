#ifndef PLAYER_H
#define PLAYER_H

#include "utils.h"
#include "bullet.h"
//#include "board.h"

#define DIRS 4

enum player_type {
    USER, OPPONENT
};


struct Player {
    struct Point *location;
    char symbol, *controls;
    int score;
    int ammo;
    struct Bullet *bullet;
    enum directions state;
    enum player_type type;
};

struct PlayerVector {
    struct Player **players;
    unsigned int length;
};

int player_dir(char key_hit, struct Player *player);

int player_exists(struct Player *player, struct Point *loc);

struct Player *create_player(struct Point *loc,char symbol,char *controls,int score,int ammo,struct Bullet *bullet,enum directions state,enum player_type type);

struct PlayerVector *push_player(struct PlayerVector *player_vector, struct Player *player);

struct Player *copy_player(struct Player *player);

void free_player(struct Player* player);

#endif