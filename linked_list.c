#include "linked_list.h"
#include <string.h>
#include <stdio.h>

struct LinkedList *add_first_LL(struct LinkedList *head, void *data, size_t data_size) {
    struct LinkedList *new_node = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    new_node->next = head;
    new_node->prev = NULL;
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    if (head != NULL) {
        head->prev = new_node;
    }
    return new_node;
}

struct LinkedList *add_last_LL(struct LinkedList *head, void *data, size_t data_size) {
    struct LinkedList *new_node = (struct LinkedList *) malloc(sizeof(struct LinkedList));
    new_node->next = NULL;
    new_node->data = malloc(data_size);
    memcpy(new_node->data, data, data_size);
    if (head == NULL) {
        new_node->prev = NULL;
        return new_node;
    }
    struct LinkedList *head_copy;
    head_copy = head;
    while (head->next) {
        head = head->next;
    }
    new_node->prev = head;
    head->next = new_node;
    return head_copy;
}

struct LinkedList *delete_data_LL(struct LinkedList *head, void *data, int(*compare)(void *, void *)) {
    if (head == NULL) {
        return head;
    }
    struct LinkedList *head_copy;
    head_copy = head;
    while (head != NULL && compare(head->data, data)) {
        head = head->next;
    }
    if (head == NULL) {
        // in case that the data doesn't exist
        return head_copy;
    }
    if (head->next != NULL) {
        head->next->prev = head->prev;
    }
    head->prev->next = head->next;
    free(head);
    return head_copy;
}


void *search_LL(struct LinkedList *head, void *data, int(*compare)(void *, void *)) {
    if (head == NULL) {
        return NULL;
    }
    while (head != NULL && compare(head->data, data)) {
        head = head->next;
    }
    if (head == NULL) {
        return NULL;
    }
    return head->data;
}

int search_data(struct LinkedList *head, void *data) {
    int list_len, i;
    while (head != NULL) {
        if (head->data == data) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void *get_data(struct LinkedList *head, int index) {
    int list_len;
    list_len = len(head);
    if (index >= list_len) {
        return NULL;
    }
    int target_pos = 0;
    while (target_pos != index) {
        ++target_pos;
        head = head->next;
    }
    return head->data;
}

int len(struct LinkedList *head) {
    int size;
    size = 0;
    while (head != NULL) {
        head = head->next;
        size += 1;
    }
    return size;
}

void free_linked_list(struct LinkedList *linkedList, void (*func)(void *)) {
    if (linkedList == NULL) {
        return;
    }
    int i, len_LL;
    len_LL = len(linkedList);
    for (i = 0; i < len_LL; ++i) {
        (*func)(get_data(linkedList, i));
    }
    free(linkedList);
}