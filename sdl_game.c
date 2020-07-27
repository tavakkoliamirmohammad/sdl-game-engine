#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <float.h>
#include "file_handling.h"
//#include "player.h"
#include "board.h"
#include "game.h"
#include <conio.h>
#include "map_handling.h"
#include "linked_list.h"
#include "token2.h"
#include "bullet.h"
#include "artificial_opp.h"
#include "a_star_search.h"
#include "syntax_checking.h"
#include "sdl_game.h"
#include "graphics.h"
#include "game_menu.h"
#include "blocks.h"
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include "game_console.h"


enum directions p_dir;
extern int game_over;
extern bool found_dest;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern SDL_Texture *bg_texture;
extern SDL_Texture *player;
extern TTF_Font *font;
int game_started = 0;
int game_won = 0;
extern int Music_On;

extern  int SCREEN_X;
extern int SCREEN_Y;

// the next 2 functions return the direction towards which players are moving

enum directions get_dir(int key_hit, struct Player *player) {
    // return the direction of the player based on the player controls
    if (key_hit == (player->controls)[0])
        return UP_DIR;
    if (key_hit == (player->controls)[1])
        return RIGHT_DIR;
    if (key_hit == (player->controls)[2])
        return DOWN_DIR;
    if (key_hit == (player->controls)[3])
        return LEFT_DIR;
    return STATIC_DIR;
}

int is_player_key(int key_hit, struct Player *player) {
    // check whether the given key is the player key
    return is_available(player->controls, key_hit);
}

int is_available(char *controls, int key) {
    // check whether the key is valid
    int index;
    for (index = 0; index < strlen(controls); ++index) {
        if (controls[index] == key) {
            return 1;
        }
    }
    return 0;
}

int is_action_command(struct TokenVector *token) {
    return token->type == ATTACK || token->type == PUT || token->type == RAINDB;
}

enum token_type action_command(int key_hit, struct LinkedList *rules) {
    int rules_len, index;
    rules_len = len(rules);
    for (index = 0; index < rules_len; ++index) {
        struct TokenVector *command = (struct TokenVector *) get_data(rules, index);
        char key = *(char *) get_data(command->info, 0);
        if (is_action_command(command) && (int) key == key_hit) {
            return command->type;
        }
    }
}

void attack(int direction, int range, struct Board *board, struct Player *player) {
    enum directions bullet_dir;
    struct Bullet *bullet;
    struct Point *bullet_loc;
    int index;
    if (direction == SDLK_UP) {
        bullet_dir = UP_DIR;
        bullet_loc = create_point(player->location->x - 1, player->location->y);
    }
    else if (direction == SDLK_RIGHT) {
        bullet_dir = RIGHT_DIR;
        bullet_loc = create_point(player->location->x, player->location->y + 1);
    }
    else if (direction == SDLK_DOWN) {
        bullet_dir = DOWN_DIR;
        bullet_loc = create_point(player->location->x + 1, player->location->y);
    }
    else if (direction == SDLK_LEFT) {
        bullet_dir = LEFT_DIR;
        bullet_loc = create_point(player->location->x, player->location->y - 1);
    }
    else {
        return;
    }
    bullet = create_bullet(BULLET, bullet_dir, bullet_loc);
    player -> bullet = bullet;
    while (!is_ord_blocked(board, bullet_loc) && range > 0 && (board->map)[bullet_loc->x][bullet_loc->y] != board->wall && !score_exists(board -> scores_vector,bullet_loc)) {
        --range;
        (board->map)[bullet->location->x][bullet->location->y] = bullet->shape;
        //delay(1000);
        //(board -> map)[bullet -> location -> x][bullet -> location -> y] = bullet -> shape = '\0';
        struct OpponentVector *temp;
        for (index = 0; board->opponent_vector != NULL && index < board->opponent_vector->length; ++index) {
            if (opponent_exists((board->opponent_vector->opponents)[index], bullet_loc)) {
//                if ((temp = (delete_opponent(board->opponent_vector, (board->opponent_vector->opponents)[index]))) == NULL) {
//                    board->opponent_vector = NULL;
//                }
                set_board_cell(board,(board -> opponent_vector->opponents)[index]->location,'\0');
                board -> opponent_vector = delete_opponent(board -> opponent_vector,(board->opponent_vector->opponents)[index]);
                //free(bullet);
            }
        }
        for(index = 0; board->raining_blocks != NULL && index < board->raining_blocks->length; ++index){
            if(point_equality((board->raining_blocks->blocks)[index]->location, bullet_loc)){
                set_board_cell(board,(board -> raining_blocks->blocks)[index]->location,'\0');
                remove_block(board->raining_blocks, (board -> raining_blocks->blocks)[index]);
                break;
            }
        }
        (board->map)[bullet->location->x][bullet->location->y] = '\0';
        update_bullet_loc(bullet);
    }
    //free(bullet);
    //free(bullet_loc);
}


int game_play(struct FileData *rules_data, struct FileData *map_data) {
//    struct FileData *rules_data;
//    struct FileData *map_data;
    struct LinkedList *rule_list;
//    rules_data = read_file(rules_file);
//    map_data = read_file(map_file);
//
//    if (map_data == NULL || rules_data == NULL){
//        // a window opens and show that the file didn't open
//        system("vlc -I dummy --dummy-quiet --fullscreen videos\\file_not_found.mkv vlc://quit\n");
//        return -2;
//    }
    int correct_syntax;
    rules_data -> file_position = 0;
    correct_syntax = check_syntax(rules_data);
    rules_data -> file_position = 0;
    if (!correct_syntax){
        return -1;
    }
    rule_list = get_file_info(rules_data);
    struct Board *board = create_board(rule_list, map_data);
    init_graphical_utils(board);
    game_started = 1;
    g_show_board(board);
    //show_maze_map(board);
    int command, p_index, p_found, range,exit_flag,event_type,res;
    char puts_key;
    char death_shape;
    enum directions state_p1;
    state_p1 = STATIC_DIR;
    p_found = 0;
    exit_flag = 0;
    res = 0;
    puts_key = get_puts_key(rule_list);
    death_shape = get_deathblock_shape(rule_list);
    while (board->time > 0 && !game_over && !game_won) {
        //show_game_time(board);
        int opp_index;
//        for (opp_index = 0;board->opponent_vector != NULL && opp_index < board -> opponent_vector -> length;++opp_index){
//            a_star_initialize(board, ((board->opponent_vector->opponents)[opp_index]->location));
//        }
        delay(200);
        board->time -= 0.2;
        rain_death_block(board,death_shape);
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_KEYDOWN:
                    command = event.key.keysym.sym;
                    music_handler(command);
                    if (is_player_key(command, board->player)) {
                        board->player->state = get_dir(command, board->player);
                        board->player->location = move(board, board->player, board->player->state);
                    }
                    if (command == puts_key) {
                        put_death_block(rule_list, board); // optimizing by passing the shape instead of rule list
                    }
                    if (command == SDLK_ESCAPE) {
                        Mix_Pause(-1);
                        SDL_Init(SDL_INIT_EVERYTHING);
                        SDL_Window *screen;
                        SDL_Renderer *menu_renderer;
                        screen = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
                                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, SDL_SWSURFACE);
                        menu_renderer = SDL_CreateRenderer(screen, -1,
                                                           SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                        SDL_Surface *surface;
                        surface = SDL_GetWindowSurface(screen);

                        TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
                        while (res = (showmenu(surface, font, menu_renderer))) {
//                            if(res == 0){
//                                SDL_RenderClear(menu_renderer);
//                                SDL_DestroyRenderer(menu_renderer);
//                                SDL_FreeSurface(surface);
//                                SDL_DestroyWindow(screen);
//                                break;
//                            }
                            if (res == 1) {
                                free_board(board); // not this free
                                SDL_RenderClear(menu_renderer);
                                SDL_DestroyRenderer(menu_renderer);
                                SDL_FreeSurface(surface);
                                SDL_DestroyWindow(screen);
                                SDL_DestroyRenderer(renderer);
                                SDL_DestroyWindow(window);
//                                Mix_FreeChunk()
//                                Mix_CloseAudio();
                                //SDL_Quit();
                                return 0;
                            }
                            if (res == 2) {
                                game_settings();
                                continue;
                            }
                            if (res == 3) { // !!!!!!clearing all pointers!!!!!!!!!!
//                                SDL_RenderClear(menu_renderer);
//                                SDL_DestroyRenderer(menu_renderer);
//                                SDL_FreeSurface(surface);
//                                SDL_DestroyWindow(screen);
//                                SDL_DestroyWindow(window);
//                                SDL_Quit();
                                return 1;
                            }
                        }
                        Mix_Resume(-1);
                        if (res == 0){
                            SDL_RenderClear(menu_renderer);
                            SDL_DestroyRenderer(menu_renderer);
                            SDL_FreeSurface(surface);
                            SDL_DestroyWindow(screen);
                        }
                        break;

                        //SDL_RenderClear(renderer);
                        //SDL_DestroyRenderer(renderer);
                        //SDL_DestroyWindow(screen);
                    }
                    if (command == SDLK_UP || command == SDLK_RIGHT || command == SDLK_DOWN || command == SDLK_LEFT) {
                        attack(command, get_bullet_range(rule_list), board, (board->player));
                    }
            }

        }
        struct Point *next_loc;
        struct Point *target_loc;
        target_loc = board -> player -> location;
        for (opp_index = 0;board->opponent_vector != NULL && opp_index < board -> opponent_vector -> length;++opp_index){
            a_star_initialize(board, ((board->opponent_vector->opponents)[opp_index]->location));
            while (((next_loc = a_star_search(board, target_loc)) == NULL));
            set_board_cell(board, board->opponent_vector->opponents[opp_index]->location, '\0');
            (board->opponent_vector->opponents)[opp_index]->location = next_loc;
            set_board_cell(board,next_loc, board->opponent_vector->opponents[opp_index]->symbol);
            a_star_close(board);
        }
        check_collision(board);
        check_for_target(board);
        g_show_board(board);
    }
    if (board -> time <= 0 && !game_over){
        system("vlc -I dummy --dummy-quiet --fullscreen videos\\win.mkv vlc://quit\n");
        game_over = 0;
        game_launcher(SCREEN_X,SCREEN_Y);

    }
    if (game_over){
        system("vlc -I dummy --dummy-quiet --fullscreen videos\\game_over.mkv vlc://quit\n");
        game_over = 0;
        game_launcher(SCREEN_X,SCREEN_Y);
    }
    else if (game_won){
        system("vlc -I dummy --dummy-quiet --fullscreen videos\\win.mkv vlc://quit\n");
        game_won = 0;
        game_launcher(SCREEN_X,SCREEN_Y);
    }
    return 1;
}

struct Point *get_closest_score(struct Board *board,struct Opponent *opponent){
    double min_distance,curr_dist;
    min_distance = DBL_MAX;
    int index;
    for (index = 0;index < board->scores_vector->length;++index){
        curr_dist = calculate_distance((board->scores_vector->scores)[index]->location,opponent->location);
        if (curr_dist < min_distance){
            min_distance = curr_dist;
        }
    }
    for (index = 0;index < board->scores_vector->length;++index){
        if (calculate_distance((board->scores_vector->scores)[index]->location,opponent->location) == min_distance){
            return (board->scores_vector->scores)[index]->location;
        }
    }
}



void check_collision(struct Board *board){
    int index;
    for (index = 0;board -> opponent_vector != NULL && index < board -> opponent_vector -> length;++index){
        if (opponent_exists((board -> opponent_vector -> opponents)[index],board -> player -> location)){
            game_over = 1;
        }
    }
    for(index = 0; board->raining_blocks != NULL && index < board->raining_blocks->length; ++index){
        if(point_equality((board->raining_blocks->blocks)[index]->location, board->player->location)){
            game_over = 1;
        }
    }
}

void put_death_block(struct LinkedList *rules,struct Board * board){
    // attack and put death block
    struct Point *loc;
    struct Block *block;
    if (board -> player -> ammo > 0){
        loc = rand_generator(board);
        block = create_block(get_deathblock_shape(rules),loc,DEATH);
        board -> blocks_vector = push_block(board -> blocks_vector,block);
        board -> player -> ammo -= 1;
    }
}

void check_for_target(struct Board *board){
    // check whether the player reached the target
    if (board == NULL || board -> target == NULL || board -> player == NULL){
        return;
    }
    if (point_equality(board -> player -> location,board -> target -> location)){
        game_won = 1;
    }
}
