#ifndef FINALPROJECT_GAME_CONSOLE_H
#define FINALPROJECT_GAME_CONSOLE_H

#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>


char *get_info(SDL_Window *console_window, SDL_Renderer *console_renderer);

void game_launcher(int x,int y);

void game_console_welcome(SDL_Renderer *console_renderer,TTF_Font *font);

void show_exit_button(SDL_Renderer *console_renderer);

#endif //FINALPROJECT_GAME_CONSOLE_H
