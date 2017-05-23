#include <stdio.h>
#include "grafo.h"

struct no{
    int vertice;
    int peso;
    struct no* prox;
};

struct grafo{
    int qt_verts, qt_arestas;
    int *grau;
    No **aresta;
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

    G->aresta = (No **)malloc(n_vertices * sizeof(No *));
    if(G->aresta == NULL){
        free(G->grau);
        free(G);
        return NULL;
    }

    int i;
    for(i = 0; i < n_vertices; i++)
        G->aresta[i] = NULL;
    return G;
}

int insere_aresta(Grafo *G, int V1, int V2, int P){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    No *aux = G->aresta[V1];
    while(aux != NULL && aux->vertice != V2)
        aux = aux->prox;

    if(aux != NULL)
        return 0;

    No *novo = (No *)malloc(sizeof(No));
    if(novo == NULL)
        return -2;
//BLOCO DA DUVIDA
    novo->vertice = V2;
    novo->peso = P;
    novo->prox = G->aresta[V1];
    G->aresta[V1] = novo;
//TA CERTO ESSA PORRA ^ ?
    G->qt_arestas++;
    G->grau[V1]++;
    G->grau[V2]++;

    return 1;
}

int verifica_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    No *aux = G->aresta[V1];
    while(aux != NULL && aux->vertice != V2)
        aux = aux->prox;
    if(aux == NULL)
        return 0;
    else
        return 1;
}

int remove_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    No *ant = NULL, *aux = G->aresta[V1];
    while(aux != NULL && aux->vertice != V2){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL)
        return 0;
    if(ant == NULL)
        G->aresta[V1] = aux->prox;
    else
        ant = aux->prox;
    free(aux);
    G->qt_arestas--;
    G->grau[V1]--;
    G->grau[V2]--;

    return 1;
}

int consulta_aresta(Grafo *G, int V1, int V2, int *P){
    if(G == NULL || V1 < 0 || V1 >= G->qt_verts || V2 < 0 || V2 >= G->qt_verts)
        return -1;

    No *aux = G->aresta[V1];
    while(aux != NULL && aux->vertice != V2)
        aux = aux->prox;

    if(aux == NULL)
        return 0;
    else{
        *P = aux->peso;
        return 1;
    }
}

void libera_grafo(Grafo **G){
    int i;
    No *aux, *aux2;
    for(i = 0; i < (*G)->qt_verts; i++){
        aux = (*G)->aresta[i];
        while(aux != NULL){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
    }
    free((*G)->aresta);
    free((*G)->grau);
    free((*G));
    *G = NULL;
}

void mostra_adjacentes(Grafo *G, int V){
    if(G == NULL || V < 0 || V >= G->qt_verts)
        printf("Grafo inexistente ou vertice invalido\n");
    else{
        No *aux = G->aresta[V];
        if(aux == NULL)
            printf("O vertice %d nao possui vertices adjacentes\n", V);
        else{
            while(aux != NULL){
                printf("%d -> %d = %d\n", V, aux->vertice, aux->peso);
                aux = aux->prox;
            }
        }
    }
}

void mostra_grafo(Grafo *G){
    if(G == NULL)
        printf("Grafo inexistente\n");
    else if(G->qt_arestas == 0)
        printf("Grafo vazio\n");
    else{
        int i;
        for(i = 0; i < G->qt_verts; i++){
            printf("Vertice %d: \n", i);
            mostra_adjacentes(G, i);
        }
    }
}
