#include "./graph.h"
#include <string.h>

int getNumberOfVertices(FILE *filePointer)
{
    rewind(filePointer);

    int numberOfVertices = 0;
    char currentChar = fgetc(filePointer);

    while (currentChar != '\n')
    {
        if (currentChar == ' ')
        {
            currentChar = fgetc(filePointer);
            continue;
        }

        numberOfVertices++;
        currentChar = fgetc(filePointer);
    }

    return numberOfVertices;
}

char *getVertices(FILE *filePointer, int numberOfVertices)
{
    rewind(filePointer);

    char *vertices = (char *)malloc(numberOfVertices * sizeof(char));
    int counter = 0;
    char currentChar = fgetc(filePointer);

    while (currentChar != '\n')
    {
        if (currentChar == ' ')
        {
            currentChar = fgetc(filePointer);
            continue;
        }

        vertices[counter] = currentChar;
        counter++;
        currentChar = fgetc(filePointer);
    }

    return vertices;
}

char **getAdjacencyLists(FILE *filePointer, char *vertices, int numberOfVertices)
{
    int **adjacencyMatrix = (int **)malloc(numberOfVertices * sizeof(int *));

    for (size_t i = 0; i < numberOfVertices; i++)
    {
        adjacencyMatrix[i] = (int *)malloc(numberOfVertices * sizeof(int));
    }

    for (size_t col = 0; col < numberOfVertices; col++)
    {
        for (size_t line = 0; line < numberOfVertices; line++)
        {
            fscanf(filePointer, "%d", &(adjacencyMatrix[col][line]));
        }
    }

    char **adjacencyLists = (char **)malloc(numberOfVertices * sizeof(char *));

    for (size_t i = 0; i < numberOfVertices; i++)
    {
        adjacencyLists[i] = (char *)malloc(numberOfVertices * sizeof(char));
    }

    for (size_t col = 0; col < numberOfVertices; col++)
    {
        int cc = 0;
        for (size_t line = 0; line < numberOfVertices; line++)
        {
            if (adjacencyMatrix[col][line] == 1)
            {
                adjacencyLists[col][cc] = vertices[line];
                cc++;
            }
            else
            {
                adjacencyLists[col][line] = ' ';
            }
        }
    }

    return adjacencyLists;
}

Graph initializeGraph(FILE *filePointer)
{
    // Check if file exists
    if (filePointer == NULL)
    {
        perror("Error opening the file");
        return (Graph){0};
    }

    Graph graph = {
        .numberOfVertices = 0,
        .adjacencyLists = NULL,
        .vertices = NULL};

    graph.numberOfVertices = getNumberOfVertices(filePointer);
    graph.vertices = getVertices(filePointer, graph.numberOfVertices);
    graph.adjacencyLists = getAdjacencyLists(filePointer, graph.vertices, graph.numberOfVertices);

    return graph;
}

void printGraph(Graph graph)
{
    printf("----Graph----\n\n");

    printf("Number of Vertices:\n");
    printf("%d\n", graph.numberOfVertices);

    printf("\nAdjacency Lists:\n");
    for (size_t i = 0; i < graph.numberOfVertices; i++)
    {
        printf("%c -> ", graph.vertices[i]);
        for (size_t j = 0; j < graph.numberOfVertices; j++)
        {
            printf("%c ", graph.adjacencyLists[i][j]);
        }
        printf("\n");
    }

    printf("\n\nVertices:\n");
    for (size_t i = 0; i < graph.numberOfVertices; i++)
    {
        printf("%c ", graph.vertices[i]);
    }
    printf("\n");
}
