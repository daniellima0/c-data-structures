#include "./lib/graph.h"
#include "./lib/flooding.h"
#include "./lib/prim.h"

int main()
{
    FILE *arq = fopen("input.txt", "r");
    Graph grafo;

    initialize_graph(&arq, &grafo);
    if (conta_conexo(&grafo) != 1)
    {
        printf("Não existe um árvore geradora minima.\n");
        return 0;
    }
    else
    {
        prim(&grafo);
    }

    return 0;
}