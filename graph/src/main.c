#include <stdio.h>
#include <string.h>
#include "../lib/graph.h"

int main()
{
    FILE *file = fopen("adjacencyMatrix.txt", "r");

    Graph graph = {
        .numberOfVertices = 0,
        .adjacencyLists = NULL,
        .vertices = NULL};

    graph = initializeGraph(file);
    printGraph(graph);

    fclose(file);
}