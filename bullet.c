#include <stdio.h>
#include <stdlib.h>
#include "bullet.h"
#include "token2.h"

struct Bullet *create_bullet(char shape,enum directions dir,struct Point *loc){
    struct Bullet *bullet = (struct Bullet *)malloc(sizeof(struct Bullet));
    bullet -> shape = shape;
    bullet -> dir = dir;
    bullet -> location = loc;
    return bullet;
}

void update_bullet_loc(struct Bullet *bullet){
    if (bullet -> dir == UP_DIR){
        bullet -> location -> x -= 1;
    }
    else if (bullet -> dir == RIGHT_DIR){
        bullet -> location -> y += 1;
    }
    else if (bullet -> dir == DOWN_DIR){
        bullet -> location -> x += 1;
    }
    else if (bullet -> dir == LEFT_DIR){
        bullet -> location -> y -= 1;
    }
}

int get_bullet_range(struct LinkedList *rules){
    int index,list_len,bullet_range;
    bullet_range = 0;
    list_len = len(rules);
    for (index = 0;index < list_len;++index){
        struct TokenVector *item = (struct TokenVector *)get_data(rules,index);
        if (item -> type == ATTACK){
            bullet_range = atoi((char *)get_data(item->info,0));
        }
    }
    return bullet_range;
}

struct Bullet *copy_bullet(struct Bullet *bullet){
    struct Bullet *new_bullet = (struct Bullet *)malloc(sizeof(struct Bullet));
    new_bullet -> shape = bullet -> shape;
    new_bullet -> location = create_point(bullet -> location -> x,bullet -> location -> y);
    new_bullet -> dir = bullet -> dir;
    return new_bullet;

}

