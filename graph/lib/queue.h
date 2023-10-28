#ifndef QUEUE_STATIC_H
#define QUEUE_STATIC_H

#include <stdio.h>
#define MAX 100

typedef int item;

typedef struct
{
    item item[MAX];
    int start, end;
} queue;

void init_queue(queue *q)
{
    q->start = q->end = MAX - 1;
}

int is_queue_empty(queue *q)
{
    if (q->start == q->end)
        return 1;
    return 0;
}

int get_next_position(int position)
{
    if (position == MAX - 1)
        return 0;
    return ++position;
}

int is_queue_full(queue *q)
{
    if (get_next_position(q->end) == q->start)
        return 1;
    return 0;
}

int insert_item(queue *q, item e)
{
    if (is_queue_full(q))
        return 0;
    q->end = get_next_position(q->end);
    q->item[q->end] = e;
    return 1;
}

int remove_item(queue *q, item *e)
{
    if (is_queue_empty(q))
        return 0;
    q->start = get_next_position(q->start);
    *e = q->item[q->start];
    return 1;
}

void print_queue(queue q)
{
    item e;
    while (!is_queue_empty(&q))
    {
        remove_item(&q, &e);
        printf("\n%c", e);
    }
}

int get_queue_size(queue *q)
{
    if (is_queue_empty(q))
        return 0;
    if (q->start < q->end)
        return q->end - q->start;
    return MAX - 1 - q->start + q->end + 1;
}

#endif