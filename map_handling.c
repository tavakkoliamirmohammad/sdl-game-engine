#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map_handling.h"
#include "utils.h"
#include "token2.h"
#include "board.h"
#include "player.h"
#include "blocks.h"
#include "target.h"
#include "object.h"
#include "artificial_opp.h"


char **map_init(int row, int col) {
    char **map = (char **) malloc(sizeof(char *) * row);
    int i;
    for (i = 0; i < row; ++i) {
        map[i] = (char *) malloc(sizeof(char) * (col + 2));
    }
    return map;
}

struct Board *create_board(struct LinkedList *rules, struct FileData *map_file) {
    int row, col, rules_len;
    rules_len = len(rules);
    char *first_line;
    first_line = read_line(map_file);
    col = atoi(strtok(first_line, "x"));
    row = atoi(strtok(NULL, "x"));
    //printf("original map:\n%s\n", map_file->file_content);
    struct Board *board;
    board = init_board();
    board->row = row;
    board->col = col;
    board->map = (char **) malloc(row * sizeof(char *));
    int i, j, counter;
    for (i = 0; i < row; ++i) {
        (board->map)[i] = (char *) malloc(sizeof(char) * (col + 1));
        for (j = 0; j < col; ++j) {
            (board->map)[i][j] = (map_file->file_content)[map_file->file_position];
            symbol_analyzer((map_file->file_content)[map_file->file_position], rules, board, i, j);
            ++(map_file->file_position);
        }
        (board->map)[i][j] = '\0';
        ++(map_file->file_position);
    }
    // getting time from text file
    for (i = 0; i < rules_len; ++i) {
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, i);
        if (item->type == TIME) {
            int time = atoi((char *) get_data(item->info, 0));
            board->time = (double) time;
        }
        else if (item->type == RPOINT) {
            int score_value = atoi((char *) get_data(item->info, 1));
            int score_count = atoi((char *) get_data(item->info, 2));
            char symbol;
            char *token_symbol;
            token_symbol = (char *) get_data(item->info, 0);
            symbol = ((char *) get_data(item->info, 0))[0];
            for (counter = 0; counter < score_count; ++counter) {
                struct Score *score;
                struct Point *loc;
                loc = rand_generator(board);
                score = create_score(loc, symbol, score_value, score_count);
                board->scores_vector = push_score(board->scores_vector, score);
                (board->map)[loc->x][loc->y] = symbol;
                free(score);
                free(loc);
            }
            board->score_shapes = add_last_LL(board->score_shapes, token_symbol, sizeof(char) * 2);
        }
        else if (item->type == RAINDB) {
            board->raining_block_count = raindb_count(rules);
        }
    }

    return board;
}

void symbol_analyzer(char symbol, struct LinkedList *rules, struct Board *board, int x, int y) {
    int token_len, i, rules_len, player_ammo;
    rules_len = len(rules);
    char *symbol_string = (char *) malloc(2 * sizeof(char));
    symbol_string[0] = symbol;
    symbol_string[1] = '\0';
    player_ammo = 0;
    for (i = 0; i < rules_len; ++i) {
        char *token_symbol;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, i);
        token_symbol = (char *) ((item->info)->data);
        // ******************add shape******************
        if (strcmp(token_symbol, symbol_string) == 0) {
            if (item->type == SOLIDBLOCK || item->type == DEATHBLOCK || item->type == MOVEBLOCK) {
                struct Block *block = (struct Block *) malloc(sizeof(struct Block));
                block->shape = symbol;
                block->location = create_point(x, y);
                board->block_shapes = add_last_LL(board->block_shapes, token_symbol,
                                                  sizeof(char) * strlen(token_symbol) + 1);

                // add block shape
                if (item->type == SOLIDBLOCK) {
                    block->type = SOLID;
                }
                else if (item->type == DEATHBLOCK) {
                    block->type = DEATH;
                }
                else {
                    block->type = MOVE;
                }
                board->blocks_vector = push_block(board->blocks_vector, block);
                free(block);
                break;
            }
            else if (item->type == WALL) {
                board->wall = symbol;
                break;
            }
            else if (item->type == CHARACTER) {
                char *user_controls;
                struct Player *player;
                user_controls = get_controls(rules);
                player_ammo = get_player_ammo(rules);
                player = create_player(create_point(x, y), symbol, user_controls, 0, player_ammo, NULL, STATIC_DIR,
                                       USER);
                board->player = player;
                board->player_shapes = add_last_LL(board->player_shapes, token_symbol,
                                                   sizeof(char) * (strlen(token_symbol) + 1));
                break;
            }
            else if (item->type == OPP) {
                struct Opponent *opponent;
                opponent = create_opponent(create_point(x, y), symbol, 0);
                board->opponent_vector = push_opponent(board->opponent_vector, opponent);
                board->opponent_shapes = add_last_LL(board->opponent_shapes, token_symbol,
                                                     sizeof(char) * (strlen(token_symbol) + 1));
                free(opponent);
                break;
            }
            else if (item->type == TARGET) {
                struct Target *target;
                target = create_target(create_point(x, y), symbol);
                board->target = copy_target(target);
                free(target);
            }

            else if (item->type == OBJECT) {
                struct Object *object;
                object = create_object(create_point(x, y), symbol);
                board->object = copy_object(object);
                free(object);
            }
        }
    }
}

char *get_controls(struct LinkedList *rules) {
    char *user_controls = (char *) malloc(sizeof(char) * 5);
    int index, rules_len;
    rules_len = len(rules);
    for (index = 0; index < rules_len; ++index) {
        char *token;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, index);
        if (item->type == UP) {
            user_controls[0] = ((char *) get_data(item->info, 0))[0];
        }
        else if (item->type == RIGHT) {
            user_controls[1] = ((char *) get_data(item->info, 0))[0];
        }
        else if (item->type == DOWN) {
            user_controls[2] = ((char *) get_data(item->info, 0))[0];
        }
        else if (item->type == LEFT) {
            user_controls[3] = ((char *) get_data(item->info, 0))[0];
        }
    }
    user_controls[4] = '\0';
    return user_controls;
}

struct Board *init_board(void) {
    struct Board *board = (struct Board *) malloc(sizeof(struct Board));
    board->blocks_vector = NULL;
    board->raining_blocks = NULL;
    board->scores_vector = NULL;
    board->player = NULL;
    board->opponent_vector = NULL;
    board->block_shapes = NULL;
    board->score_shapes = NULL;
    board->player_shapes = NULL;
    board->opponent_shapes = NULL;
    board->target = NULL;
    board->object = NULL;
    board->row = board->col = 0;
    board->raining_block_count = 0;
    board->time = 0.0;
    return board;
}

int get_player_ammo(struct LinkedList *rules) {
    int index, rules_len, player_ammo;
    rules_len = len(rules);
    player_ammo = 0;
    for (index = 0; index < rules_len; ++index) {
        char *token;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, index);
        if (item->type == PUT) {
            player_ammo = atoi((char *) get_data(item->info, 2));
        }
    }
    return player_ammo;
}

char get_deathblock_shape(struct LinkedList *rules) {
    int index, rules_len;
    char shape;
    shape = '\0';
    rules_len = len(rules);
    for (index = 0; index < rules_len; ++index) {
        char *token;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, index);
        if (item->type == PUT) {
            shape = ((char *) get_data(item->info, 2))[0];
        }
    }
    return shape;

}

char get_puts_key(struct LinkedList *rules) {
    int index, rules_len;
    char key;
    key = '\0';
    rules_len = len(rules);
    for (index = 0; index < rules_len; ++index) {
        char *token;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, index);
        if (item->type == PUT) {
            key = ((char *) get_data(item->info, 0))[0];
        }
    }
    return key;

}

int raindb_count(struct LinkedList *rules) {
    int index, rules_len, raindb_count;
    raindb_count = 0;
    rules_len = len(rules);
    for (index = 0; index < rules_len; ++index) {
        char *token;
        struct TokenVector *item;
        item = (struct TokenVector *) get_data(rules, index);
        if (item->type == RAINDB) {
            raindb_count = atoi((char *) get_data(item->info, 0));
        }
    }
    return raindb_count;
}

void show_board(struct Board *board) {
    hidecursor();
    set_position(0, 0);
//    system("cls");
    int row_index, col_index;
    for (row_index = 0; row_index < board->row; ++row_index) {
        for (col_index = 0; col_index < board->col; ++col_index) {
            printf("%c", (board->map)[row_index][col_index]);
        }
        printf("\n");
    }
}


