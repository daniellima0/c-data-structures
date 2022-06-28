#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef char item;

typedef struct node_aux {
    struct node_aux *prev;
    item info;
    struct node_aux *next;
} node;

typedef struct {
    node *start;
    node *end;
} dllist;

dllist *init_dllist() {
    dllist *l = (dllist *)malloc(sizeof(dllist));
    l->start = NULL;
    l->end = NULL;
    return l;
}

int is_dllist_empty(dllist *l) {
    if (l->start == NULL) return 1;
    return 0;
}

node *allocate() {
    node *pointer;
    pointer = (node *)malloc(sizeof(node));
    return pointer;
}

int insert_item(dllist *l, item e) {
    node *new_node;
    new_node = allocate();
    if (!new_node) return 0;
    new_node->info = e;
    if (is_dllist_empty(l)) {
        new_node->next = NULL;
        new_node->prev = NULL;
        l->start = l->end = new_node;
    } else {
        new_node->next = NULL;
        new_node->prev = l->end;
        l->end->next = new_node;
        l->end = new_node;
    }
    return 1;
}

void print_dllist(dllist *l, int order) {
    node *current;

    switch (order) {
        case 1:
            current = l->start;
            while (current != NULL) {
                printf("%c\n", current->info);
                current = current->next;
            }
            break;
        case 2:
            current = l->end;
            while (current != NULL) {
                printf("%c\n", current->info);
                current = current->prev;
            }
            break;

        default:
            printf("invalid code");
    }
}

int remove_item(dllist *l, item e) {
    node *current = l->start;

    while ((current != NULL) && (current->info != e)) {
        current = current->next;
    }

    if (current == NULL) return 0;

    if (l->start == l->end) {
        l->start = l->end = NULL;
    } else {
        if (l->start == current) {
            l->start = current->next;
            current->next->prev = NULL;
        } else {
            if (l->end == current) {
                l->end = current->prev;
                current->prev->next = NULL;
            } else {
                current->next->prev = current->prev;
                current->prev->next = current->next;
            }
        }
    }
    free(current);
    return 1;
}

node *search_item(dllist *l, item e) {
    node *current;
    current = l->start;
    while ((current != NULL) && (current->info != e)) {
        current = current->next;
    }
    return current;
}

dllist *destroy_dllist(dllist *l) {
    node *current;
    current = l->start;
    while (current != NULL) {
        l->start = current->next;
        free(current);
        current = l->start;
    }
    free(l);
    return NULL;
}

#endif