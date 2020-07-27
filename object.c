#include <stdio.h>
#include <stdlib.h>
#include "object.h"

struct Object *create_object(struct Point *loc,char shape){
    struct Object *object = (struct Object *)malloc(sizeof(struct Object));
    object -> location = loc;
    object -> shape = shape;
    return object;
}

struct Object *copy_object(struct Object *object){
    struct Object *object_copy = (struct Object *)malloc(sizeof(struct Object));
    object_copy -> location = create_point(object->location->x,object->location->y);
    object_copy -> shape = object -> shape;
    return object_copy;
}



