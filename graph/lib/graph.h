#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node
{
    struct Vertex *vertex;
    struct Node *next_node;
    int weight;
} Node;

typedef struct Vertex
{
    char label[20];
    int degree;
    int num_edges;
    Node *adjacency_list;
} Vertex;

typedef struct
{
    int num_vertices;
    int num_edges;
    struct Vertex *root;
} Graph;

// Função para inicializar o Grafo
void initialize_graph(FILE **file, Graph *graph);
// Alocar dinamicamente um No
Node *allocate_node();
// Retorna o estado do Grafo (vazio ou não)
int is_graph_empty(Graph *graph);
// Contando o numero de vertices
int get_num_vertices(FILE **file, Graph *graph);
// Aloca todos os vertices do Grafo com base no retoro de "get_num_vertices();"
void allocate_vertices(FILE **file, Graph *graph);
// Insere os Nós nos vértices
void insert_vertex(Graph *graph, char *row, Vertex *vertex);
// Povoando a lista de adjacentes
void populate_adjacency_list(FILE *file, Graph *graph, Vertex *vertices);
// Imprime o Grafo
void print_graph(Graph *graph);

int is_graph_empty(Graph *graph)
{
    if (graph->root == NULL)
        return 1;
    return 0;
}

Node *allocate_node()
{
    Node *new_node;
    new_node = (Node *)malloc(sizeof(Node));
    return new_node;
}

void initialize_graph(FILE **file, Graph *graph)
{
    if (!file)
    {
        printf("Couldn't open file\n");
        exit(0);
    }

    (*graph).num_vertices = 0;
    (*graph).num_edges = 0;
    (*graph).root = NULL;

    get_num_vertices(file, graph);
    allocate_vertices(file, graph);
}

int get_num_vertices(FILE **file, Graph *graph)
{
    rewind(*file);
    int i, num_space = 0;

    char row[100];
    char *result;
    result = fgets(row, 100, *file);

    if (!result)
    {
        printf("Error reading header\n");
        return 0;
    }

    int row_size = strlen(row);

    for (i = 0; i < (row_size); i++)
    {
        if (isspace(row[i]))
        {
            num_space++;
        }
    }

    graph->num_vertices = num_space;
    // printf("Number of vertices: %d\n", graph->num_vertices);

    return (graph->num_vertices);
}

void allocate_vertices(FILE **file, Graph *graph)
{
    // Creating a vector of type vertex. Where each position represents a vertex with its structure.
    graph->root = (Vertex *)malloc(sizeof(Vertex) * graph->num_vertices);

    // Setting the first position of the vector as the root of the graph.
    graph->root = &graph->root[0];
    rewind(*file);
    char row[100];
    char *result = fgets(row, 100, *file);
    int flag = 0; // Marcando a primeira leitura.
    char *t;
    int i;
    for (i = 0; i < (graph->num_vertices) - 1; i++)
    {
        graph->root[i].degree = 0; // Todos os vertices iniciam com grau zero
        graph->root[i].num_edges = 0;
        if (flag == 0)
        {
            t = strtok(row, " ");
            strcpy(graph->root[i].label, t); // Inserindo em cada vertex o seu nome
            flag++;
        }
        else
        {
            t = strtok(NULL, " ");
            strcpy(graph->root[i].label, t);
        }
    }

    // Treating the reading of "\n"
    t = strtok(NULL, "\n");
    strcpy(graph->root[i].label, t);

    // All vertices start with degree of zero
    graph->root[i].degree = 0;
    graph->root[i].num_edges = 0;

    // Printing the vertices labels
    // for(i=0; i< graph->num_vertices; i++){
    //     printf("(%s)", graph->root[i].label);
    // }
    // printf("\n");

    populate_adjacency_list(*file, graph, graph->root);
}

void populate_adjacency_list(FILE *file, Graph *graph, Vertex *vertices)
{
    char row[100];
    char *result;
    int i = 0;
    while (!feof(file)) // Reads a row (including with the '\n')
    {
        result = fgets(row, 100, file); // 'fgets' reads up until 99 characters or until the '\n'
        if (result)                     // If it was possible to read the row
        {
            // printf("Row %d : %s", i, row);
            insert_vertex(graph, row, &vertices[i++]); // Inserting the vertex in the adjacency list
        }
    }
    // printf("\n");
    graph->num_edges /= 2;
}

void insert_vertex(Graph *graph, char *row, Vertex *vertex)
{
    char *t;
    int flag = 0, i;
    vertex->adjacency_list = allocate_node();
    Node *no = (*vertex).adjacency_list;

    no->vertex = vertex;

    for (i = 0; i < (graph->num_vertices) - 1; i++)
    {
        if (flag == 0)
        {
            t = strtok(row, " ");
            if (atoi(t) != -1)
            {
                Node *new_node = allocate_node();
                new_node->vertex = &graph->root[i];
                no->next_node = new_node;
                no->weight = atoi(t); // String -> Int
                no = new_node;
                vertex->num_edges++;

                if (vertex != &graph->root[i])
                {
                    graph->root[i].degree++;
                    graph->num_edges++;
                }
                else
                {
                    graph->root[i].degree += 2;
                    graph->num_edges += 2;
                }
            }
            flag++;
        }
        else
        {
            t = strtok(NULL, " ");
            if (atoi(t) != -1)
            {
                Node *new_node = allocate_node();
                new_node->vertex = &graph->root[i];
                no->next_node = new_node;
                no->weight = atoi(t); // String -> Int
                no = new_node;

                vertex->num_edges++;

                if (vertex != &graph->root[i])
                {
                    graph->root[i].degree++;
                    graph->num_edges++;
                }
                else
                {
                    graph->root[i].degree += 2;
                    graph->num_edges += 2;
                }
            }
        }
    }

    t = strtok(NULL, "\n");
    if (atoi(t) != -1)
    {
        Node *new_node = allocate_node();
        new_node->vertex = &graph->root[i];
        no->next_node = new_node;
        no->weight = atoi(t); // String -> Int
        no = new_node;

        vertex->num_edges++;

        if (vertex != &graph->root[i])
        {
            graph->root[i].degree++;
            graph->num_edges++;
        }
        else
        {
            graph->root[i].degree += 2;
            graph->num_edges += 2;
        }
    }
}

void print_graph(Graph *graph)
{
    int i = 0;
    printf("Number of edges: %d\n", graph->num_edges);
    for (i = 0; i < graph->num_vertices; i++)
    {
        Vertex *vertice_aux = &graph->root[i];
        Node *no = vertice_aux->adjacency_list;
        printf("Vertex: %s\n", vertice_aux->label);
        while (no->next_node != NULL)
        {
            printf("%s -> %s | Degree: %d | Number of Edges: %d | Weight: %d\n", graph->root[i].label, no->next_node->vertex->label, graph->root[i].degree, graph->root[i].num_edges, no->weight);
            no = no->next_node;
        }
        printf("\n");
    }
}

#endif