#include "./graph.h"
#include <string.h>

Graph initializeGraph(FILE *filePointer)
{
    // Check if file exists
    if (filePointer == NULL)
    {
        perror("Error opening the file");
        return (Graph){0};
    }

    rewind(filePointer);

    char currentChar = fgetc(filePointer);
    int numberOfVertices = 0;

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

    rewind(filePointer);

    char *vertices = (char *)malloc(numberOfVertices * sizeof(char));

    int counter = 0;
    currentChar = fgetc(filePointer);
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

    return (Graph){
        .numberOfVertices = numberOfVertices,
        .adjacencyLists = adjacencyLists,
        .vertices = vertices};
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
