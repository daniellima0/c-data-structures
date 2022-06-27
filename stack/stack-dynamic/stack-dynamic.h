#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct node_aux {
    item info;
    struct node_aux *next;
} node;

typedef struct {
    node *top;
} stack;

stack *init_stack() {
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    return s;
}

int is_stack_empty(stack *s) {
    if (s->top == NULL) return 1;
    return 0;
}

node *allocate() {
    node *pointer;
    pointer = (node *)malloc(sizeof(node));
    return pointer;
}

int push(stack *s, item e) {
    node *new_node;
    new_node = allocate();
    if (!new_node) return 0;

    new_node->info = e;
    if (is_stack_empty(s)) {
        new_node->next = NULL;
    } else {
        new_node->next = s->top;
    }
    s->top = new_node;
    return 1;
}

int pop(stack *s, item *e) {
    node *aux;

    if (is_stack_empty(s)) return 0;
    *e = s->top->info;
    aux = s->top;
    s->top = s->top->next;
    free(aux);
    aux = NULL;
    return 1;
}

int top(stack *s, item *e) {
    node *aux;

    if (is_stack_empty(s)) return 0;
    *e = s->top->info;
    return 1;
}

stack *destroy_stack(stack *s) {
    node *current = s->top, *aux;
    item e;
    while (current != NULL) {
        aux = current->next;
        pop(s, &e);
        current = aux;
    }
    s->top = NULL;
    free(s);
    return NULL;
}

void print_stack(stack *s) {
    stack *stack_aux;
    item e;
    stack_aux = init_stack();

    node *current = s->top;

    while (!is_stack_empty(s)) {
        pop(s, &e);
        printf("%d ", e);
        push(stack_aux, e);
    }

    while (!is_stack_empty(stack_aux)) {
        pop(stack_aux, &e);
        push(s, e);
    }
}

#endif