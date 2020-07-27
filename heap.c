#include <stdlib.h>
#include "heap.h"
#include "utils.h"
#include <float.h>

struct MinHeap *initialize_min_heap(int capacity) {
    struct MinHeap *heap = (struct MinHeap *) malloc(sizeof(struct MinHeap));
    heap->pCell = (struct Cell **) malloc(sizeof(struct Cell *) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

int heap_parent(int i) {
    return (i - 1) / 2;
}

// to get index of left child of node at index i
int heap_left(int i) {
    return (2 * i + 1);
}

// to get index of right child of node at index i
int heap_right(int i) {
    return (2 * i + 2);
}

// Returns the minimum key (key at root) from min heap
struct Cell *heap_get_min(struct MinHeap *heap) {
    return (heap->pCell)[0];
}

struct Cell *heap_extract_min(struct MinHeap *heap) {
    if (heap->size <= 0)
        return NULL;
    if (heap->size == 1) {
        (heap->size)--;
        return (heap->pCell)[0];
    }

    // Store the minimum value, and remove it from heap
    struct Cell *root;
    root = (heap->pCell)[0];
    (heap->pCell)[0] = (heap->pCell)[heap->size - 1];
    (heap->size)--;
    min_heapify(heap, 0);
    return root;
}

// Decreases key value of key at index i to new_val
// Decreases value of key at index 'i' to new_val.  It is assumed that
// new_val is smaller than harr[i].
void heap_decreaseKey(struct MinHeap *heap, int i, double new_val) {
    ((heap->pCell)[i])->f = new_val;
    while (i != 0 && ((heap->pCell)[heap_parent(i)])->f > ((heap->pCell)[i])->f) {
        swap_cell((heap->pCell) + i, (heap->pCell) + heap_parent(i));
        i = heap_parent(i);
    }
}

// Inserts a new key 'k'
void heap_insert_key(struct MinHeap *heap, double f,int x,int y) {
    if (heap->capacity == heap->size) {
        return;
    }

    struct Cell *cell = (struct Cell *)malloc(sizeof(struct Cell));
    cell -> point = create_point(x,y);
    cell -> f = f;

    int key_index;
    key_index = search_key(heap,cell);
    if (key_index != -1 && f < (heap->pCell)[key_index]->f){
        heap_decreaseKey(heap, key_index, f);
        free(cell);
        return;
    }
    // First insert the new key at the end
    (heap->size)++;
    (heap->pCell)[heap->size - 1] = cell;
    int i;
    i = heap->size - 1;
    // Fix the min heap property if it is violated
    while (i != 0 && ((heap->pCell)[heap_parent(i)])->f > ((heap->pCell)[i])->f) {
        swap_cell((heap->pCell) + i, (heap->pCell) + heap_parent(i));
        i = heap_parent(i);
    }
}

// A recursive method to heapify a subtree with the root at given index
// This method assumes that the subtrees are already heapified
void min_heapify(struct MinHeap *heap, int i) {
    int l,r;
    l = heap_left(i);
    r = heap_right(i);
    int smallest;
    smallest = i;
    if (l < heap->size && ((heap->pCell)[l])->f < ((heap->pCell)[i])->f)
        smallest = l;
    if (r < heap->size && ((heap->pCell)[r])->f < ((heap->pCell)[smallest])->f)
        smallest = r;
    if (smallest != i) {
        swap_cell((heap->pCell) + i, (heap->pCell) + smallest);
        min_heapify(heap, smallest);
    }
}

// This function deletes key at index i. It first reduced value to minus
// infinite, then calls extractMin()
void heap_deleteKey(struct MinHeap *heap, int i) {
    heap_decreaseKey(heap, i, DBL_MIN);
    heap_extract_min(heap);
}

void swap_cell(struct Cell **c1, struct Cell **c2) {
    struct Cell *temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

int search_key(struct MinHeap *heap,struct Cell *cell){
    int index;
    for (index = 0;index < heap -> size;++index){
        if (point_equality(cell->point,(heap->pCell)[index]->point)){
            return index;
        }
    }
    return -1;
}

int is_empty(struct MinHeap *heap){
    return heap -> size == 0;
}