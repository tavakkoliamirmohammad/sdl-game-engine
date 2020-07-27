#ifndef FINALPROJECT_GAME_MENU_H
#define FINALPROJECT_GAME_MENU_H

#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

#define NUMMENU 4
#define NUMSETTINGS 4
#define NUMSTART 3

int showmenu(SDL_Surface *screen, TTF_Font *font, SDL_Renderer *renderer);

int start_menu(char *game_name);

#endif //FINALPROJECT_GAME_MENU_H
