#include "graph.h"
const int max = 1e5;

void prim(Graph *gr){
    int visitados[gr->num_vertices];
    memset(visitados, 0, sizeof(visitados));
    visitados[0] = 1;
    Vertex *vertex = &gr->root[0];
    Node *no = vertex->adjacency_list;
    int i, j, n = gr->num_vertices;
    for(i=0; i<n-1; i++){
        Node *s;
        int p_min = max, k = 0;
        for(j=0; j<n; j++){
            if (visitados[j]) {
                Node *no = gr->root[j].adjacency_list;
                while(no->next_node != NULL){
                    if(no->weight < p_min && !visitados[mapeando_vertices(no->next_node->vertex, gr)]){
                        p_min = no->weight;
                        s = no;
                        k = j;
                    }
                    no = no->next_node;
                }
            }
        }
        visitados[mapeando_vertices(s->next_node->vertex, gr)] = 1;
        printf("%s->%s\n",gr->root[k].label ,s->next_node->vertex->label);
    }
}