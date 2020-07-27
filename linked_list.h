#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>


struct LinkedList {
    void *data;
    struct LinkedList *prev;
    struct LinkedList *next;
};

struct LinkedList *add_first_LL(struct LinkedList *head, void *data, size_t data_size);

struct LinkedList *add_last_LL(struct LinkedList *head, void *data, size_t data_size);

struct LinkedList *delete_data_LL(struct LinkedList *head, void *data, int(*)(void *, void *));

void *search_LL(struct LinkedList *head, void *data, int(*compare)(void *, void *));

int search_data(struct LinkedList *head,void *data);

int len(struct LinkedList *head);

void *get_data(struct LinkedList *head, int index);

void free_linked_list(struct LinkedList* linkedList, void (*func)(void*));

#endif