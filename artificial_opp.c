#include <stdio.h>
#include <stdlib.h>
#include "artificial_opp.h"
#include "utils.h"
#include "board.h"

struct Opponent *create_opponent(struct Point *loc, char symbol, int score) {
    // create an opponent with the given data
    struct Opponent *opponent = (struct Opponent *) malloc(sizeof(struct Opponent));
    opponent->location = loc;
    opponent->symbol = symbol;
    opponent->score = score;
    return opponent;
}

int opponent_exists(struct Opponent *opponent, struct Point *loc) {
    // returns whether there exists an opponent in the given location
    return point_equality(opponent->location, loc);
}

int check_opponent_existence(struct OpponentVector *opponent_vector, struct Point *loc) {
    // check in the opponents vector if the opponent exists
    int index;
    for (index = 0; opponent_vector != NULL && index < opponent_vector->length; ++index) {
        if (opponent_exists((opponent_vector->opponents)[index], loc)) {
            return 1;
        }
    }
    return 0;
}

struct OpponentVector *push_opponent(struct OpponentVector *opponent_vector, struct Opponent *opponent) {
    // adding the opponent to the end of the vector
    int len;
    if (opponent == NULL) {
        return opponent_vector;
    }
    if (opponent_vector == NULL) {
        opponent_vector = (struct OpponentVector *) malloc(sizeof(struct OpponentVector));
        opponent_vector->length = 1;
    }
    else {
        len = opponent_vector->length;
        ++(opponent_vector->length);
        opponent_vector = (struct OpponentVector *) my_realloc(opponent_vector,
                                                               (len + 1) * sizeof(struct OpponentVector));
    }
    if (opponent_vector->length == 1) {
        opponent_vector->opponents = (struct Opponent **) malloc(sizeof(struct Opponent *));
    }
    else {
        len = opponent_vector->length;
        opponent_vector->opponents = (struct Opponent **) my_realloc(opponent_vector->opponents,
                                                                     (len + 1) * sizeof(struct Opponent *));
    }
    (opponent_vector->opponents)[opponent_vector->length - 1] = (struct Opponent *) malloc(sizeof(struct Opponent));
    (opponent_vector->opponents)[opponent_vector->length - 1] = copy_opponent(opponent);
    return opponent_vector;
}

struct Opponent *copy_opponent(struct Opponent *opponent) {
    // getting a copy of the opponent so that freeing it would be safe
    struct Opponent *new_opponent = (struct Opponent *) malloc(sizeof(struct Opponent));
    new_opponent->location = create_point(opponent->location->x, opponent->location->y);
    new_opponent->symbol = opponent->symbol;
    new_opponent->score = opponent->score;
    return new_opponent;
}

int opp_equality(struct Opponent *opp1, struct Opponent *opp2) {
    return (opp1->symbol == opp2->symbol && opp1->score == opp2->score &&
            point_equality(opp1->location, opp2->location));
}

int search_opp(struct OpponentVector *opponent_vector, struct Opponent *opponent) {
    // returns index of the target score in the vector
    int index;
    for (index = 0; index < opponent_vector->length; ++index) {
        if (opp_equality(opponent_vector->opponents[index], opponent)) {
            return index;
        }
    }
    return -1;
}

struct OpponentVector *delete_opponent(struct OpponentVector *opponent_vector, struct Opponent *opponent) {
    int index;
    index = search_opp(opponent_vector, opponent);
    if (opponent == NULL || opponent_vector == NULL || index == -1) {
        return opponent_vector;
    }
    if (opponent_vector->length == 1) {
        free((opponent_vector->opponents)[0]);
        free(opponent_vector);
        opponent_vector = NULL;
        return opponent_vector;
    }
    free((opponent_vector->opponents)[index]);
    shift_opp(opponent_vector, index + 1);
    opponent_vector->length -= 1;
    return opponent_vector;
}

void shift_opp(struct OpponentVector *opponent_vector, int index) {
    int i;
    for (i = index; i < opponent_vector->length; ++i) {
        (opponent_vector->opponents)[i - 1] = (opponent_vector->opponents)[i];
    }
}

void free_opponent(struct Opponent *opponent) {
    if(opponent == NULL){
        return;
    }
    free(opponent->location);
    free(opponent);
}

void free_opponent_vector(struct OpponentVector *opponentVector) {
    // removing all pointers in the opponent vector
    if (opponentVector == NULL) {
        return;
    }
    int i;
    for (i = 0; i < opponentVector->length; ++i) {
        free_opponent((opponentVector->opponents)[i]);
    }
    free(opponentVector);
}