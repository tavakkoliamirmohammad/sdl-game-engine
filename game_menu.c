#include "game_menu.h"
#include "board.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include "graphics.h"


extern SDL_Texture **bg_textures;
extern SDL_Texture **wall_textures;
extern TTF_Font *font;
extern int Music_On;

extern int SCREEN_X;
extern int SCREEN_Y;


int showmenu(SDL_Surface *screen, TTF_Font *font, SDL_Renderer *renderer) {
    // returns the selected choice in the menu
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8192);
    Mix_Chunk *select_track = Mix_LoadWAV("sounds\\misc_menu_3.wav");
    Uint32 time;
    int x, y;
    const char *labels[NUMMENU] = {"Continue","New Game","Settings", "Exit"};
    SDL_Surface *menus[NUMMENU];
    bool selected[NUMMENU] = {0};
    SDL_Color color[2] = {{255, 255, 255},
                          {255, 0,   0}};
    menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]); // returning surface
    menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);
    menus[2] = TTF_RenderText_Solid(font, labels[2], color[0]);
    menus[3] = TTF_RenderText_Solid(font,labels[3],color[0]);
    SDL_Texture *texture[NUMMENU];
    SDL_Rect pos[NUMMENU];

    pos[0].x = screen->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
    pos[0].y = screen->clip_rect.h / 2 - menus[0]->clip_rect.h;
    pos[1].x = screen->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
    pos[1].y = screen->clip_rect.h / 2 + menus[1]->clip_rect.h;
    pos[2].x = screen->clip_rect.w / 2 - menus[2]->clip_rect.w / 2;
    pos[2].y = (int)(screen->clip_rect.h / 1.7) + menus[2]->clip_rect.h;
    pos[3].x = screen->clip_rect.w / 2 - menus[3]->clip_rect.w / 2;
    pos[3].y = (int)(screen->clip_rect.h / 1.5) + menus[3]->clip_rect.h;

    int j;
    for (j = 0; j < NUMMENU; ++j) {
        texture[j] = SDL_CreateTextureFromSurface(renderer, menus[j]);
        TTF_SizeText(font, labels[j], &(pos[j].w), &(pos[j].h));
        SDL_RenderCopy(renderer,texture[j],NULL,pos + j);
    }

    SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));

    SDL_Event event;
    while (1) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_FreeSurface(menus[0]);
                    SDL_FreeSurface(menus[1]);
                    SDL_FreeSurface(menus[2]);
                    SDL_FreeSurface(menus[3]);
                    return 3; // changed
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (int i = 0; i < NUMMENU; i += 1) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            if (!selected[i]) {
                                if (Music_On){
                                    Mix_PlayChannel(-1,select_track,0);
                                }
                                selected[i] = 1;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                                texture[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
                                SDL_RenderCopy(renderer,texture[i],NULL,pos + i);
                            }
                            //Mix_FreeChunk(select_track);
                        }
                        else {
                            if (selected[i]) {
                                selected[i] = 0;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                                texture[i] = SDL_CreateTextureFromSurface(renderer, menus[i]);
                                SDL_RenderCopy(renderer,texture[i],NULL,pos + i);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (int i = 0; i < NUMMENU; i += 1) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            SDL_FreeSurface(menus[0]);
                            SDL_FreeSurface(menus[1]);
                            SDL_FreeSurface(menus[2]);
                            SDL_FreeSurface(menus[3]);
                            return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_FreeSurface(menus[0]);
                        SDL_FreeSurface(menus[1]);
                        SDL_FreeSurface(menus[2]);
                        SDL_FreeSurface(menus[3]);
                        return 0;
                    }
            }
        }
        for (int i = 0; i < NUMMENU; i += 1) {
            SDL_BlitSurface(menus[i], NULL, screen, &pos[i]);
        }
        SDL_RenderPresent(renderer);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
}

int start_menu(char *game_name){
    // the game launcher loads the start menu, start menu consists of three parts
    // start game begins the game with default textures
    // in settings, background tiles, wall textures, and audio features are handled
    SDL_Init(SDL_INIT_EVERYTHING);
    font = TTF_OpenFont("ALGER.ttf",SCREEN_Y / 27);
    SDL_Window *start_window;
    SDL_Renderer *start_renderer;
    start_window = SDL_CreateWindow(game_name,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_X,SCREEN_Y,SDL_SWSURFACE);
    start_renderer = SDL_CreateRenderer(start_window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8192);
    Mix_Chunk *select_track = Mix_LoadWAV("sounds\\misc_menu_3.wav");
    const char *labels[NUMSTART] = {"Start Game", "Settings","Exit"};
    SDL_Surface *menus[NUMSTART];
    SDL_Surface *surface;
    surface = SDL_GetWindowSurface(start_window);
    bool selected[NUMSTART] = {0,0,0};
    SDL_Color color[2] = {{255, 255, 255},
                          {255, 0,   0}};
    Uint32 time;

    int i,x,y;
    for (i = 0;i < NUMSTART;++i){
        menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
    }
    SDL_Texture *texture[NUMSTART];
    SDL_Rect pos[NUMSTART];
    pos[0].x = surface->clip_rect.w / 2 - menus[0]->clip_rect.w / 2;
    pos[0].y = surface->clip_rect.h / 2 - menus[0]->clip_rect.h;
    pos[1].x = surface->clip_rect.w / 2 - menus[1]->clip_rect.w / 2;
    pos[1].y = surface->clip_rect.h / 2 + menus[1]->clip_rect.h;
    pos[2].x = surface->clip_rect.w / 2 - menus[2]->clip_rect.w / 2;
    pos[2].y = (int)(surface->clip_rect.h / 1.7) + menus[2]->clip_rect.h;

    for (i = 0;i < NUMSTART;++i){
        texture[i] = SDL_CreateTextureFromSurface(start_renderer, menus[i]);
        TTF_SizeText(font, labels[i], &(pos[i].w), &(pos[i].h));
        SDL_RenderCopy(start_renderer,texture[i],NULL,pos + i);
    }
    SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
    SDL_Event event;
    while (1) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    SDL_FreeSurface(menus[0]);
                    SDL_FreeSurface(menus[1]);
                    SDL_FreeSurface(menus[2]);
                    SDL_DestroyRenderer(start_renderer);
                    for (i = 0;i < NUMSTART;++i){
                        SDL_DestroyTexture(texture[i]);
                    }
                    SDL_DestroyWindow(start_window);
                    return 0;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (i = 0; i < NUMSTART; ++i) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            if (!selected[i]) {
                                if (Music_On){
                                    Mix_PlayChannel(-1,select_track,0);
                                }
                                selected[i] = 1;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                                texture[i] = SDL_CreateTextureFromSurface(start_renderer, menus[i]);
                                SDL_RenderCopy(start_renderer,texture[i],NULL,pos + i);
                            }
                            //Mix_FreeChunk(select_track);
                        }
                        else {
                            if (selected[i]) {
                                selected[i] = 0;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                                texture[i] = SDL_CreateTextureFromSurface(start_renderer, menus[i]);
                                SDL_RenderCopy(start_renderer,texture[i],NULL,pos + i);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (i = 0; i < NUMSTART; ++i) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            SDL_FreeSurface(menus[0]);
                            SDL_FreeSurface(menus[1]);
                            SDL_FreeSurface(menus[2]);
                            SDL_DestroyRenderer(start_renderer);
                            int j;
                            for (j = 0;j < NUMSTART;++j){
                                SDL_DestroyTexture(texture[i]);
                            }
                            SDL_DestroyWindow(start_window);
                            return i;
                            //return i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_FreeSurface(menus[0]);
                        SDL_FreeSurface(menus[1]);
                        SDL_FreeSurface(menus[2]);
                        SDL_DestroyRenderer(start_renderer);
                        for (i = 0;i < NUMSTART;++i){
                            SDL_DestroyTexture(texture[i]);
                        }
                        SDL_DestroyWindow(start_window);
                        return 2;
                    }
            }
        }
        for (i = 0; i < NUMSTART; ++i) {
            SDL_BlitSurface(menus[i], NULL, surface, &pos[i]);
        }
        SDL_RenderPresent(start_renderer);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }


}