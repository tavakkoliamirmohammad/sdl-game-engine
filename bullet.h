#ifndef FINALPROJECT_BULLET_H
#define FINALPROJECT_BULLET_H
#define BULLET '-'
#include "utils.h"
#include "linked_list.h"

struct Bullet {
    char shape;
    enum directions dir;
    struct Point *location;
};

struct Bullet *create_bullet(char shape,enum directions dir,struct Point *loc);

void update_bullet_loc(struct Bullet *bullet);

int get_bullet_range(struct LinkedList *rules);

struct Bullet *copy_bullet(struct Bullet *bullet);

#endif //FINALPROJECT_BULLET_H
