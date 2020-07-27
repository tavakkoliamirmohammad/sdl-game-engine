#include <stdlib.h>
#include "player.h"

int player_dir(char key_hit,struct Player *player){
    int index;
    for (index = 0;index < DIRS;++index){
        if ((player -> controls)[index] == key_hit){
            return index;
        }
    }
    return -1;
}

int player_exists(struct Player *player,struct Point *loc){
    return point_equality(player -> location,loc);
}

struct Player *create_player(struct Point *loc,char symbol,char *controls,int score,int ammo,struct Bullet *bullet,enum directions state,enum player_type type){
    struct Player *player = (struct Player *)malloc(sizeof(struct Player));
    player -> location = loc;
    player -> symbol = symbol;
    player -> controls = controls;
    player -> score = score;
    player -> ammo = ammo;
    player -> bullet = bullet;
    player -> type = type;
    player -> state = STATIC_DIR;
    return player;
}

struct PlayerVector *push_player(struct PlayerVector *player_vector,struct Player *player){
    int len;
    if (player == NULL){
        return player_vector;
    }
    if (player_vector == NULL){
        player_vector = (struct PlayerVector *)malloc(sizeof(struct PlayerVector));
        player_vector -> length = 1;
    }
    else {
        len = player_vector -> length;
        ++(player_vector -> length);
        // attention!!!!
        player_vector = (struct PlayerVector *)my_realloc(player_vector,(len+1) * sizeof(struct PlayerVector));
    }
    if (player_vector -> length == 1){
        player_vector->players = (struct Player **)malloc(sizeof(struct Player *));
    }
    else{
        len = player_vector -> length;
        player_vector->players = (struct Player **)my_realloc(player_vector->players,(len+1) * sizeof(struct Player *));
    }
    (player_vector->players)[player_vector->length - 1] = (struct Player *)malloc(sizeof(struct Player));
    (player_vector -> players)[player_vector -> length - 1] = copy_player(player);
    return player_vector;

}

struct Player *copy_player(struct Player *player){
    struct Player *new_player = (struct Player *)malloc(sizeof(struct Player));
    new_player -> location = create_point(player->location->x,player->location->y);
    new_player -> symbol = player -> symbol;
    new_player -> controls = player -> controls;
    new_player -> score = player -> score;
    new_player -> ammo = player -> ammo;
    new_player -> bullet = copy_bullet(player -> bullet);
    new_player -> type = player -> type;
    new_player->state = player->state;
    return new_player;
}

void free_player(struct Player* player){
    if(player == NULL){
        return;
    }
    free(player->location);
    if(player->bullet != NULL){
        free(player->bullet);
        free(player->bullet->location);
    }

    free(player->controls);
    free(player);
}
