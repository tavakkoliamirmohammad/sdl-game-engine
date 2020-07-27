#ifndef FINALPROJECT_HEAP_H
#define FINALPROJECT_HEAP_H

#include "utils.h"


struct Cell {
    double f;
    struct Point *point;
};

struct MinHeap {
    struct Cell **pCell;
    int capacity; // maximum possible size of min heap
    int size; // Current number of elements in min heap
};

struct MinHeap *initialize_min_heap(int capacity);

int heap_parent(int i);

int heap_left(int i);

int heap_right(int i);

struct Cell *heap_get_min(struct MinHeap *heap);

void swap_cell(struct Cell **c1, struct Cell **c2);

void heap_insert_key(struct MinHeap *heap, double f,int x,int y);

void heap_decreaseKey(struct MinHeap *heap, int i, double new_val);

struct Cell *heap_extract_min(struct MinHeap *heap);

void min_heapify(struct MinHeap *heap, int i);

void heap_deleteKey(struct MinHeap *heap, int i);

int search_key(struct MinHeap *heap,struct Cell *cell);

int is_empty(struct MinHeap *heap);

#endif //FINALPROJECT_HEAP_H
