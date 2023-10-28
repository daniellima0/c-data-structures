#include "./lib/prim.h"

int main()
{
    FILE *file = fopen("input.txt", "r");
    Graph graph;

    initialize_graph(&file, &graph);
    prim(&graph);

    return 0;
}