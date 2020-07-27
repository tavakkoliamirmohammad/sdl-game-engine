#include <stdio.h>
#include <stdlib.h>
#include "target.h"


struct Target *create_target(struct Point *loc,char shape){
    // create the taget with the given shape
    struct Target *target = (struct Target *)malloc(sizeof(struct Target));
    target -> location = loc;
    target -> shape = shape;
    return target;
}

struct Target *copy_target(struct Target *target){
    // return the copy of the target
    struct Target *target_copy = (struct Target *)malloc(sizeof(struct Target));
    target_copy -> location = create_point(target->location->x,target->location->y);
    target_copy -> shape = target -> shape;
    return target_copy;
}


