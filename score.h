#ifndef SCORE_H
#define SCORE_H

#include "utils.h"

struct Score {
    char shape;
    int value;
    struct Point *location;
    int count;
};

struct ScoreVector {
    struct Score **scores;
    unsigned int length;
};

struct Score *create_score(struct Point *loc, char shape, int value, int count);

int score_equality(struct Score *score1, struct Score *score2);

struct Score *copy_score(struct Score *score);

struct ScoreVector *push_score(struct ScoreVector *score_vector, struct Score *score);

void shift(struct ScoreVector *score_vector, int index);

int search(struct ScoreVector *score_vector, struct Score *score);

struct ScoreVector *delete_score(struct ScoreVector *score_vector, struct Score *score);

int score_exists(struct ScoreVector *scores_vector, struct Point *loc);

char *get_score_shapes(struct ScoreVector *score_vector);

struct Score *get_score(struct ScoreVector *score_vector, struct Point *loc);

void free_Score(struct Score *score);

void free_score_vector(struct ScoreVector *scoreVector);

#endif