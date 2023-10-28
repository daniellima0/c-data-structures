#ifndef FLOODING
#define FLOODING

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "fila.h"
#include "graph.h"

void flooding(Graph *gr, int *vizitados, int start);

int mapeando_vertices(Vertex *vertex, Graph *gr);

void flooding(Graph *gr, int *vizitados, int start){
    tp_fila fila;
    inicializa_fila(&fila);
    vizitados[start] = 1;
    insere_fila(&fila, start);
    while(!fila_vazia(&fila)){
        int s;
        remove_fila(&fila, &s);
        Node *no_aux = gr->root[s].adjacency_list;
        int i;
        for(i=0; i<gr->root[s].num_edges; i++){
            no_aux = no_aux->next_node;
            int v = mapeando_vertices(no_aux->vertex, gr);
            if(!vizitados[v]){
                vizitados[v] = 1;
                insere_fila(&fila, v);
            }
        }
    }
}

int mapeando_vertices(Vertex *vertex, Graph *gr){
    int i;
    for(i=0; i<gr->num_vertices; i++){
        if(vertex == &gr->root[i]){
            return i;
        }
    }
    return -1;
}

int conta_conexo(Graph *gr){
    int i, count = 0;
    int vizitados[gr->num_vertices];
    memset(vizitados, 0, sizeof(vizitados));
    for(i=0; i<gr->num_vertices; i++){
        if(!vizitados[i]){
            flooding(gr, vizitados, i);
            count++;
        }
    }
    return count;
}

#endif