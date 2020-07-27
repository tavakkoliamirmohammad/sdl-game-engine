#ifndef FINALPROJECT_ARTIFICIAL_OPP_H
#define FINALPROJECT_ARTIFICIAL_OPP_H

#include "utils.h"


struct Opponent {
    struct Point *location;
    char symbol;
    int score;

};

struct OpponentVector {
    struct Opponent **opponents;
    unsigned int length;
};

struct Opponent *create_opponent(struct Point *loc, char symbol, int score);

struct Opponent *copy_opponent(struct Opponent *opponent);

struct OpponentVector *push_opponent(struct OpponentVector *opponent_vector, struct Opponent *opponent);

int opponent_exists(struct Opponent *opponent, struct Point *loc);

void shift_opp(struct OpponentVector *opponent_vector, int index);

int search_opp(struct OpponentVector *opponent_vector, struct Opponent *opponent);

int opp_equality(struct Opponent *opp1, struct Opponent *opp2);

struct OpponentVector *delete_opponent(struct OpponentVector *opponent_vector, struct Opponent *opponent);

int check_opponent_existence(struct OpponentVector *opponent_vector, struct Point *loc);

void free_opponent(struct Opponent* opponent);

void free_opponent_vector(struct OpponentVector* opponentVector);

#endif //FINALPROJECT_ARTIFICIAL_OPP_H
