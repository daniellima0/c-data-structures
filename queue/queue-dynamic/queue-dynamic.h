#include <stdio.h>
#include <stdlib.h>

typedef int item;

typedef struct node_aux {
    item info;
    struct node_aux *next;
} node;

typedef struct {
    node *start, *end;
} queue;

queue *init_queue() {
    queue *q = (queue *)malloc(sizeof(queue));
    q->start = q->end = NULL;
    return q;
}

node *allocate() {
    node *pointer;
    pointer = (node *)malloc(sizeof(node));
    return pointer;
}

int is_queue_empty(queue *q) {
    if (q->start == NULL) return 1;
    return 0;
}

int insert_item(queue *q, item e) {
    node *novo;
    novo = allocate();
    if (!novo) return 0;

    novo->info = e;
    novo->next = NULL;
    if (is_queue_empty(q)) {
        q->start = novo;
    } else {
        q->end->next = novo;
    }
    q->end = novo;
    return 1;
}

int remove_item(queue *q, item *e) {
    node *aux;

    if (is_queue_empty(q)) return 0;
    *e = q->start->info;
    aux = q->start;

    if (q->start == q->end)
        q->start = q->end = NULL;
    else
        q->start = q->start->next;

    free(aux);
    return 1;
}

void print_queue(queue *q) {
    queue *queue_aux;
    item e;

    queue_aux = init_queue();

    while (!is_queue_empty(q)) {
        remove_item(q, &e);
        printf("%d ", e);
        insert_item(queue_aux, e);
    }

    q = queue_aux;
    printf("\n");
}

queue *destroy_queue(queue *q) {
    node *atu = q->start;
    item e;

    while (atu != NULL) {
        remove_item(q, &e);
        atu = atu->next;
    }
    q->start = q->end = NULL;
    free(q);
    return NULL;
}
