#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "board.h"
#include "score.h"
#include "graphics.h"
#include "game_menu.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <conio.h>
#include <stdbool.h>


int  SCREEN_X;
int SCREEN_Y;

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture **scores;
SDL_Texture *player;
SDL_Texture *opponent;
SDL_Texture **wall_textures = NULL;
SDL_Texture **copy_wall_textures = NULL;
SDL_Texture *details_wall;
SDL_Texture **blocks;
SDL_Texture **bg_textures = NULL;
SDL_Texture **copy_bg_textures = NULL;
SDL_Texture *target;
SDL_Texture *animated_player;
SDL_Texture **player_motions;
SDL_Texture *wall = NULL;
SDL_Texture *bg_tile = NULL;
SDL_Texture *sprite_stand;
SDL_Rect player_sprite;
SDL_Rect player_pos;
TTF_Font *font;
Mix_Chunk **sound_tracks;
int Music_On = 0;
int bg_tile_initialized = 0;
int wall_initialized = 0;
int chosen_wall = 0;
int chosen_bg_tile = 1;
int player_type = 0; // for sprite or ordinary type
extern int game_started;

int player_width, player_height, texture_width, texture_height;
const int FPS = 60;

char *score_shapes = NULL;

void init_graphical_utils(struct Board *board) {
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8192);
    window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y,
                              SDL_SWSURFACE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    font = TTF_OpenFont("ALGER.ttf", SCREEN_Y / 27);
    int index, scores_shapes_count;
    score_shapes = get_score_shapes(board->scores_vector);
    scores_shapes_count = strlen(score_shapes);
    scores = (SDL_Texture **) malloc((scores_shapes_count) * sizeof(SDL_Texture *));
    if (board->scores_vector != NULL) {
        if (scores_shapes_count == 1) {
            scores[0] = load_texture("images\\score1.png");
        }
        if (scores_shapes_count == 2) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
        }
        if (scores_shapes_count == 3) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
        }
        if (scores_shapes_count == 4) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
        }
        if (scores_shapes_count == 5) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
        }
        if (scores_shapes_count == 6) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
            scores[5] = load_texture("images\\score6.png");
        }
        if (scores_shapes_count == 7) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
            scores[5] = load_texture("images\\score6.png");
            scores[6] = load_texture("images\\score7.png");
        }
        if (scores_shapes_count == 8) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
            scores[5] = load_texture("images\\score6.png");
            scores[6] = load_texture("images\\score7.png");
            scores[7] = load_texture("images\\score8.png");
        }
        if (scores_shapes_count == 9) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
            scores[5] = load_texture("images\\score6.png");
            scores[6] = load_texture("images\\score7.png");
            scores[7] = load_texture("images\\score8.png");
            scores[8] = load_texture("images\\score9.png");
        }
        if (scores_shapes_count == 10) {
            scores[0] = load_texture("images\\score1.png");
            scores[1] = load_texture("images\\score2.png");
            scores[2] = load_texture("images\\score3.png");
            scores[3] = load_texture("images\\score4.png");
            scores[4] = load_texture("images\\score5.png");
            scores[5] = load_texture("images\\score6.png");
            scores[6] = load_texture("images\\score7.png");
            scores[7] = load_texture("images\\score8.png");
            scores[8] = load_texture("images\\score9.png");
            scores[9] = load_texture("images\\score10.png");
        }
    }
    player_motions = (SDL_Texture **) malloc(5 * sizeof(SDL_Texture *));
    player_motions[0] = load_texture("images\\up_player.png");
    player_motions[1] = load_texture("images\\right_player.png");
    player_motions[2] = load_texture("images\\down_player.png");
    player_motions[3] = load_texture("images\\left_player.png");
    player_motions[4] = load_texture("images\\stand.png");
    SDL_QueryTexture(player_motions[0], NULL, NULL, &texture_width, &texture_height);
    player_width = texture_width / 4;
    player_height = texture_height;
    player_sprite.x = player_sprite.y = 0;
    player_sprite.w = player_width;
    player_sprite.h = player_height;
    player_pos.y = (board->player->location->x + 1) * SCREEN_X / (board->col + 10);
    player_pos.x = (board->player->location->y + 1) * SCREEN_Y / (board->row + 2);
    player_pos.w = SCREEN_X / (board->col + 10);
    player_pos.h = SCREEN_Y / (board->row + 2);
    player = load_texture("images\\player.png");
    opponent = load_texture("images\\opponent.png");
    target = load_texture("images\\score7.png");
    sprite_stand = load_texture("images\\stand1.png");
    details_wall = load_texture("images\\details_board.png");
    blocks = (SDL_Texture **) malloc(3 * sizeof(SDL_Texture *));
    for (index = 0; board->blocks_vector != NULL && index < board->blocks_vector->length; ++index) {
        if ((board->blocks_vector->blocks)[index]->type == SOLID) {
            blocks[0] = load_texture("images\\solid_block.png");
        }
        else if ((board->blocks_vector->blocks)[index]->type == MOVE) {
            blocks[1] = load_texture("images\\moving_block.png");
        }
        else if ((board->blocks_vector->blocks)[index]->type == DEATH) {
            blocks[2] = load_texture("images\\death_block.png");
        }
    }

    sound_tracks = (Mix_Chunk **) malloc(10 * sizeof(Mix_Chunk *));

    sound_tracks[0] = Mix_LoadWAV("sounds\\battle.wav");
    sound_tracks[1] = Mix_LoadWAV("sounds\\battle2.wav");
    sound_tracks[2] = Mix_LoadWAV("sounds\\track3.wav");
    sound_tracks[3] = Mix_LoadWAV("sounds\\track4.wav");
    sound_tracks[4] = Mix_LoadWAV("sounds\\track5.wav");
    sound_tracks[5] = Mix_LoadWAV("sounds\\track6.wav");
    sound_tracks[6] = Mix_LoadWAV("sounds\\track7.wav");
    sound_tracks[7] = Mix_LoadWAV("sounds\\track8.wav");
    sound_tracks[8] = Mix_LoadWAV("sounds\\track9.wav");
    sound_tracks[9] = Mix_LoadWAV("sounds\\track10.wav");

    bg_textures = (SDL_Texture **) malloc(5 * sizeof(SDL_Texture *));
    wall_textures = (SDL_Texture **) malloc(4 * sizeof(SDL_Texture *));

    bg_textures[0] = load_texture("images\\wooden_tile.png");
    bg_textures[1] = load_texture("images\\black_tile.png");
    bg_textures[2] = load_texture("images\\water_tile.png");
    bg_textures[3] = load_texture("images\\metallic_tile.png");
    bg_textures[4] = load_texture("images\\green_tile.png");

    wall_textures[0] = load_texture("images\\wall.png");
    wall_textures[1] = load_texture("images\\wooden_wall.png");
    wall_textures[2] = load_texture("images\\fire_wall.png");
    wall_textures[3] = load_texture("images\\rock_wall.png");

    if (!wall_initialized) {
        wall = load_texture("images\\wall.png");
    }
    else {
        wall = wall_textures[chosen_wall];
    }
    if (!bg_tile_initialized) {
        bg_tile = load_texture("images\\wooden_tile.png");
    }
    else {
        bg_tile = bg_textures[chosen_bg_tile];
    }


}


SDL_Texture *load_texture(char *path) {
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void g_show_board(struct Board *board) {
    SDL_RenderClear(renderer);
    int i, j, x, y, k, row, col;
    struct Point *loc;
    struct Block *block;
    struct Score *score;
    row = board->row;
    col = board->col;
    for (i = 0; i < row; ++i) {
        for (j = 0; j < col; ++j) {
            x = (j) * SCREEN_X / (col + 7);
            y = (i) * SCREEN_Y / (row);
            draw_texture(bg_tile, x, y, board);
            loc = create_point(i, j);
            if (player_type == 1) {
                player_pos.y = y;
                player_pos.x = x;
                player_pos.w = SCREEN_X / (board->col + 7);
                player_pos.h = SCREEN_Y / (board->row);
            }
            if ((board->map)[i][j] == board->wall) {
                draw_texture(wall, x, y, board);
            }
            else if (board->player != NULL && point_equality(loc, board->player->location)) {
                if (player_type == 1) {
                    player_width = texture_width / 4;
                    player_height = texture_height;
                    if (board->player->state == UP_DIR) {
                        player_sprite.x += player_width;
                        if (player_sprite.x >= texture_width) {
                            player_sprite.x = 0;
                        }
                        SDL_RenderCopy(renderer, player_motions[0], &player_sprite, &player_pos);
                    }
                    else if (board->player->state == RIGHT_DIR) {
                        player_sprite.x += player_width;
                        if (player_sprite.x >= texture_width) {
                            player_sprite.x = 0;
                        }
                        SDL_RenderCopy(renderer, player_motions[1], &player_sprite, &player_pos);
                    }
                    else if (board->player->state == DOWN_DIR) {
                        player_sprite.x += (player_width);
                        if (player_sprite.x >= texture_width) {
                            player_sprite.x = 0;
                        }
                        SDL_RenderCopy(renderer, player_motions[2], &player_sprite, &player_pos);
                    }
                    else if (board->player->state == LEFT_DIR) {
                        player_sprite.x += (player_width);
                        if (player_sprite.x >= texture_width) {
                            player_sprite.x = 0;
                        }
                        SDL_RenderCopy(renderer, player_motions[3], &player_sprite, &player_pos);
                    }
                    else if (board->player->state == STATIC_DIR) {
                        SDL_RenderCopy(renderer, player_motions[4], &player_sprite, &player_pos);
                    }
                }
                else {
                    draw_texture(player, x, y, board);
                }
            }
            else if (check_opponent_existence(board->opponent_vector, loc)) {

                draw_texture(opponent, x, y, board);
            }
            else if ((block = search_block(board->blocks_vector, loc)) != NULL) {
                if (block->type == SOLID) {
                    draw_texture(blocks[0], x, y, board);
                }
                else if (block->type == MOVE) {
                    draw_texture(blocks[1], x, y, board);
                }
                else if (block->type == DEATH) {
                    draw_texture(blocks[2], x, y, board);
                }
            }
            else if ((block = search_block(board->raining_blocks, loc)) != NULL) {
                draw_texture(blocks[2], x, y, board);
            }
            else if ((score = get_score(board->scores_vector, loc)) != NULL) {
                int matching_index;
                matching_index = get_matching_index(score);
                draw_texture(scores[matching_index], x, y, board);
            }
            else if (board->target != NULL && point_equality(loc, board->target->location)) {
                draw_texture(target, x, y, board);
            }
            free(loc);
        }
    }

    show_details_board(board);
    show_game_time(board);
    show_player_score(board);
    show_player_avatar(board);
    show_opponent_avatar(board);
    SDL_RenderPresent(renderer);

}

void draw_texture(SDL_Texture *texture, int x, int y, struct Board *board) {
    struct SDL_Rect dest;
    dest.w = SCREEN_X / (board->col + 7);
    dest.h = SCREEN_Y / (board->row);
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(renderer, texture, NULL, &dest); // here
}

int get_matching_index(struct Score *score) {
    int index;
    for (index = 0; score != NULL && score_shapes[index]; ++index) {
        if (score->shape == score_shapes[index]) {
            return index;
        }
    }
    return -1;
}

void show_game_time(struct Board *board) {
    int row, col;
    row = board->row;
    col = board->col;
    char board_time[100] = "";
    SDL_Color color = {255, 255, 255};
    SDL_Texture *text, *time;
    sprintf(board_time, "%g", board->time);
    text = load_font_texture(font, color, "Remaining Time: ");
    time = load_font_texture(font, color, board_time);
    int text_x, text_y, time_x, time_y;
    text_x = time_x = (col + 1) * SCREEN_X / (col + 7);
    text_y = SCREEN_Y / (row) + 20;
    time_y = 2 * SCREEN_Y / (row);
    draw_font_texture(text, text_x, text_y);
    draw_font_texture(time, time_x, time_y);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(time);
}

void show_player_score(struct Board *board) {
    int row, col;
    row = board->row;
    col = board->col;
    char player_score[100] = "";
    char text_show[100] = "Player Score: ";
    sprintf(player_score, "%d", board->player->score);
    SDL_Color color = {255, 255, 255};
    SDL_Texture *text, *score;
    text = load_font_texture(font, color, text_show);
    score = load_font_texture(font, color, player_score);
    int text_x, text_y, score_x, score_y;
    text_x = score_x = (col + 1) * SCREEN_X / (col + 7);
    text_y = 3 * SCREEN_Y / (row + 2);
    score_y = 4 * SCREEN_Y / (row + 2);
    draw_font_texture(text, text_x, text_y);
    draw_font_texture(score, score_x, score_y);
    SDL_DestroyTexture(text);
    SDL_DestroyTexture(score);
}

void show_player_avatar(struct Board *board) { // same for opponent
    int row, col;
    row = board->row;
    col = board->col;
    SDL_Texture *texture;
    SDL_Rect text_rect;
    SDL_Color color = {255, 255, 255};
    texture = load_font_texture(font, color, "Player Avatar:");
    int text_x, text_y, avatar_x, avatar_y;
    text_x = avatar_x = (col + 1) * SCREEN_X / (col + 7);
    text_y = 5 * SCREEN_Y / (row + 2);
    avatar_y = text_y + 50;
    draw_font_texture(texture, text_x, text_y);
    if (player_type == 0){
        draw_texture(player, avatar_x, avatar_y, board);
    }
    else {
        draw_texture(sprite_stand, avatar_x, avatar_y, board);
    }

    SDL_DestroyTexture(texture);
}

void show_opponent_avatar(struct Board *board) {
    if (board -> opponent_vector == NULL){
        return;
    }
    int row, col;
    row = board->row;
    col = board->col;
    SDL_Texture *texture;
    SDL_Rect text_rect;
    SDL_Color color = {255, 255, 255};
    texture = load_font_texture(font, color, "Opponent Avatar:");
    int text_x, text_y, avatar_x, avatar_y;
    text_x = avatar_x = (col + 1) * SCREEN_X / (col + 7);
    text_y = 7 * SCREEN_Y / (row + 2);
    avatar_y = text_y + 50;
    draw_font_texture(texture, text_x, text_y);
    draw_texture(opponent, avatar_x, avatar_y, board);
    SDL_DestroyTexture(texture);
}


void show_details_board(struct Board *board) {
    int row, col;
    row = board->row;
    col = board->col;
    int i, j, k;
    for (k = col + 2; k < SCREEN_X / col; ++k) {
        draw_texture(details_wall, k * SCREEN_X / (col + 10), 0, board);
    }
    for (i = 0; i < row; ++i) {
        for (j = col + 2; j < SCREEN_Y / col; ++j) {
            if (j == col + 2) {
                draw_texture(details_wall, (col + 2) * SCREEN_X / (col + 10), (i + 1) * SCREEN_Y / (row + 2), board);
            }
            if (j == col + 9) {
                draw_texture(details_wall, j * SCREEN_X / (col + 10), (i + 1) * SCREEN_Y / (row + 2), board);
            }
        }
    }
    for (k = col + 2; k < col + 10; ++k) {
        draw_texture(details_wall, k * SCREEN_X / (col + 10), (i + 1) * SCREEN_Y / (row + 2), board);
    }
}

SDL_Texture *load_font_texture(TTF_Font *font, SDL_Color color, char *label) {
    SDL_Surface *surface;
    SDL_Texture *text;
    surface = TTF_RenderText_Solid(font, label, color);
    text = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return text;
}

void draw_font_texture(SDL_Texture *font_texture, int x, int y) {
    struct SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(font_texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(renderer, font_texture, NULL, &dest); // here
}

void general_draw_texture(SDL_Texture *texture, SDL_Renderer *target_renderer, int x, int y) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));
    SDL_RenderCopy(target_renderer, texture, NULL, &rect);
    SDL_RenderPresent(target_renderer);

}

int game_settings(void) { // close font
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 8192);
    Mix_Chunk *select_track = Mix_LoadWAV("sounds\\misc_menu_3.wav");
    SDL_Window *settings_window;
    settings_window = SDL_CreateWindow("Settings", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y,
                                       SDL_SWSURFACE);
    SDL_Renderer *settings_renderer;
    SDL_Surface *surface;
    surface = SDL_GetWindowSurface(settings_window);
    settings_renderer = SDL_CreateRenderer(settings_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC |
                                                                SDL_RENDERER_TARGETTEXTURE); // check!!!!
    SDL_RenderClear(settings_renderer);
    const char *labels[NUMSETTINGS] = {"Music (On/OFF)", "Choose Background Tile", "Choose Wall Shape", "Back to Menu"};
    SDL_Surface *choices[NUMSETTINGS];
    SDL_Color color[3] = {{255, 255, 255},
                          {255, 0,   0},
                          {220, 220, 220}};
    Uint32 time;
    TTF_SetFontStyle(font, TTF_STYLE_ITALIC);
    int i, x, y;
    for (i = 0; i < NUMSETTINGS; ++i) {
        choices[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
    }

    SDL_Texture *mute;
    SDL_Texture *unmute;
    bool selected[NUMSETTINGS] = {0, 0, 0, 0};
    bool wall_selected[4] = {0};
    bool tile_selected[5] = {0};
    SDL_Texture *settings_texture[NUMSETTINGS];
    SDL_Rect pos[NUMSETTINGS]; // for texts
    SDL_Rect tiles_pos[5]; // for showing tiles
    SDL_Rect walls_pos[4];
    SDL_Rect sound_pos;
    // index 1 for bg tile, index 2 for walls
//    pos[0].x = surface->clip_rect.w / 2 - choices[0]->clip_rect.w / 2;
//    pos[0].y = surface->clip_rect.h / 2 - choices[0]->clip_rect.h;
//    pos[1].x = surface->clip_rect.w / 2 - choices[1]->clip_rect.w / 2;
//    pos[1].y = surface->clip_rect.h / 2 + choices[1]->clip_rect.h;
//    pos[2].x = surface->clip_rect.w / 2 - choices[2]->clip_rect.w / 2;
//    pos[2].y = (int) (surface->clip_rect.h / 1.7) + choices[2]->clip_rect.h;
//    pos[3].x = surface->clip_rect.w / 2 - choices[3]->clip_rect.w / 2;
//    pos[3].y = (int) (surface->clip_rect.h / 1.5) + choices[3]->clip_rect.h;

    pos[0].x = surface->clip_rect.w / 2 - choices[0]->clip_rect.w / 2;
    pos[0].y = surface->clip_rect.h / 4;
    pos[1].x = surface->clip_rect.w / 2 - choices[1]->clip_rect.w / 2;
    pos[1].y = pos[0].y + surface->clip_rect.h / 8;
    pos[2].x = surface->clip_rect.w / 2 - choices[2]->clip_rect.w / 2;
    pos[2].y = pos[1].y + surface->clip_rect.h / 8;
    pos[3].x = surface->clip_rect.w / 2 - choices[3]->clip_rect.w / 2;
    pos[3].y = pos[2].y + surface->clip_rect.h / 8;


    copy_bg_textures = (SDL_Texture **) malloc(5 * sizeof(SDL_Texture *));
    copy_wall_textures = (SDL_Texture **) malloc(4 * sizeof(SDL_Texture *));

    copy_bg_textures[0] = general_load_texture("images\\wooden_tile.png", settings_renderer);
    copy_bg_textures[1] = general_load_texture("images\\black_tile.png", settings_renderer);
    copy_bg_textures[2] = general_load_texture("images\\water_tile.png", settings_renderer);
    copy_bg_textures[3] = general_load_texture("images\\metallic_tile.png", settings_renderer);
    copy_bg_textures[4] = general_load_texture("images\\green_tile.png", settings_renderer);

    copy_wall_textures[0] = general_load_texture("images\\wall.png", settings_renderer);
    copy_wall_textures[1] = general_load_texture("images\\wooden_wall.png", settings_renderer);
    copy_wall_textures[2] = general_load_texture("images\\fire_wall.png", settings_renderer);
    copy_wall_textures[3] = general_load_texture("images\\rock_wall.png", settings_renderer);

    mute = general_load_texture("images\\mute.png", settings_renderer);
    unmute = general_load_texture("images\\unmute.png", settings_renderer);

    for (i = 0; i < NUMSETTINGS; ++i) {
        settings_texture[i] = SDL_CreateTextureFromSurface(settings_renderer, choices[i]);
        TTF_SizeText(font, labels[i], &(pos[i].w), &(pos[i].h));
        SDL_RenderCopy(settings_renderer, settings_texture[i], NULL, &pos[i]);
    }
    //SDL_RenderClear(settings_renderer);

//        SDL_QueryTexture(test,NULL,NULL,&(tiles_pos[0].w),&(tiles_pos[0].h));
//        printf("\nW %d    H %d",tiles_pos[0].w,tiles_pos[0].h);
//        SDL_RenderCopy(settings_renderer,test,NULL,NULL);
//        SDL_RenderPresent(settings_renderer);

//    for (i = 0; i < 5; ++i) {
//        tiles_pos[i].x = pos[1].x + 30 * (i + 6);
//        tiles_pos[i].y = pos[1].y + 60;
//        //SDL_QueryTexture(bg_textures[i],NULL,NULL,&(tiles_pos[i].w),&(tiles_pos[i].h));
//        tiles_pos[i].w = 30;
//        tiles_pos[i].h = 30;
//        SDL_RenderCopy(settings_renderer, copy_bg_textures[i], NULL, &(tiles_pos[i]));
//    }
    for (i = 0; i < 5; ++i) {
        tiles_pos[i].x = SCREEN_X / 2 + 30 * (i - 2);
        tiles_pos[i].y = pos[1].y + surface->clip_rect.h / 16;
        //SDL_QueryTexture(bg_textures[i],NULL,NULL,&(tiles_pos[i].w),&(tiles_pos[i].h));
        tiles_pos[i].w = 30;
        tiles_pos[i].h = 30;
        SDL_RenderCopy(settings_renderer, copy_bg_textures[i], NULL, &(tiles_pos[i]));
    }
//    for (i = 0; i < 4; ++i) {
//        walls_pos[i].x = pos[2].x + 30 * (i + 5);
//        walls_pos[i].y = pos[2].y + 50;
//        walls_pos[i].w = 30;
//        walls_pos[i].h = 30;
//        //SDL_QueryTexture(wall_textures[i],NULL,NULL,&(walls_pos[i].w),&(walls_pos[i].h));
//        SDL_RenderCopy(settings_renderer, copy_wall_textures[i], NULL, &walls_pos[i]);
//    }
    for (i = 0; i < 4; ++i) {
        walls_pos[i].x = SCREEN_X / 2 + 30 * (i - 2);
        walls_pos[i].y = pos[2].y + surface->clip_rect.h / 16;
        walls_pos[i].w = 30;
        walls_pos[i].h = 30;
        //SDL_QueryTexture(wall_textures[i],NULL,NULL,&(walls_pos[i].w),&(walls_pos[i].h));
        SDL_RenderCopy(settings_renderer, copy_wall_textures[i], NULL, &walls_pos[i]);
    }

    sound_pos.x = pos[0].x + pos[0].w + 10;
    sound_pos.y = pos[0].y;
    SDL_QueryTexture(mute, NULL, NULL, &(sound_pos.w), &(sound_pos.h));

    if (Music_On) {
        SDL_RenderCopy(settings_renderer, unmute, NULL, &sound_pos);
    }
    else {
        SDL_RenderCopy(settings_renderer, mute, NULL, &sound_pos);
    }
    SDL_RenderPresent(renderer);
    SDL_FillRect(surface, &surface->clip_rect, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
    SDL_Event event;
    while (1) {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case (SDL_QUIT | SDLK_ESCAPE):
                    SDL_FreeSurface(choices[0]);
                    SDL_FreeSurface(choices[1]);
                    SDL_FreeSurface(choices[2]);
                    SDL_FreeSurface(choices[3]);
                    SDL_DestroyRenderer(settings_renderer);
                    for (i = 0; i < NUMSETTINGS; ++i) {
                        SDL_DestroyTexture(settings_texture[i]);
                    }
                    SDL_DestroyWindow(settings_window);
                    return 0;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (i = 0; i < NUMSETTINGS; ++i) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            if (!selected[i]) {
                                if (Music_On) {
                                    Mix_PlayChannel(-1, select_track, 0);
                                    SDL_RenderCopy(settings_renderer, unmute, NULL, &sound_pos);
                                }
                                else {
                                    SDL_RenderCopy(settings_renderer, mute, NULL, &sound_pos);
                                }
                                selected[i] = 1;
                                SDL_FreeSurface(choices[i]);
                                choices[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                                settings_texture[i] = SDL_CreateTextureFromSurface(settings_renderer, choices[i]);
                                SDL_RenderCopy(settings_renderer, settings_texture[i], NULL, pos + i);
                                SDL_RenderPresent(settings_renderer);
                            }
                            //Mix_FreeChunk(select_track);
                        }
                        else if (selected[i]) {
                            selected[i] = 0;
                            SDL_FreeSurface(choices[i]);
                            choices[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                            settings_texture[i] = SDL_CreateTextureFromSurface(settings_renderer, choices[i]);
                            SDL_RenderCopy(settings_renderer, settings_texture[i], NULL, pos + i);
                            SDL_RenderPresent(settings_renderer);
                        }
                        else if (x >= walls_pos[i].x && x <= walls_pos[i].x + walls_pos[i].w && y >= walls_pos[i].y &&
                                 y <= walls_pos[i].y + walls_pos[i].h) {
                            if (!wall_selected[i]) {
                                if (Music_On) {
                                    Mix_PlayChannel(-1, select_track, 0);
                                    SDL_RenderCopy(settings_renderer, unmute, NULL, &sound_pos);
                                }
                                else {
                                    SDL_RenderCopy(settings_renderer, mute, NULL, &sound_pos);
                                }

                                wall_selected[i] = 1;
                                SDL_RenderCopy(settings_renderer, copy_wall_textures[i], NULL, &(walls_pos[i]));
                            }
                        }
                        else if (x >= tiles_pos[i].x && x <= tiles_pos[i].x + tiles_pos[i].w && y >= tiles_pos[i].y &&
                                 y <= tiles_pos[i].y + tiles_pos[i].h) {
                            if (!tile_selected[i]) {
                                if (Music_On) {
                                    Mix_PlayChannel(-1, select_track, 0);
                                    SDL_RenderCopy(settings_renderer, unmute, NULL, &sound_pos);
                                }
                                else {
                                    SDL_RenderCopy(settings_renderer, mute, NULL, &sound_pos);
                                }

                                tile_selected[i] = 1;
                                SDL_RenderCopy(settings_renderer, copy_bg_textures[i], NULL, &(tiles_pos[i]));
                            }
                        }
                        else {
                            if (selected[i]) {
                                selected[i] = 0;
                                SDL_FreeSurface(choices[i]);
                                choices[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                                settings_texture[i] = SDL_CreateTextureFromSurface(settings_renderer, choices[i]);
                                SDL_RenderCopy(settings_renderer, settings_texture[i], NULL, pos + i);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    if ((x >= pos[0].x && x <= pos[0].x + pos[0].w && y >= pos[0].y && y <= pos[0].y + pos[0].h) ||
                        (x >= sound_pos.x && x <= sound_pos.x + sound_pos.w && y >= sound_pos.y &&
                         y <= sound_pos.y + sound_pos.h)) {
                        Music_On = !Music_On;
                        if (Music_On) {
                            SDL_RenderCopy(settings_renderer, unmute, NULL, &sound_pos);
                        }
                        else {
                            SDL_RenderCopy(settings_renderer, mute, NULL, &sound_pos);
                        }
                    }
                    if (x >= pos[3].x && x <= pos[3].x + pos[3].w && y >= pos[3].y && y <= pos[3].y + pos[3].h) {
                        SDL_FreeSurface(choices[0]);
                        SDL_FreeSurface(choices[1]);
                        SDL_FreeSurface(choices[2]);
                        SDL_FreeSurface(choices[3]);
                        SDL_FreeSurface(surface);
                        SDL_DestroyRenderer(settings_renderer);
                        for (i = 0; i < NUMSETTINGS; ++i) {
                            SDL_DestroyTexture(settings_texture[i]);
                        }
                        SDL_DestroyWindow(settings_window);
                        return 0;
                    }
                    for (i = 0; i < 4; ++i) {
                        if (x >= walls_pos[i].x && x <= walls_pos[i].x + walls_pos[i].w && y >= walls_pos[i].y &&
                            y <= walls_pos[i].y + walls_pos[i].h) {
                            if (game_started) {
                                wall = wall_textures[i];
                            }
                            wall_initialized = 1;
                            chosen_wall = i;
                        }
                    }
                    for (i = 0; i < 5; ++i) {
                        if (x >= tiles_pos[i].x && x <= tiles_pos[i].x + tiles_pos[i].w && y >= tiles_pos[i].y &&
                            y <= tiles_pos[i].y + tiles_pos[i].h) {
                            if (game_started) {
                                bg_tile = bg_textures[i];
                            }
                            bg_tile_initialized = 1;
                            chosen_bg_tile = i;
                        }
                    }
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        SDL_FreeSurface(choices[0]);
                        SDL_FreeSurface(choices[1]);
                        SDL_FreeSurface(choices[2]);
                        SDL_FreeSurface(choices[3]);
                        SDL_DestroyRenderer(settings_renderer);
                        for (i = 0; i < NUMSETTINGS; ++i) {
                            SDL_DestroyTexture(settings_texture[i]);
                        }
                        SDL_DestroyWindow(settings_window);
                        return 0;
                    }
            }
        }
        for (i = 0; i < NUMSETTINGS; ++i) {
            SDL_BlitSurface(choices[i], NULL, surface, &pos[i]);
        }
        SDL_RenderPresent(settings_renderer);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
}

SDL_Texture *general_load_texture(char *path, SDL_Renderer *new_renderer) {
    //The final texture
    SDL_Texture *newTexture = NULL;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
    }
    newTexture = SDL_CreateTextureFromSurface(new_renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

void music_handler(int select_key) {
    if (Music_On){
        switch (select_key) {
            case SDLK_1:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(0, sound_tracks[0], 0);
                break;
            case SDLK_2:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(1, sound_tracks[1], 0);
                break;
            case SDLK_3:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(2, sound_tracks[2], 0);
                break;
            case SDLK_4:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(3, sound_tracks[3], 0);
                break;
            case SDLK_5:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(4, sound_tracks[4], 0);
                break;
            case SDLK_6:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(5, sound_tracks[5], 0);
                break;
            case SDLK_7:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(6, sound_tracks[6], 0);
                break;
            case SDLK_8:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(7, sound_tracks[7], 0);
                break;
            case SDLK_9:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(8, sound_tracks[8], 0);
                break;
            case SDLK_0:
                Mix_HaltChannel(-1);
                Mix_PlayChannel(9, sound_tracks[9], 0);
                break;
            default:
                break;
        }
    }

}