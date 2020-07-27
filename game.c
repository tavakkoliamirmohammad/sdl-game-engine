//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//#include <stdbool.h>
//#include <float.h>
//#include <SDL2\SDL.h>
//#include <SDL2\SDL_image.h>
//#include "file_handling.h"
////#include "player.h"
//#include "board.h"
//#include "game.h"
//#include <conio.h>
//#include "map_handling.h"
//#include "linked_list.h"
//#include "token2.h"
//#include "bullet.h"
//#include "artificial_opp.h"
//#include "a_star_search.h"
//#include "graphics.h"
//
//enum directions p_dir;
//extern int game_over;
//int in_attack = 0;
//extern bool found_dest;
//
//// the next 2 functions return the direction towards which players are moving
//
//enum directions get_dir(int key_hit, struct Player *player) {
//    if (key_hit == (player->controls)[0])
//        return UP_DIR;
//    if (key_hit == (player->controls)[1])
//        return RIGHT_DIR;
//    if (key_hit == (player->controls)[2])
//        return DOWN_DIR;
//    if (key_hit == (player->controls)[3])
//        return LEFT_DIR;
//    return STATIC_DIR;
//}
//
//int is_player_key(int key_hit, struct Player *player) {
//    return is_available(player->controls, key_hit);
//}
//
//int is_available(char *controls, int key) {
//    int index;
//    for (index = 0; index < strlen(controls); ++index) {
//        if (controls[index] == key) {
//            return 1;
//        }
//    }
//    return 0;
//}
//
//int is_action_command(struct TokenVector *token) {
//    return token->type == ATTACK || token->type == PUT || token->type == RAINDB;
//}
//
//enum token_type action_command(int key_hit, struct LinkedList *rules) {
//    int rules_len, index;
//    rules_len = len(rules);
//    for (index = 0; index < rules_len; ++index) {
//        struct TokenVector *command = (struct TokenVector *) get_data(rules, index);
//        char key = *(char *) get_data(command->info, 0);
//        if (is_action_command(command) && (int) key == key_hit) {
//            return command->type;
//        }
//    }
//}
//
//void attack(int direction, int range, struct Board *board, struct Player *player) {
//    enum directions bullet_dir;
//    struct Bullet *bullet;
//    struct Point *bullet_loc;
//    int index;
//    if (direction == UPARROW) {
//        bullet_dir = UP_DIR;
//        bullet_loc = create_point(player->location->x - 1, player->location->y);
//    }
//    else if (direction == RIGHTARROW) {
//        bullet_dir = RIGHT_DIR;
//        bullet_loc = create_point(player->location->x, player->location->y + 1);
//    }
//    else if (direction == DOWNARROW) {
//        bullet_dir = DOWN_DIR;
//        bullet_loc = create_point(player->location->x + 1, player->location->y);
//    }
//    else if (direction == LEFTARROW) {
//        bullet_dir = LEFT_DIR;
//        bullet_loc = create_point(player->location->x, player->location->y - 1);
//    }
//    else {
//        return;
//    }
//    bullet = create_bullet(BULLET, bullet_dir, bullet_loc);
//    while (!is_blocked(board, bullet_loc) && range > 0 && (board->map)[bullet_loc->x][bullet_loc->y] != board->wall && !score_exists(board -> scores_vector,bullet_loc)) {
//        --range;
//        (board->map)[bullet->location->x][bullet->location->y] = bullet->shape;
//        //delay(1000);
//        //(board -> map)[bullet -> location -> x][bullet -> location -> y] = bullet -> shape = '\0';
//        struct OpponentVector *temp;
//        for (index = 0; board->opponent_vector != NULL && index < board->opponent_vector->length; ++index) {
//            if (opponent_exists((board->opponent_vector->opponents)[index], bullet_loc)) {
////                if ((temp = (delete_opponent(board->opponent_vector, (board->opponent_vector->opponents)[index]))) == NULL) {
////                    board->opponent_vector = NULL;
////                }
//                set_board_cell(board,(board -> opponent_vector->opponents)[index]->location,'\0');
//                board -> opponent_vector = delete_opponent(board -> opponent_vector,(board->opponent_vector->opponents)[index]);
//                //free(bullet);
//            }
//        }
//        (board->map)[bullet->location->x][bullet->location->y] = bullet->shape = '\0';
//        update_bullet_loc(bullet);
//    }
//    free(bullet);
//    free(bullet_loc);
//}
//
//
//void game_play(char *rules_file, char *map_file) {
//    struct FileData *rules_data;
//    struct FileData *map_data;
//    struct LinkedList *rule_list;
//    rules_data = read_file(rules_file);
//    map_data = read_file(map_file);
//    rule_list = get_file_info(rules_data);
//    struct Board *board = create_board(rule_list, map_data);
//
//    system("cls");
//    show_board(board);
//    int command, p_index, p_found, range;
//    enum directions state_p1;
//    state_p1 = STATIC_DIR;
//    p_found = 0;
//    //struct Player *player = (struct Player *)malloc(sizeof(struct Player));
//    //player = (board->players_vector->players)[0];
//    while (board->time > 0 && !game_over) {
//        int opp_index;
//        for (opp_index = 0;board->opponent_vector != NULL && opp_index < board -> opponent_vector -> length;++opp_index){
//            a_star_initialize(board, ((board->opponent_vector->opponents)[opp_index]->location));
//        }
//        //a_star_initialize(board, ((board->opponent_vector->opponents)[0]->location));
//        delay(200);
//        board->time -= 0.02;
////        if (point_equality((board->opponent_vector->opponents)[0]->location,(board->scores_vector->scores)[0]->location)){
////            game_over = 1;
////            return;
////        }
//        SDL_Event event;
//        while (SDL_PollEvent(&event)){
//            switch (event.type){
//                case SDL_KEYDOWN:
//                    command = event.key.keysym.sym;
//                    if (is_player_key(command,board->player)){
//                        board -> player -> state = get_dir(command,board->player);
//                        board->player->location = move(board,board->player,board -> player -> state);
//                    }
//                    attack(command,get_bullet_range(rule_list),board,(board->player));
//            }
//        }
//        struct Point *next_loc;
//        struct Point *target_loc;
//        //target_loc = get_closest_score(board,(board->opponent_vector->opponents)[0]);
//        target_loc = board -> player -> location;
//        if (board -> opponent_vector != NULL){
//            while (((next_loc = a_star_search(board, target_loc)) == NULL));
//        }
//        for (opp_index = 0;board->opponent_vector != NULL && opp_index < board -> opponent_vector -> length;++opp_index){
//            set_board_cell(board, board->opponent_vector->opponents[opp_index]->location, '\0');
//            (board->opponent_vector->opponents)[opp_index]->location = next_loc;
//            set_board_cell(board,next_loc, board->opponent_vector->opponents[opp_index]->symbol);
//        }
//
////        if (found_dest == true){
////            break;
////        }
//
//        if(next_loc == NULL){
//            printf("destination reached\n");
//            return;
//        }
//        check_collision(board);
//        g_show_board(board);
//    }
//}
//
//struct Point *get_closest_score(struct Board *board,struct Opponent *opponent){
//    double min_distance,curr_dist;
//    min_distance = DBL_MAX;
//    int index;
//    for (index = 0;index < board->scores_vector->length;++index){
//        curr_dist = calculate_distance((board->scores_vector->scores)[index]->location,opponent->location);
//        if (curr_dist < min_distance){
//            min_distance = curr_dist;
//        }
//    }
//    for (index = 0;index < board->scores_vector->length;++index){
//        if (calculate_distance((board->scores_vector->scores)[index]->location,opponent->location) == min_distance){
//            return (board->scores_vector->scores)[index]->location;
//        }
//    }
//}
//
//void check_collision(struct Board *board){
//    int index;
//    for (index = 0;board -> opponent_vector != NULL && index < board -> opponent_vector -> length;++index){
//        if (opponent_exists((board -> opponent_vector -> opponents)[index],board -> player -> location)){
//            game_over = 1;
//        }
//    }
//}
//
//void put_death_block(struct LinkedList *rules,struct Board * board){
//    struct Point *loc;
//    struct Block *block;
//    if (board -> player -> ammo > 0){
//        loc = rand_generator(board);
//        block = create_block(get_deathblock_shape(rules),loc,DEATH);
//        board -> blocks_vector = push_block(board -> blocks_vector,block);
//    }
//}