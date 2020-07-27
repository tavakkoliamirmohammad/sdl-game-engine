#ifndef FINALPROJECT_GRAPHICS_H
#define FINALPROJECT_GRAPHICS_H

#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include "board.h"

SDL_Texture *load_texture(char *path);

void init_graphical_utils(struct Board *board);

void draw_texture(SDL_Texture *texture, int x, int y, struct Board *board);

int get_matching_index(struct Score *score);

void g_show_board(struct Board *board);

void show_game_time(struct Board *board);

void show_player_score(struct Board *board);

SDL_Texture *load_font_texture(TTF_Font *font,SDL_Color color,char *label);

void show_details_board(struct Board *board);

void draw_font_texture(SDL_Texture *font_texture,int x,int y);


SDL_Texture *general_load_texture(char *path,SDL_Renderer *new_renderer);

void general_draw_texture(SDL_Texture *texture,SDL_Renderer *target_renderer,int x,int y);

void music_handler(int select_key);

void show_player_avatar(struct Board *board);

void show_opponent_avatar(struct Board *board);

int game_settings(void);

#endif //FINALPROJECT_GRAPHICS_H
