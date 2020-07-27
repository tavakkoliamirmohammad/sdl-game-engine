#ifndef UTILS_H
#define UTILS_H
#define UPARROW 72
#define DOWNARROW 80
#define RIGHTARROW 77
#define LEFTARROW 75
#include <stdio.h>

struct Point {
    int x, y; // x number of rows, y number of columns
};

enum directions {
    UP_DIR, RIGHT_DIR, DOWN_DIR, LEFT_DIR, STATIC_DIR
};


int point_equality(struct Point *p1, struct Point *p2);

struct Point *create_point(int x, int y);

double calculate_distance(struct Point *point1,struct Point *point2);

int is_char_available(char *string,char key);

void *my_realloc(void *mem, size_t size);


#endif