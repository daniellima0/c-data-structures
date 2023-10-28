#include "flooding.h"

const int max = 1e5;

void prim(Graph *graph)
{
    if (count_connected_components(graph) != 1)
    {
        printf("The graph must have only one connected component.\n");
        return;
    }

    int visited[graph->num_vertices];
    memset(visited, 0, sizeof(visited));
    visited[0] = 1;
    Vertex *vertex = &graph->root[0];
    Node *node = vertex->adjacency_list;
    int i, j, n = graph->num_vertices;
    for (i = 0; i < n - 1; i++)
    {
        Node *s;
        int p_min = max, k = 0;
        for (j = 0; j < n; j++)
        {
            if (visited[j])
            {
                Node *node = graph->root[j].adjacency_list;
                while (node->next_node != NULL)
                {
                    if (node->weight < p_min && !visited[map_vertices(node->next_node->vertex, graph)])
                    {
                        p_min = node->weight;
                        s = node;
                        k = j;
                    }
                    node = node->next_node;
                }
            }
        }
        visited[map_vertices(s->next_node->vertex, graph)] = 1;
        printf("%s->%s\n", graph->root[k].label, s->next_node->vertex->label);
    }
}