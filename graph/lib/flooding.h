#ifndef FLOODING
#define FLOODING

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "queue.h"
#include "graph.h"

void flooding(Graph *graph, int *visited, int start);

int map_vertices(Vertex *vertex, Graph *graph);

void flooding(Graph *graph, int *visited, int start)
{
    queue queue;
    init_queue(&queue);
    visited[start] = 1;
    insert_item(&queue, start);
    while (!is_queue_empty(&queue))
    {
        int s;
        remove_item(&queue, &s);
        Node *aux_node = graph->root[s].adjacency_list;
        int i;
        for (i = 0; i < graph->root[s].num_edges; i++)
        {
            aux_node = aux_node->next_node;
            int v = map_vertices(aux_node->vertex, graph);
            if (!visited[v])
            {
                visited[v] = 1;
                insert_item(&queue, v);
            }
        }
    }
}

int map_vertices(Vertex *vertex, Graph *graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        if (vertex == &graph->root[i])
        {
            return i;
        }
    }
    return -1;
}

int count_connected_components(Graph *graph)
{
    int i, count = 0;
    int visited[graph->num_vertices];
    memset(visited, 0, sizeof(visited));
    for (i = 0; i < graph->num_vertices; i++)
    {
        if (!visited[i])
        {
            flooding(graph, visited, i);
            count++;
        }
    }
    return count;
}

#endif