#include "graphics.h"
#include "sdl_game.h"
#include "game_console.h"
#include "game_menu.h"
#include "file_handling.h"
#
#include <stdio.h>
#include <string.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_ttf.h>

extern int SCREEN_X;
extern int SCREEN_Y;

extern int player_type;

extern TTF_Font *font;

char *get_info(SDL_Window *console_window, SDL_Renderer *console_renderer) {
    // getting the name of the game and the avatar from the user, returning the game name to the game launcher
    SDL_Color color = {0, 255, 0};
    SDL_Texture *txt_texture;
    TTF_Init();
    font = TTF_OpenFont("ALGER.ttf", SCREEN_Y / 27);
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
    SDL_Surface *surface;
    SDL_bool done = SDL_FALSE;
    SDL_Rect text_rect;
    SDL_Rect input_box;
    SDL_StartTextInput();


    text_rect.x = text_rect.y = 20;
    text_rect.w = 1000;
    text_rect.h = 50;
    input_box.x = input_box.y = 20;
    input_box.w = 300;
    input_box.h = 100;


    SDL_Texture *ordinary_avatar;
    SDL_Texture *sprite_avatar;
    ordinary_avatar = general_load_texture("images\\ord_avatar.png", console_renderer);
    sprite_avatar = general_load_texture("images\\stand1.png", console_renderer);
    SDL_Rect ord_rect, sprite_rect;
    int ord_x, ord_y, sprite_x, sprite_y;
    sprite_y = ord_y = 3 * SCREEN_Y / 4;
    ord_x = SCREEN_X / 2 - SCREEN_X / 8;
    sprite_x = SCREEN_X / 2 + SCREEN_X / 8;
    ord_rect.x = ord_x;
    ord_rect.y = ord_y;
    sprite_rect.x = sprite_x;
    sprite_rect.y = sprite_y;


    SDL_Texture *exit_button;
    exit_button = general_load_texture("images\\exit.png", console_renderer);

    int x = SCREEN_X - 240;
    int y = SCREEN_Y - 238;
    SDL_Rect exit_pos, ord_pos, sprite_pos;
    exit_pos.x = x;
    exit_pos.y = y;
    SDL_QueryTexture(exit_button, NULL, NULL, &(exit_pos.w), &(exit_pos.h));
    SDL_QueryTexture(ordinary_avatar, NULL, NULL, &(ord_rect.w), &(ord_rect.h));
    SDL_QueryTexture(sprite_avatar, NULL, NULL, &(sprite_rect.w), &(sprite_rect.h));
    int mouse_x, mouse_y;
    SDL_Color rect_color = {0, 0, 255};
    char *text = (char *) malloc(1000 * sizeof(char));
    text[0] = '\0';
    SDL_SetTextInputRect(&text_rect);
    SDL_Cursor *cursor;
    cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
    SDL_SetCursor(cursor);
    SDL_ShowCursor(SDL_ENABLE);
    //SDL_RenderPresent(console_renderer);
    text_rect.x = SCREEN_X / 2;
    text_rect.y = SCREEN_Y / 2;
    while (!done) {
        //SDL_SetRenderDrawColor(console_renderer,0,0,0,255);
        //SDL_RenderDrawRect(console_renderer,&input_box);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        game_console_welcome(console_renderer, font);
        show_exit_button(console_renderer);
        general_draw_texture(ordinary_avatar, console_renderer, ord_x, ord_y);
        general_draw_texture(sprite_avatar, console_renderer, sprite_x, sprite_y);
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = SDL_TRUE;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) { // checking for user mouse click
                if (mouse_x >= exit_pos.x && mouse_x <= (exit_pos.x + exit_pos.w) && mouse_y >= exit_pos.y &&
                    mouse_y <= (exit_pos.y + exit_pos.h)) {
                    return NULL;
                }
                else if (mouse_x >= sprite_rect.x && mouse_x <= (sprite_rect.x + sprite_rect.w) &&
                         mouse_y >= sprite_rect.y &&
                         mouse_y <= (sprite_rect.y + sprite_rect.h)) {
                    player_type = 1;
                }

                else if (mouse_x >= ord_rect.x && mouse_x <= (ord_rect.x + ord_rect.w) && mouse_y >= ord_rect.y &&
                         mouse_y <= (ord_rect.y + ord_rect.h)) {
                    player_type = 0;
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == 13) {
                break;
            }
            else if (event.type == SDL_TEXTINPUT || event.type == SDL_KEYDOWN) {
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
                    // handling the case in which user enters backspace to remove the last character by clearing and re_rendering
                    text[strlen(text) - 1] = '\0';
                    SDL_RenderClear(console_renderer);
                    surface = TTF_RenderText_Solid(font, text, color);
                    txt_texture = SDL_CreateTextureFromSurface(console_renderer, surface);
                    SDL_QueryTexture(txt_texture, NULL, NULL, &(text_rect.w), &(text_rect.h));
                    SDL_FreeSurface(surface);
                    SDL_RenderCopy(console_renderer, txt_texture, NULL, &text_rect);
                    SDL_RenderPresent(console_renderer);
                }
                else if (event.type == SDL_TEXTINPUT) {
                    strcat(text, event.text.text);
                    surface = TTF_RenderText_Solid(font, text, color);
                    txt_texture = SDL_CreateTextureFromSurface(console_renderer, surface);
                    SDL_QueryTexture(txt_texture, NULL, NULL, &(text_rect.w), &(text_rect.h));
                    SDL_FreeSurface(surface);
                    SDL_RenderCopy(console_renderer, txt_texture, NULL, &text_rect);
                    SDL_RenderPresent(console_renderer);
                }

//                if (event.type == SDL_KEYDOWN && event.key.keysym.sym != SDLK_BACKSPACE) {
//                    strcat(text, event.text.text);
//                }
            }
            SDL_RenderPresent(console_renderer);

            system("cls");
        }
    }
    SDL_FreeCursor(cursor);
    TTF_CloseFont(font);
    SDL_StopTextInput();
    SDL_DestroyTexture(ordinary_avatar);
    SDL_DestroyTexture(sprite_avatar);
    SDL_Quit();
    return text;
}

void game_launcher(int x,int y) {
    // launches a game with the specific name, if file is not found, warning pops up
    SCREEN_X = x;
    SCREEN_Y = y;
    char game_rules[50] = "game-";
    char game_map[50] = "map-";
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *console_window;
    SDL_Renderer *console_renderer;
    console_window = SDL_CreateWindow("Game Console", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X,
                                      SCREEN_Y, SDL_SWSURFACE);
    console_renderer = SDL_CreateRenderer(console_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    char *game_name;
    SDL_RenderClear(console_renderer);
    SDL_RenderPresent(console_renderer);
    game_name = get_info(console_window, console_renderer);
    if (game_name == NULL) {
        SDL_DestroyRenderer(console_renderer);
        SDL_DestroyWindow(console_window);
        SDL_Quit();
        return;
    }
    SDL_RenderPresent(console_renderer);
    strcat(game_rules, game_name);
    strcat(game_map, game_name);
    strcat(game_rules, ".txt");
    strcat(game_map, ".txt");
    struct FileData *rules_data;
    struct FileData *map_data;
    rules_data = read_file(game_rules);
    map_data = read_file(game_map);

    if (map_data == NULL || rules_data == NULL){
        // a window opens and show that the file didn't open
        system("vlc -I dummy --dummy-quiet --fullscreen videos\\file_not_found.mkv vlc://quit\n");
        return;
    }
    //SDL_DestroyRenderer(console_renderer);
    //SDL_DestroyWindow(console_window);
    //game_play(game_rules,game_map);
    int init_game;
    while ((init_game = start_menu(game_name)) != 0) {
        if (init_game == 1) {
            game_settings();
        }
        else if (init_game == 2) {
            SDL_DestroyRenderer(console_renderer);
            SDL_DestroyWindow(console_window);
            SDL_Quit();
            break;
        }
    }
    int result;

    if (init_game == 0) {
        while (1){
            if ((result = game_play(rules_data, map_data)) == 0){
                continue;
            }
            else if (result == -1){
                system("vlc -I dummy --dummy-quiet --fullscreen videos\\syntax_error.mkv vlc://quit\n");
                break;
            }
            else {
                break;
            }

        } // if problem is with files, return sth except 0
    }
}

void game_console_welcome(SDL_Renderer *console_renderer, TTF_Font *font) {
    char welcome[100] = "Welcome to the Game Console";
    SDL_Color color = {38, 59, 239};
    SDL_Rect rect;
    SDL_Surface *welcome_surface;
    SDL_Texture *welcome_texture;
    welcome_surface = TTF_RenderText_Solid(font, welcome, color);
    welcome_texture = SDL_CreateTextureFromSurface(console_renderer, welcome_surface);
    rect.x = SCREEN_X / 3;
    rect.y = 10;
    SDL_QueryTexture(welcome_texture, NULL, NULL, &(rect.w), &(rect.h));
    SDL_RenderCopy(console_renderer, welcome_texture, NULL, &rect);
    SDL_RenderPresent(console_renderer);
}

void show_exit_button(SDL_Renderer *console_renderer) {
    SDL_Texture *exit_button;
    exit_button = general_load_texture("images\\exit.png", console_renderer);
    int x = SCREEN_X - 240;
    int y = SCREEN_Y - 238;
    general_draw_texture(exit_button, console_renderer, x, y);
}