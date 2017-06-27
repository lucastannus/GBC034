#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "fila.h"

struct aresta{
    int capacidade;
    int custo;
    int delay;
    int trafego;
};

typedef struct no{
    int vertice;
    ArestaLista pesos;
    struct no *prox;
}No;

struct grafo{
    int q_vertices;
    int q_arestas;
    int *grau;
    No **arestas;
};

Grafo *cria_grafo(int qnt_vertices){
    if(qnt_vertices <= 0)
        return NULL;

    Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
    if(grafo == NULL)
        return NULL;

    grafo->grau = (int*)calloc(qnt_vertices, sizeof(int));
    if(grafo->grau == NULL){
        free(grafo);
        return NULL;
    }

    grafo->arestas = (No**)malloc(qnt_vertices * sizeof(No*));
    if(grafo->arestas == NULL){
        free(grafo->arestas);
        free(grafo);
        return NULL;
    }
    int i;

    for(i = 0; i < qnt_vertices; i++)
        grafo->arestas[i] = NULL;

    grafo->q_arestas = 0;
    grafo->q_vertices = qnt_vertices;

    return grafo;
}

int verifica_aresta(Grafo *grafo, int vO, int vD){
    if(grafo == NULL || vO < 0 || vD < 0 || vO >= grafo->q_vertices || vD >= grafo->q_vertices)
        return -1;

    No *aux;

    aux = grafo->arestas[vO];
    while(aux != NULL && aux->vertice != vD)
        aux = aux->prox;

    if(aux == NULL)
        return 0; //ARESTA NAO EXISTE
    else
        return 1; //ARESTA EXISTE
}

int insere_aresta(Grafo *grafo, int vO, int vD, int capacidade, int custo, int delay, int trafego){
    if(grafo == NULL || vO < 0 || vD < 0 || vO >= grafo->q_vertices || vD >= grafo->q_vertices || vO == vD)
        return -1;

    if(capacidade < 1 || custo < 1 || delay < 1 || trafego < 1)
        return -1;

    if((verifica_aresta(grafo, vO, vD)) == 1)
        return 0;

    No *novo1 = (No*)malloc(sizeof(No));
    if(novo1 == NULL)
        return -1;

    novo1->pesos.capacidade = capacidade;
    novo1->pesos.custo = custo;
    novo1->pesos.delay = delay;
    novo1->pesos.trafego = trafego;

    novo1->vertice = vD;
    novo1->prox = grafo->arestas[vO];
    grafo->arestas[vO] = novo1;

    No *novo2 = (No*)malloc(sizeof(No));
    if(novo2 == NULL)
        return -1;

    novo2->pesos.capacidade = capacidade;
    novo2->pesos.custo = custo;
    novo2->pesos.delay = delay;
    novo2->pesos.trafego = trafego;

    novo2->vertice = vO;
    novo2->prox = grafo->arestas[vD];
    grafo->arestas[vD] = novo2;

    grafo->q_arestas++;
    grafo->grau[vO]++;
    grafo->grau[vD]++;

    return 1;
}

int remove_aresta(Grafo *grafo, int vO, int vD){
    if(grafo == NULL || vO < 0 || vD < 0 || vO >= grafo->q_vertices || vD >= grafo->q_vertices)
        return -1;

    No *aux1, *aux2, *aux_ant;

    aux1 = grafo->arestas[vO];
    aux_ant = NULL;

    if(aux1->vertice == vD){
        grafo->arestas[vO] = aux1->prox;
        free(aux1);
        return 1;
    }

    while(aux1 != NULL && aux1->vertice != vD){
        aux_ant = aux1;
        aux1 = aux1->prox;
    }
    if(aux1 == NULL)
        return 0; //ARESTA NAO EXISTE

    aux_ant->prox = aux1->prox;
    free(aux1);

    aux2 = grafo->arestas[vD];
    aux_ant = NULL;

    if(aux2->vertice == vO){
        grafo->arestas[vD] = aux2->prox;
        free(aux2);
        return 1;
    }

    while(aux2 != NULL && aux2->vertice != vO){
        aux_ant = aux2;
        aux2 = aux2->prox;
    }
    if(aux2 == NULL)
        return 0;

    aux_ant->prox = aux2->prox;
    free(aux2);

    grafo->q_arestas--;
    grafo->grau[vO]--;
    grafo->grau[vD]--;

    return 1;
}

int consulta_aresta(Grafo *grafo, int vO, int vD, int peso){
    if(grafo == NULL || vO < 0 || vD < 0 || vO >= grafo->q_vertices || vD >= grafo->q_vertices)
        return -1;
    if(peso < 1 || peso > 4)
        return -1;

    No *aux;
    int retorno;

    aux = grafo->arestas[vO];

    while(aux != NULL && aux->vertice != vD)
        aux = aux->prox;

    if(aux == NULL)
        return 0; //ARESTA NAO EXISTE

    switch (peso){
        case 1:
            retorno = aux->pesos.capacidade;
            break;
        case 2:
            retorno = aux->pesos.custo;
            break;
        case 3:
            retorno = aux->pesos.delay;
            break;
        default:
            retorno = aux->pesos.trafego;
    }
    return retorno;
}

void libera_grafo(Grafo **grafo){
    int i;
    No *aux, *aux_ant;

    for(i = 0; i < (*grafo)->q_vertices; i++){
        aux = (*grafo)->arestas[i];

        while(aux != NULL){
            aux_ant = aux;
            aux = aux->prox;
            free(aux_ant);
        }
    }

    free((*grafo)->arestas);
    free((*grafo)->grau);
    free((*grafo));
    *grafo = NULL;
}

int num_vertices(Grafo *grafo){
    if(grafo == NULL)
        return -1;
    return grafo->q_vertices;
}

int grau_vertice(Grafo *grafo, int v){
    if(grafo == NULL || v < 0 || v >= grafo->q_vertices)
        return -1;

    return grafo->grau[v];
}

int eh_adjacente(Grafo *grafo, int v1, int v2){
    if(grafo == NULL || v1 < 0 || v2 < 0 || v1 >= grafo->q_vertices || v2 >= grafo->q_vertices)
        return -1;

    No *aux;

    aux = grafo->arestas[v1];

    while(aux != NULL && aux->vertice != v2)
        aux = aux->prox;
    if(aux == NULL)
        return 0;

    return 1;
}

void mostra_adjacentes(Grafo *grafo, int v){
    if(grafo == NULL || v < 0 || v >= grafo->q_vertices){
        printf("Grafo nao existe ou vertice invalido\n");
        return;
    }
    No *aux;

    aux = grafo->arestas[v];

    if(aux == NULL)
        printf("O vertice %d nao possui vertices adjacentes.\n", v);
    else{
        while(aux != NULL){
            printf("%d -> %d\n", v, aux->vertice);
            aux = aux->prox;
        }
    }
}

void mostra_grafo(Grafo *grafo){
    if(grafo == NULL)
        return;

    if(grafo->q_arestas == 0){
        printf("Grafo vazio\n");
        return;
    }
    int i;

    for(i = 0; i < num_vertices(grafo); i++){
        printf("Vertice %d:\n", i);
        mostra_adjacentes(grafo, i);
        printf("\n");
    }
}

void busca_profundidade(Grafo *grafo, int vO, int *visitados){
    int vaux;

    visitados[vO] = 1;
    printf("%d ", vO);

    No *aux = grafo->arestas[vO];

    while(aux != NULL){
        vaux = aux->vertice;
        aux = aux->prox;

    if(visitados[vaux] == 0)
        busca_profundidade(grafo, vaux, visitados);
    }
}

void dfs(Grafo *grafo, int vO){
    if(grafo == NULL || vO < 0 || vO > num_vertices(grafo))
        return;

    int *visitados;

    visitados = (int*)calloc(num_vertices(grafo), sizeof(int));
    if(visitados == NULL)
        return;

    printf("DFS: ");
    busca_profundidade(grafo, vO, visitados);
    printf("\n");
    free(visitados);

}

void busca_largura(Grafo *grafo, int v){
    if(grafo == NULL || v < 0 || v > num_vertices(grafo))
        return;

    int vaux;
    No *aux;

    int *visitados = (int*)calloc(num_vertices(grafo), sizeof(int));
    if(visitados == NULL)
        return;

    Fila *fila = cria_fila();

    printf("BFS: ");

    visitados[v] = 1;
    printf("%d ", v);

    insere_fila(fila, v);

    while(!(fila_vazia(fila))){
        remove_fila(fila, &vaux);
        aux = grafo->arestas[vaux];

        while(aux != NULL){
            if(visitados[aux->vertice] == 0){
                visitados[aux->vertice] = 1;
                printf("%d ", aux->vertice);
                insere_fila(fila, aux->vertice);
            }
            aux = aux->prox;
        }
    }
    printf("\n");
}

ArestaLista *dijkstra(Grafo *grafo, int v, char m, int **A){

    if(grafo == NULL || v < 0 || v >= grafo->q_vertices)
        return NULL;

    if(m != 'c' && m != 'd' && m != 'z' && m != 't')
        return NULL;

    (*A) = (int *)malloc(grafo->q_vertices * sizeof(int));
    int *S = (int *)calloc(grafo->q_vertices, sizeof(int));
    ArestaLista *D = (ArestaLista *)malloc(grafo->q_vertices * sizeof(ArestaLista));
    if((*A) == NULL || S == NULL || D == NULL)
        return NULL;

    int i;

    for(i = 0; i < grafo->q_vertices; i++){
        (*A)[i] = -1;
        D[i].capacidade = INT_MAX;
        D[i].custo = INT_MAX;
        D[i].delay = INT_MAX;
        D[i].trafego = INT_MAX;
    }

    S[v] = 1;
    D[v].capacidade = 0;
    D[v].custo = 0;
    D[v].delay = 0;
    D[v].trafego = 0;

    dijkstra_aux(grafo, v, m, S, D, (*A));

    free(S);

    return D;
}

void dijkstra_aux(Grafo *grafo, int v, char M, int *S, ArestaLista *D, int *A){
    int i, k, menor, vk, dnovo;
    No *aux;

    switch(M){
        case 'z':
            aux = grafo->arestas[v];

            while(aux != NULL){
                A[aux->vertice] = v;
                D[aux->vertice].capacidade = aux->pesos.capacidade;
                D[aux->vertice].custo = aux->pesos.custo;
                D[aux->vertice].delay = aux->pesos.delay;
                D[aux->vertice].trafego = aux->pesos.trafego;
                aux = aux->prox;
            }

            for(k = 2; k <= grafo->q_vertices; k++){
                menor = INT_MAX;

                for(i = 0; i < grafo->q_vertices; i++){
                    if(D[i].capacidade < menor && S[i] == 0){
                        menor = D[i].capacidade;
                        vk = i;
                    }
                }

                S[vk] = 1;

                aux = grafo->arestas[vk];
                while(aux != NULL){
                    dnovo = D[vk].capacidade + consulta_aresta(grafo, vk, aux->vertice, 1);
                    if(dnovo < D[aux->vertice].capacidade){
                        A[aux->vertice] = vk;
                        D[aux->vertice].capacidade = dnovo;
                        D[aux->vertice].custo = D[vk].custo + consulta_aresta(grafo, vk, aux->vertice, 2);
                        D[aux->vertice].delay = D[vk].delay + consulta_aresta(grafo, vk, aux->vertice, 3);
                        D[aux->vertice].trafego = D[vk].trafego + consulta_aresta(grafo, vk, aux->vertice, 4);
                    }
                    aux = aux->prox;
                }
            }
            break;

        case 'c':
            aux = grafo->arestas[v];

            while(aux != NULL){
                A[aux->vertice] = v;
                D[aux->vertice].capacidade = aux->pesos.capacidade;
                D[aux->vertice].custo = aux->pesos.custo;
                D[aux->vertice].delay = aux->pesos.delay;
                D[aux->vertice].trafego = aux->pesos.trafego;
                aux = aux->prox;
            }

            for(k = 2; k <= grafo->q_vertices; k++){
                menor = INT_MAX;

                for(i = 0; i < grafo->q_vertices; i++){
                    if(D[i].custo < menor && S[i] == 0){
                        menor = D[i].custo;
                        vk = i;
                    }
                }

                S[vk] = 1;

                aux = grafo->arestas[vk];
                while(aux != NULL){
                    dnovo = D[vk].custo + consulta_aresta(grafo, vk, aux->vertice, 2);
                    if(dnovo < D[aux->vertice].custo){
                        A[aux->vertice] = vk;
                        D[aux->vertice].custo = dnovo;
                        D[aux->vertice].capacidade = D[vk].capacidade + consulta_aresta(grafo, vk, aux->vertice, 1);
                        D[aux->vertice].delay = D[vk].delay + consulta_aresta(grafo, vk, aux->vertice, 3);
                        D[aux->vertice].trafego = D[vk].trafego + consulta_aresta(grafo, vk, aux->vertice, 4);
                    }
                    aux = aux->prox;
                }
            }
            break;

        case'd':
            aux = grafo->arestas[v];

            while(aux != NULL){
                A[aux->vertice] = v;
                D[aux->vertice].capacidade = aux->pesos.capacidade;
                D[aux->vertice].custo = aux->pesos.custo;
                D[aux->vertice].delay = aux->pesos.delay;
                D[aux->vertice].trafego = aux->pesos.trafego;
                aux = aux->prox;
            }

            for(k = 2; k <= grafo->q_vertices; k++){
                menor = INT_MAX;

                for(i = 0; i < grafo->q_vertices; i++){
                    if(D[i].delay < menor && S[i] == 0){
                        menor = D[i].delay;
                        vk = i;
                    }
                }

                S[vk] = 1;

                aux = grafo->arestas[vk];
                while(aux != NULL){
                    dnovo = D[vk].delay + consulta_aresta(grafo, vk, aux->vertice, 3);
                    if(dnovo < D[aux->vertice].delay){
                        A[aux->vertice] = vk;
                        D[aux->vertice].delay = dnovo;
                        D[aux->vertice].custo = D[vk].custo + consulta_aresta(grafo, vk, aux->vertice, 2);
                        D[aux->vertice].capacidade = D[vk].capacidade + consulta_aresta(grafo, vk, aux->vertice, 1);
                        D[aux->vertice].trafego = D[vk].trafego + consulta_aresta(grafo, vk, aux->vertice, 4);
                    }
                    aux = aux->prox;
                }
            }
            break;

        case 't':
            aux = grafo->arestas[v];

            while(aux != NULL){
                A[aux->vertice] = v;
                D[aux->vertice].capacidade = aux->pesos.capacidade;
                D[aux->vertice].custo = aux->pesos.custo;
                D[aux->vertice].delay = aux->pesos.delay;
                D[aux->vertice].trafego = aux->pesos.trafego;
                aux = aux->prox;
            }

            for(k = 2; k <= grafo->q_vertices; k++){
                menor = INT_MAX;

                for(i = 0; i < grafo->q_vertices; i++){
                    if(D[i].trafego < menor && S[i] == 0){
                        menor = D[i].trafego;
                        vk = i;
                    }
                }

                S[vk] = 1;

                aux = grafo->arestas[vk];
                while(aux != NULL){
                    dnovo = D[vk].trafego + consulta_aresta(grafo, vk, aux->vertice, 4);
                    if(dnovo < D[aux->vertice].trafego){
                        A[aux->vertice] = vk;
                        D[aux->vertice].trafego = dnovo;
                        D[aux->vertice].custo = D[vk].custo + consulta_aresta(grafo, vk, aux->vertice, 2);
                        D[aux->vertice].delay = D[vk].delay + consulta_aresta(grafo, vk, aux->vertice, 3);
                        D[aux->vertice].capacidade = D[vk].capacidade + consulta_aresta(grafo, vk, aux->vertice, 1);
                    }
                    aux = aux->prox;
                }
            }
            break;
    }
}

void mostra_caminho(int V1, int V2, int *A){
    if(V1 == V2)
        printf("%d ", V1);
    else if(A[V2] == -1)
        printf("Nao existe caminho de %d para %d\n", V1, V2);
    else{
        mostra_caminho(V1, A[V2], A);
        printf("%d ", V2);
    }
}

int max_delay(ArestaLista *D, int *R, int n){
    int i, max = 0;

    for(i = 0; i < n; i++){
        if(D[R[i]].delay > max)
            max = D[R[i]].delay;
    }
    return max;
}

double max_enlace(ArestaLista *D, int *R, int n, int tam){
    int i;
    double enlace = 0, max = 0;

    for(i = 0; i < n; i++){
        enlace = (D[R[i]].trafego + tam) / D[R[i]].capacidade;
        if(enlace > max)
            max = enlace;
    }
    return max;
}

//RECEBO GRAFO, ORIGEM, VETOR DE RECEPTORES, TAMANHO DO VETOR DE RECEPTORES, PESO-REFERENCIA E TAMANHO DA MENSAGEM
void arvores_multicast(Grafo *grafo, int V, int *R, int n, char M, int tam){
    int *A, i;
    int custo, D_max;
    double alfa_max;
    ArestaLista *D;

    D = dijkstra(grafo, V, M, &A);

    for(i = 0; i < n; i++){
        printf("Menor caminho entre %d e %d, com base em %c(e):\n", V, R[i], M);
        mostra_caminho(V, R[i], A);
        custo = D[R[i]].custo;
        D_max = max_delay(D, R, n);
        alfa_max = max_enlace(D, R, n, tam);
        printf("\nCusto total da arvore: %d\n", custo);
        printf("Delay fim-a-fim maximo: %d\n", D_max);
        printf("Utilizacao maxima do enlace: %.2lf\n", alfa_max);
        printf("\n");
    }
    free(D);
    free(A);
}
