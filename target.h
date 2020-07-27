#ifndef FINALPROJECT_TARGET_H
#define FINALPROJECT_TARGET_H

#include "utils.h"

struct Target {
    struct Point *location;
    char shape;
};

struct Target *create_target(struct Point *loc,char shape);

struct Target *copy_target(struct Target *target);



#endif //FINALPROJECT_TARGET_H
