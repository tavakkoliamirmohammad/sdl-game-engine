#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include "utils.h"
#include <string.h>

int point_equality(struct Point *p1,struct Point *p2){ // returns whether the 2 points are equal
    return (p1 -> x == p2 -> x && p1 -> y == p2 -> y);
}

double calculate_distance(struct Point *point1,struct Point *point2){
    return sqrt(pow(point1->x - point2->x,2) + pow(point1->y - point2->y,2));
}

struct Point *create_point(int x, int y){
    struct Point *new_point = (struct Point *)malloc(sizeof(struct Point));
    new_point -> x = x;
    new_point -> y = y;
    return new_point;
}

void *my_realloc(void *mem, size_t size) {
    char *buff = malloc(size); // allocate new space
    if (mem == NULL) {
        // if the given pointer is null so return allocated memory
        return buff;
    }
    if (buff) {
        // if allocation is successful copy the content of the old memory
        memcpy(buff, (char *) mem, size);
        free(mem); // free the old memory
    }
    // in case of failure it returns null pointer else new allocated memory
    return buff;
}

int is_char_available(char *string,char key){
    int index;
    for (index = 0;string[index];++index){
        if (string[index] == key){
            return 1;
        }
    }
    return 0;
}

