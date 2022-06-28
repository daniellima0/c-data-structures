#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct node {
    item info;
    struct node *next;
} sllist;

sllist *init_sllist() {
    return NULL;
}

int is_sllist_empty(sllist *l) {
    if (l == NULL) return 1;
    return 0;
}

sllist *allocate() {
    sllist *new_node;
    new_node = (sllist *)malloc(sizeof(sllist));
    return new_node;
}

int insert_item(sllist **l, item e) {
    sllist *new_node, *current;
    new_node = allocate();

    if (new_node == NULL) return 0;

    new_node->info = e;
    new_node->next = NULL;

    if (is_sllist_empty(*l)) {
        *l = new_node;
    } else {
        current = *l;

        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 1;
}

void print_sllist(sllist *l) {
    sllist *current;
    current = l;
    while (current != NULL) {
        printf("%d\n", current->info);
        current = current->next;
    }
}

int get_sllist_size(sllist *l) {
    int counter = 0;
    sllist *current;
    current = l;

    while (current != NULL) {
        counter++;
        current = current->next;
    }

    return counter;
}

sllist *search_item(sllist *l, item e) {
    sllist *current;
    current = l;

    while ((current != NULL) && (current->info != e)) {
        current = current->next;
    }

    if (current == NULL) return NULL;

    return current;
}

int remove_item(sllist **l, item e) {
    sllist *prev, *current;
    current = *l;
    prev = NULL;

    while ((current != NULL) && (current->info != e)) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return 0;

    if (prev == NULL) {
        *l = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    current = NULL;

    return 1;
}

#endif