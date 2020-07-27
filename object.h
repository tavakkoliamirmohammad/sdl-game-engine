#ifndef FINALPROJECT_OBJECT_H
#define FINALPROJECT_OBJECT_H

#include "utils.h"

struct Object {
    struct Point *location;
    char shape;
};

struct Object *create_object(struct Point *loc,char shape);

struct Object *copy_object(struct Object *object);

#endif //FINALPROJECT_OBJECT_H
