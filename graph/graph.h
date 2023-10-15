#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int numberOfVertices;
    char **adjacencyLists;
    char *vertices;
} Graph;

// initializes the graph
Graph initializeGraph(FILE *filePointer);
// prints the graph
void printGraph(Graph graph);

#endif