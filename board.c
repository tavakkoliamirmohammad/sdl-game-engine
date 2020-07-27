#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "board.h"
#include "player.h"
#include "utils.h"
#include "linked_list.h"
#include "map_handling.h"
#include "object.h"
#include <windows.h>


char empty_cell = '\0';
int game_over = 0;

void delay(unsigned int ms) {
    unsigned int ret_time = clock() + ms;   // Get finishing time.
    while (clock() <= ret_time);               // Loop until end.
}

void set_position(int X, int Y) { // setting the cursor into an arbitrary position
    HANDLE Screen;
    Screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position = {X, Y};
    SetConsoleCursorPosition(Screen, Position);
}

void hidecursor(void) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

int is_blocked(struct Board *board, struct Point *loc) {
    // returns whether there exists a block in the given location
    int index;
    if (board->blocks_vector != NULL) {
        for (index = 0; index < board->blocks_vector->length; ++index) {
            if (point_equality((board->blocks_vector->blocks)[index]->location, loc)) {
                return 1;
            }
        }
    }
    if (board->raining_blocks != NULL) {
        for (index = 0; index < board->raining_blocks->length; ++index) {
            if (point_equality((board->raining_blocks->blocks)[index]->location, loc)) {
                return 1;
            }
        }
    }
    return 0;
}

int is_ord_blocked(struct Board *board, struct Point *loc) {
    // returns whether there exists a block in the given location
    int index;
    if (board->blocks_vector != NULL) {
        for (index = 0; index < board->blocks_vector->length; ++index) {
            if (point_equality((board->blocks_vector->blocks)[index]->location, loc)) {
                return 1;
            }
        }
    }
    return 0;
}

int is_rain_block(struct Board* board, struct Point* loc){
    int index;
    if (board->raining_blocks != NULL) {
        for (index = 0; index < board->raining_blocks->length; ++index) {
            if (point_equality((board->raining_blocks->blocks)[index]->location, loc)) {
                return 1;
            }
        }
    }
    return 0;
}

int access_allowed(struct Board *board, struct Point *loc) {
    int index;
    for (index = 0; board->opponent_vector != NULL && index < board->opponent_vector->length; ++index) {
        if (point_equality((board->opponent_vector->opponents)[index]->location, loc)) {
            return 0;
        }
    }

    char *cell;
    cell = get_board_cell(board, loc);
    if (cell != NULL) {
        return !(is_blocked(board, loc) || *cell == board->wall);
    }
    return 0;
}

struct Score *is_score(struct Board *board, struct Point *loc) {
    // returns whether there exists a score in the given location
    int index;
    struct Score *target_score;
    if (board->scores_vector != NULL) {
        for (index = 0; index < board->scores_vector->length; ++index) {
            if (point_equality((board->scores_vector->scores)[index]->location, loc)) {
                target_score = (board->scores_vector->scores)[index];
                return target_score;
            }
        }
    }
    return NULL;
}

void add_score(struct Board *board, struct Player *player) {
    struct Score *score;
    int value, count;
    char shape;
    if ((score = is_score(board, player->location))) {
        value = score->value;
        count = score->count;
        shape = score->shape;
        player->score += score->value;
        remove_score(board, score);
        score_fill(board, shape, value, count);
    }
}


struct Point *rand_generator(struct Board *board) {
    // generating random numbers and checking if the board is empty in the generated index number.
    int len, rand_num, i, x, y;
    static int rand_initializer;
    rand_initializer = 0;
    len = board->row * board->col;
    i = 1;
    if (!rand_initializer) {
        srand(time(NULL) * i * i * i * 170); // generating a random seed
        rand_initializer = 1;
    }
    rand_num = rand() % len;
    x = rand_num / board->col;
    y = rand_num % board->row;
    struct Point *new_point;
    new_point = create_point(x, y);
    while (!inside_board(board, new_point) || !is_cell_empty(board, new_point)) {
        free(new_point);
        ++i;
        rand_num = rand() % len;
        x = rand_num / board->col;
        y = rand_num % board->col;
        new_point = create_point(x, y);
    }
    return new_point;
}

int is_cell_empty(struct Board *board, struct Point *loc) {
    // first check if the player exists in the given location
    int index;
    if (player_exists(board->player, loc)) {
        return 0;
    }
    for (index = 0; board->opponent_vector != NULL && index < board->opponent_vector->length; ++index) {
        if (opponent_exists((board->opponent_vector->opponents)[index], loc)) {
            return 0;
        }
    }
    // now check for the blocks, scores and wall
    char *cell;
    cell = get_board_cell(board, loc);
    if (cell != NULL) {
        return !(is_blocked(board, loc) || is_score(board, loc) || *cell == board->wall);
    }
    return 0;
}


char *get_board_cell(struct Board *board, struct Point *loc) {
    if (inside_board(board, loc)) {
        return &((board->map)[loc->x][loc->y]);
    }
    return NULL;
}

struct Point *moving_allowed(struct Board *board, struct Point *loc, enum directions dir) {
    int x, y, res; // x for the row index y for column index res for final result
    struct Point *new_point; // for new location
    if (dir == UP_DIR) {
        x = loc->x - 1;
        y = loc->y;
    }
    else if (dir == RIGHT_DIR) {
        x = loc->x;
        y = loc->y + 1;
    }
    else if (dir == DOWN_DIR) {
        x = loc->x + 1;
        y = loc->y;
    }
    else if (dir == LEFT_DIR) {
        x = loc->x;
        y = loc->y - 1;
    }
    else if (dir == STATIC_DIR) {
        x = loc->x;
        y = loc->y;
        return loc;
    }
    else {
        // in case of wrong direction
        return NULL;
    }
    new_point = create_point(x, y);
    if (new_point != NULL && access_allowed(board, new_point)) {
        return new_point;
    }
    return NULL;
}


struct Point *move(struct Board *board, struct Player *player, enum directions dir) {
    /* this function handles the moving of players,by checking if moving through a specific direction is possible,
     * and then changes the position of the moving player in the board, and at the end returns the updated location
     * of the player in the board. */
    struct Point *next_loc;
    next_loc = moving_allowed(board, player->location, dir);
    check_for_deathblock(board, player);
    move_block(board);
    if (next_loc != NULL) {
        set_board_cell(board, player->location, empty_cell);
        player->location = next_loc;
        set_board_cell(board, player->location, player->symbol);
        add_score(board, player);
    }
//    check_for_deathblock(board, player);
    return player->location;
}

void set_board_cell(struct Board *board, struct Point *loc, char symbol) {
    if (inside_board(board, loc)) {
        (board->map)[loc->x][loc->y] = symbol;
    }
}

void move_block(struct Board *board) {
    struct Point *loc;
    struct Block *moving_block;
    if (board->player->state == UP_DIR) {
        loc = create_point(board->player->location->x - 1, board->player->location->y);
    }
    else if (board->player->state == RIGHT_DIR) {
        loc = create_point(board->player->location->x, board->player->location->y + 1);
    }
    else if (board->player->state == DOWN_DIR) {
        loc = create_point(board->player->location->x + 1, board->player->location->y);
    }
    else if (board->player->state == LEFT_DIR) {
        loc = create_point(board->player->location->x, board->player->location->y - 1);
    }
    else {
        return;
    }
    moving_block = get_moving_block(board, loc);
    if (moving_block != NULL) {
        struct Point *new_loc;
        new_loc = moving_block_access_allowed(board, loc, board->player->state);
        if (new_loc != NULL) {
            moving_block->location = new_loc;
            set_board_cell(board, new_loc, moving_block->shape);
            set_board_cell(board, board->player->location, empty_cell);
            board->player->location = loc;
            set_board_cell(board, loc, board->player->symbol);
        }
    }
}


struct Point *rand_death_loc(struct Board *board) {
    int i, y;
    i = 1;
    srand(time(NULL) * i * i * i * 170); // generating a random seed
    y = rand() % board->row;
    struct Point *new_point;
    new_point = create_point(1, y);
    while (!inside_board(board, new_point) || !is_cell_empty(board, new_point)) {
        free(new_point);
        ++i;
        srand(time(NULL) * i * i * i * 170);
        y = rand() % board->row;
        new_point = create_point(1, y);
    }
    return new_point;
}

void init_board_raindb(struct Board *board, char shape) {
    //board -> raining_blocks = (struct BlockVector *)malloc(sizeof(struct BlockVector));
    //board -> raining_blocks -> blocks = (struct Block **)malloc(board->raining_block_count * sizeof(struct Block *));
    if (shape == '\0') {
        return;
    }
    struct Block *block;
    struct Point *loc;
    int index;
    for (index = 0; index < board->raining_block_count; ++index) {
        loc = rand_death_loc(board);
        block = create_block(shape, loc, DEATH);
        board->raining_blocks = push_block(board->raining_blocks, block);
    }
}

void rain_death_block(struct Board *board, char shape) {
    if (shape == '\0') {
        return;
    }
    init_board_raindb(board, shape);
    int index;
    struct Point *next_loc;
    struct Block *block;
    for (index = 0; board->raining_blocks != NULL && index < board->raining_blocks->length; ++index) {
        block = (board->raining_blocks->blocks)[index];
        next_loc = moving_block_access_allowed(board, block->location, DOWN_DIR);
        if (next_loc != NULL) {
            set_board_cell(board, block->location, empty_cell);
            block->location = next_loc;
            set_board_cell(board, next_loc, shape);
        }
        else {
            set_board_cell(board, block->location, empty_cell);
            remove_block(board->raining_blocks, (board->raining_blocks->blocks)[index]);
        }
    }
}


struct Block *get_moving_block(struct Board *board, struct Point *loc) {
    int index;
    for (index = 0; board->blocks_vector != NULL && index < board->blocks_vector->length; ++index) {
        struct Block *block = (board->blocks_vector->blocks)[index];
        if (point_equality(block->location, loc) && block->type == MOVE) {
            return block;
        }
    }
    return NULL;
}

struct Point *moving_block_access_allowed(struct Board *board, struct Point *loc, enum directions dir) {
    int x, y, res; // x for the row index y for column index res for final result
    struct Point *new_point; // for new location
    if (dir == UP_DIR) {
        x = loc->x - 1;
        y = loc->y;
    }
    else if (dir == RIGHT_DIR) {
        x = loc->x;
        y = loc->y + 1;
    }
    else if (dir == DOWN_DIR) {
        x = loc->x + 1;
        y = loc->y;
    }
    else if (dir == LEFT_DIR) {
        x = loc->x;
        y = loc->y - 1;
    }
    else if (dir == STATIC_DIR) {
        x = loc->x;
        y = loc->y;
        return loc;
    }
    else {
        // in case of wrong direction
        return NULL;
    }
    new_point = create_point(x, y);
    char *cell;
    cell = get_board_cell(board, new_point);
    if (new_point != NULL && cell != NULL && !is_blocked(board, new_point) && !is_score(board, new_point) &&
        !is_opponent(board, new_point) && inside_board(board, new_point) && *cell != board->wall) {
        return new_point;
    }

    return NULL;

}

int is_opponent(struct Board *board, struct Point *loc) {
    int index;
    for (index = 0; board->opponent_vector != NULL && index < board->opponent_vector->length; ++index) {
        if (point_equality((board->opponent_vector->opponents)[index]->location, loc)) {
            return 1;
        }
    }
    return 0;

}

int inside_board(struct Board *board, struct Point *loc) {
    return (loc->x < board->row && loc->x > 0 && loc->y < board->col && loc->y > 0);
}

void score_fill(struct Board *board, char shape, int value, int count) {
    struct Point *loc = rand_generator(board);
    struct Score *new_score = create_score(loc, shape, value, count);
    board->scores_vector = push_score(board->scores_vector, new_score);
    (board->map)[loc->x][loc->y] = shape;
}

void remove_score(struct Board *board, struct Score *score) {
    board->scores_vector = delete_score(board->scores_vector, score);
}

void check_for_deathblock(struct Board *board, struct Player *player) {
    int index;
    struct Point *loc;
    if (player->state == UP_DIR) {
        loc = create_point(player->location->x - 1, player->location->y);
    }
    else if (player->state == RIGHT_DIR) {
        loc = create_point(player->location->x, player->location->y + 1);
    }
    else if (player->state == DOWN_DIR) {
        loc = create_point(player->location->x + 1, player->location->y);
    }
    else if (player->state == LEFT_DIR) {
        loc = create_point(player->location->x, player->location->y - 1);
    }
    else {
        return;
    }
    for (index = 0; board->blocks_vector != NULL && index < board->blocks_vector->length; ++index) {
        if (point_equality((board->blocks_vector->blocks)[index]->location, loc) &&
            (board->blocks_vector->blocks)[index]->type == DEATH) {
            game_over = 1;
        }
    }
    for (index = 0; board->raining_blocks != NULL && index < board->raining_blocks->length; ++index) {
        if ((point_equality((board->raining_blocks->blocks)[index]->location, loc) ||
             point_equality((board->raining_blocks->blocks)[index]->location, player->location)) &&
            (board->raining_blocks->blocks)[index]->type == DEATH) {
            game_over = 1;
        }
    }
}

void free_board(struct Board* board){
    if(board->target != NULL){
        free(board->target->location);
        free(board->target);
    }
    if(board->object != NULL){
        free(board->object->location);
        free(board->object);
    }
    free_linked_list(board->player_shapes, free);
    free_linked_list(board->opponent_shapes, free);
    free_linked_list(board->score_shapes, free);
    free_linked_list(board->block_shapes, free);
    free_player(board->player);
    free_opponent_vector(board->opponent_vector);
    free_block_vector(board->blocks_vector);
    free_block_vector(board->raining_blocks);
    free_score_vector(board->scores_vector);
    int i;
    for(i = 0 ; i < board->row; ++i){
        free((board->map)[i]);
    }
    free(board->map);
    free(board);
}


