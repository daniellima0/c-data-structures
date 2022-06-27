#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#define MAX 100

typedef char
    item;

typedef struct {
    int top;
    item item[MAX];
} stack;

void init_stack(stack *s) {
    s->top = -1;
}

int is_stack_empty(stack *s) {
    if (s->top == -1) return 1;
    return 0;
}

int is_stack_full(stack *s) {
    if (s->top == MAX - 1) return 1;
    return 0;
}

int push(stack *s, item e) {
    if (is_stack_full(s) == 1) return 0;
    s->top++;
    s->item[s->top] = e;
    return 1;
}

int pop(stack *s, item *e) {
    if (is_stack_empty(s)) return 0;
    *e = s->item[s->top];
    s->top--;
    return 1;
}

int top(stack *s, item *e) {
    if (is_stack_empty(s)) return 0;
    *e = s->item[s->top];
    return 1;
}

void print_stack(stack s) {
    item e;
    printf("\n");
    while (!is_stack_empty(&s)) {
        pop(&s, &e);
        printf("%c ", e);
    }
}

int get_stack_height(stack *s) {
    return s->top + 1;
}

#endif