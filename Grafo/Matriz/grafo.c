#include <stdio.h>
#include "grafo.h"

struct grafo{
    int qt_verts, qt_arestas;
    int *grau;
    int **aresta;
};

Grafo *cria_grafo(int n_vertices){
    if(n_vertices <= 0)
        return NULL;

    Grafo *G = (Grafo *)malloc(sizeof(Grafo));
    if(G == NULL)
        return NULL;

    G->qt_verts = n_vertices;
    G->qt_arestas = 0;

    G->grau = (int *)calloc(n_vertices, sizeof(int));
    if(G->grau == NULL){
        free(G);
        return NULL;
    }

    G->aresta = (int **) malloc(n_vertices * sizeof(int *));
    if(G->aresta == NULL){
        free(G->grau);
        free(G);
        return NULL;
    }

    int i, k;
    for(i = 0; i < n_vertices; i++){
        G->aresta[i] = (int *)calloc(n_vertices, sizeof(int));
        if(G->aresta[i] == NULL){
            for(k = 0; k < i; k++)
                free(G->aresta[k]);
            free(G->aresta);
            free(G->grau);
            free(G);
            return NULL;
        }
    }
    return G;
}

int insere_aresta(Grafo *G, int V1, int V2, int P){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    if(G->aresta[V1][V2] != 0)
        return 0;

    G->aresta[V1][V2] = P;
    G->qt_arestas++;
    G->grau[V1]++;
    G->grau[V2]++;
    return 1;
}

int verifica_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    if(G->aresta[V1][V2] == 0)
        return 0;
    else
        return 1;
}

int remove_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    if(G->aresta[V1][V2] == 0)
        return 0;

    G->aresta[V1][V2] = 0;
    G->qt_arestas--;
    G->grau[V1]--;
    G->grau[V2]--;
    return 1;
}

int consulta_aresta(Grafo *G, int V1, int V2, int *P){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    if(G->aresta[V1][V2] == 0)
        return 0;

    *P = G->aresta[V1][V2];
    return 1;
}


void mostra_adjacentes(Grafo *G, int V){
     if(G == NULL || V < 0 || V >= G->qt_verts)
        printf("Grafo inexistente ou vertice invalido\n");
     else{
        int i, count = 0;
        for(i = 0; i < G->qt_verts; i++){
            if(G->aresta[V][i] != 0){
                printf("%d -> %d = %d\n", V, i, G->aresta[V][i]);
                count++;
            }
        }
        if(count == 0)
            printf("O vertice %d nao possui vertices adjacentes\n", V);
     }
}

void mostra_grafo(Grafo *G){
    if(G == NULL)
        printf("Grafo inexistente");
    else if(G->qt_arestas == 0)
        printf("Grafo vazio");
    else{
        int i;
        for(i = 0; i < G->qt_verts; i++){
            mostra_adjacentes(G, i);
        }
    }
}

void libera_grafo(Grafo **G){
    int i;
    for(i = 0; i < (*G)->qt_verts; i++)
        free((*G)->aresta[i]);
    free((*G)->aresta);
    free((*G)->grau);
    free((*G));
    *G = NULL;
}
