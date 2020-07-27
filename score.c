#include <stdlib.h>
#include "score.h"
#include "utils.h"

struct Score *create_score(struct Point *loc, char shape, int value, int count) {
    struct Score *new_score = (struct Score *) malloc(sizeof(struct Score));
    new_score->location = create_point(loc->x, loc->y);
    new_score->shape = shape;
    new_score->value = value;
    new_score->count = count;
    return new_score;
}

// checking whether 2 points are located in the same location
int score_equality(struct Score *score1, struct Score *score2) {
    return (score1->shape == score2->shape && score1->value == score2->value &&
            point_equality(score1->location, score2->location) && score1->count == score2->count);
}

struct ScoreVector *push_score(struct ScoreVector *score_vector, struct Score *score) {
    int len;
    if (score == NULL) {
        return score_vector;
    }
    if (score_vector == NULL) {
        score_vector = (struct ScoreVector *) malloc(sizeof(struct ScoreVector));
        score_vector->length = 1;
    }
    else {
        len = score_vector->length;
        ++(score_vector->length);
        score_vector = (struct ScoreVector *) my_realloc(score_vector, (len + 1) * sizeof(struct ScoreVector));
    }
    if (score_vector->length == 1) {
        score_vector->scores = (struct Score **) malloc(sizeof(struct Score *));
    }
    else {
        len = score_vector->length;
        score_vector->scores = (struct Score **) my_realloc(score_vector->scores, (len + 1) * sizeof(struct Score *));
    }
    (score_vector->scores)[score_vector->length - 1] = (struct Score *) malloc(sizeof(struct Score));
    (score_vector->scores)[score_vector->length - 1] = copy_score(score);
    return score_vector;
}

struct Score *copy_score(struct Score *score) {
    struct Score *new_score = (struct Score *) malloc(sizeof(struct Score));
    new_score->location = create_point(score->location->x, score->location->y);
    new_score->shape = score->shape;
    new_score->value = score->value;
    new_score->count = score->count;
    return new_score;
}

int search(struct ScoreVector *score_vector, struct Score *score) { // returns index of the target score in the vector
    int index;
    for (index = 0; index < score_vector->length; ++index) {
        if (score_equality(score_vector->scores[index], score)) {
            return index;
        }
    }
    return -1;
}

struct Score *get_score(struct ScoreVector *score_vector, struct Point *loc) {
    int index;
    for (index = 0; score_vector != NULL && index < score_vector->length; ++index) {
        if (point_equality((score_vector->scores)[index]->location, loc)) {
            return (score_vector->scores)[index];
        }
    }
    return NULL;
}

int score_exists(struct ScoreVector *scores_vector, struct Point *loc) {
    int index;
    for (index = 0; scores_vector != NULL && index < scores_vector->length; ++index) {
        if (point_equality((scores_vector->scores)[index]->location, loc)) {
            return 1;
        }
    }
    return 0;
}


struct ScoreVector *delete_score(struct ScoreVector *score_vector, struct Score *score) {
    int index;
    index = search(score_vector, score);
    if (score == NULL || score_vector == NULL || index == -1) {
        return score_vector;
    }
    free((score_vector->scores)[index]); // warning!!!!
    shift(score_vector, index + 1);
    score_vector->length -= 1;
    return score_vector;
}

void shift(struct ScoreVector *score_vector, int index) {
    int i;
    for (i = index; i < score_vector->length; ++i) {
        (score_vector->scores)[i - 1] = (score_vector->scores)[i];
    }
}

char *get_score_shapes(struct ScoreVector *score_vector) {
    int index, counted_index, new_size;
    char *already_counted = (char *) malloc(sizeof(char));
    counted_index = 0;
    new_size = 1;
    for (index = 0; score_vector != NULL && index < score_vector->length; ++index) {
        if (counted_index == 0) {
            ++new_size;
            already_counted = (char *) my_realloc(already_counted, new_size * sizeof(char));
            already_counted[counted_index] = (score_vector->scores)[index]->shape;
            ++counted_index;
            already_counted[counted_index] = '\0';
        }
        else if (!is_char_available(already_counted, (score_vector->scores)[index]->shape)) {
            ++new_size;
            already_counted = (char *) my_realloc(already_counted, new_size * sizeof(char));
            already_counted[counted_index] = (score_vector->scores)[index]->shape;
            ++counted_index;
            already_counted[counted_index] = '\0';
        }
    }
    return already_counted;
}

void free_Score(struct Score *score) {
    free(score->location);
    free(score);
}

void free_score_vector(struct ScoreVector *scoreVector) {
    if (scoreVector == NULL) {
        return;
    }
    int i;
    for (i = 0; i < scoreVector->length; ++i) {
        free_Score((scoreVector->scores)[i]);
    }
    free(scoreVector);
}
