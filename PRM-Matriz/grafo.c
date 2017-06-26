#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"
#include "fila.h"

struct aresta{
    int c;
    int d;
    int z;
    int t;
};

struct grafo{
    int qt_vertices, qt_arestas;
    int *grau;
    Aresta **aresta;
};

Grafo *cria_grafo(int n_vertices){
    if(n_vertices <= 0)
        return NULL;

    Grafo *G = (Grafo *)malloc(sizeof(Grafo));
    if(G == NULL)
        return NULL;

    G->grau = (int *)calloc(n_vertices, sizeof(int));
    if(G->grau == NULL){
        free(G);
        return NULL;
    }

    G->aresta = (Aresta **)malloc(n_vertices * sizeof(Aresta *));
    if(G->aresta == NULL){
        free(G->grau);
        free(G);
        return NULL;
    }

    int i, k;
    for(i = 0; i < n_vertices; i++){
        G->aresta[i] = (Aresta *)malloc(n_vertices * sizeof(Aresta));
        if(G->aresta[i] == NULL){
            for(k = 0; k < i; k++)
                free(G->aresta[k]);
            free(G->aresta);
            free(G->grau);
            free(G);
            return NULL;
        }
    }
    for(i = 0; i < n_vertices; i++){
        for(k = 0; k < n_vertices; k++){
            G->aresta[i][k].c = 0;
            G->aresta[i][k].d = 0;
            G->aresta[i][k].z = 0;
            G->aresta[i][k].t = 0;
        }
    }
    G->qt_vertices = n_vertices;
    G->qt_arestas = 0;
    return G;
}

int numVertices(Grafo *G){
    return G->qt_vertices;
}

int grauVertice(Grafo *G, int V){
    return G->grau[V];
}

int verifica_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_vertices || V2 < 0 || V2 >= G->qt_vertices)
        return -1;

    if(G->aresta[V1][V2].c != 0 || G->aresta[V1][V2].d != 0 || G->aresta[V1][V2].z != 0 || G->aresta[V1][V2].t != 0)
        return 1;

    return 0;
}

int insere_aresta(Grafo *G, int V1, int V2, int C, int D, int Z, int T){
    if(G == NULL || V1 < 0 || V1 >= G->qt_vertices || V2 < 0 || V2 >= G->qt_vertices)
        return -1;

    if(C <= 0 || D <= 0 || Z <= 0 || T <= 0)
        return -1;

    if(verifica_aresta(G, V1, V2) == 1)
        return 0;

    G->aresta[V1][V2].c = C;
    G->aresta[V1][V2].d = D;
    G->aresta[V1][V2].z = Z;
    G->aresta[V1][V2].t = T;
    G->aresta[V2][V1].c = C;
    G->aresta[V2][V1].d = D;
    G->aresta[V2][V1].z = Z;
    G->aresta[V2][V1].t = T;
    G->grau[V1]++;
    G->grau[V2]++;
    G->qt_arestas++;
    return 1;
}

int remove_aresta(Grafo *G, int V1, int V2){
    if(G == NULL || V1 < 0 || V1 >= G->qt_vertices || V2 < 0 || V2 >= G->qt_vertices)
        return -1;

    if(!(verifica_aresta(G, V1, V2)))
        return 0;

    G->aresta[V1][V2].c = 0;
    G->aresta[V1][V2].d = 0;
    G->aresta[V1][V2].z = 0;
    G->aresta[V1][V2].t = 0;
    G->aresta[V2][V1].c = 0;
    G->aresta[V2][V1].d = 0;
    G->aresta[V2][V1].z = 0;
    G->aresta[V2][V1].t = 0;
    G->grau[V1]--;
    G->grau[V2]--;
    G->qt_arestas--;
    return 1;
}

int consulta_aresta(Grafo *G, int V1, int V2, char M, int *P){
    if(G == NULL || V1 < 0 || V1 >= G->qt_vertices || V2 < 0 || V2 >= G->qt_vertices)
        return -1;

    if(!(verifica_aresta(G, V1, V2)))
        return 0;

    switch(M){
        case 'c':
            *P = G->aresta[V1][V2].c;
        break;
        case 'd':
            *P = G->aresta[V1][V2].d;
        break;
        case 'z':
            *P = G->aresta[V1][V2].z;
        break;
        case 't':
            *P = G->aresta[V1][V2].t;
        break;
    }
    return 1;
}

void mostra_adjacentes(Grafo *G, int V){
    if(G == NULL || V < 0 || V >= G->qt_vertices)
        printf("Grafo inexistente ou vertice invalido\n");
    else{
        int i, count;
        for(i = 0; i < G->qt_vertices; i++){
            if(verifica_aresta(G, V, i) == 1){
                printf("%d -> %d :\n", V, i);
                printf("\tC(e): %d\n", G->aresta[V][i].c);
                printf("\tD(e): %d\n", G->aresta[V][i].d);
                printf("\tZ(e): %d\n", G->aresta[V][i].z);
                printf("\tT(e): %d\n", G->aresta[V][i].t);
                count++;
            }
        }
        if(!count)
            printf("O vertice nao possui vertices adjacentes.\n");
    }
}

void busca_profudidade(Grafo *G, int V, int *visitado){
    int i;
    visitado[V] = 1;
    printf("%d ", V);
    for(i = 0; i < G->qt_vertices; i++){
        if(verifica_aresta(G, V, i) == 1 && !visitado[i])
            busca_profudidade(G, i, visitado);
    }
}

void DFS(Grafo *G, int V){
    if(G == NULL || V < 0 || V >= G->qt_vertices){
        printf("Erro.\n");
        return;
    }
    int *visitado = (int *)calloc(G->qt_vertices, sizeof(int));
    if(visitado == NULL){
        printf("Erro.\n");
        return;
    }
    printf("Ordem de visita: ");
    busca_profudidade(G, V, visitado);
    printf("\n");
    free(visitado);
}

void busca_largura(Grafo *G, int V){
    if(G == NULL || V < 0 || V >= G->qt_vertices){
        printf("Erro.\n");
        return;
    }
    int *visitado = (int *)calloc(G->qt_vertices, sizeof(int));
    if(visitado == NULL){
        printf("Erro.\n");
        return;
    }
    Fila *f = cria_fila();
    if(f == NULL){
        printf("Erro.\n");
        return;
    }
    int i, head;
    visitado[V] = 1;
    printf("Ordem de visita: %d ", V);
    enfileira(f, V);
    while(!fila_vazia(f)){
        head = cabeca(f);
        desenfileira(f);
        for(i = 0; i < G->qt_vertices; i++){
            if(verifica_aresta(G, head, i) == 1 && !visitado[i]){
                visitado[i] = 1;
                printf("%d ", i);
                enfileira(f, i);
            }
        }
    }
    printf("\n");
    free(visitado);
    libera_fila(f);
}

//Menor caminho é calculado com base no peso M (parametro)
Aresta *dijkstra(Grafo *G, int V, char M, int **A){
    if(G == NULL || V < 0 || V >= G->qt_vertices)
        return NULL;
    if(M != 'c' && M != 'd' && M != 'z' && M != 't')
        return NULL;

    (*A) = (int *)malloc(G->qt_vertices * sizeof(int));
    int *S = (int *)calloc(G->qt_vertices, sizeof(int));
    Aresta *D = (Aresta *)malloc(G->qt_vertices * sizeof(Aresta));
    if((*A) == NULL || S == NULL || D == NULL)
        return NULL;
    int i;
    for(i = 0; i < G->qt_vertices; i++){
        (*A)[i] = -1;
        D[i].c = INT_MAX;
        D[i].d = INT_MAX;
        D[i].z = INT_MAX;
        D[i].t = INT_MAX;
    }

    S[V] = 1;
    D[V].c = 0;
    D[V].d = 0;
    D[V].z = 0;
    D[V].t = 0;

    dijkstra_aux(G, V, M, S, D, (*A));

    free(S);
    return D;
}

void dijkstra_aux(Grafo *G, int V, char M, int *S, Aresta *D, int *A){
    int i, j, k, dnovo, vk = V, menor;
    switch(M){
        case 'c':
            for(i = 0; i < G->qt_vertices; i++){
                if(G->aresta[V][i].c != 0 && S[i] == 0){
                    A[i] = V;
                    D[i].c = G->aresta[V][i].c;
                    D[i].d = G->aresta[V][i].d;
                    D[i].z = G->aresta[V][i].z;
                    D[i].t = G->aresta[V][i].t;
                }
            }

            for(k = 2; k <= G->qt_vertices; k++){
                menor = INT_MAX;
                for(i = 0; i < G->qt_vertices; i++){
                    if(D[i].c < menor && S[i] == 0){
                        menor = D[i].c;
                        vk = i;
                    }
                }
                S[vk] = 1;
                for(j = 0; j < G->qt_vertices; j++){
                    if(S[j] == 0 && G->aresta[vk][j].c != 0){
                        dnovo = D[vk].c + G->aresta[vk][j].c;
                        if(dnovo < D[j].c){
                            A[j] = vk;
                            D[j].c = dnovo;
                            D[j].d = D[vk].d + G->aresta[vk][j].d;
                            D[j].z = D[vk].z + G->aresta[vk][j].z;
                            D[j].t = D[vk].t + G->aresta[vk][j].t;
                         }
                    }
                }
            }
        break;
        case 'd':
            for(i = 0; i < G->qt_vertices; i++){
                if(G->aresta[V][i].d != 0 && S[i] == 0){
                    A[i] = V;
                    D[i].d = G->aresta[V][i].d;
                    D[i].c = G->aresta[V][i].c;
                    D[i].z = G->aresta[V][i].z;
                    D[i].t = G->aresta[V][i].t;
                }
            }

            for(k = 2; k <= G->qt_vertices; k++){
                menor = INT_MAX;
                for(i = 0; i < G->qt_vertices; i++){
                    if(D[i].d < menor && S[i] == 0){
                        menor = D[i].d;
                        vk = i;
                    }
                }
                S[vk] = 1;
                for(j = 0; j < G->qt_vertices; j++){
                    if(S[j] == 0 && G->aresta[vk][j].d != 0){
                        dnovo = D[vk].d + G->aresta[vk][j].d;
                        if(dnovo < D[j].d){
                            A[j] = vk;
                            D[j].d = dnovo;
                            D[j].c = D[vk].c + G->aresta[vk][j].c;
                            D[j].z = D[vk].z + G->aresta[vk][j].z;
                            D[j].t = D[vk].t + G->aresta[vk][j].t;
                        }
                    }
                }
            }
            break;
        case 'z':
            for(i = 0; i < G->qt_vertices; i++){
                if(G->aresta[V][i].z != 0 && S[i] == 0){
                    A[i] = V;
                    D[i].z = G->aresta[V][i].z;
                    D[i].c = G->aresta[V][i].c;
                    D[i].d = G->aresta[V][i].d;
                    D[i].t = G->aresta[V][i].t;
                }
            }

            for(k = 2; k <= G->qt_vertices; k++){
                menor = INT_MAX;
                for(i = 0; i < G->qt_vertices; i++){
                    if(D[i].z < menor && S[i] == 0){
                        menor = D[i].z;
                        vk = i;
                    }
                }
                S[vk] = 1;
                for(j = 0; j < G->qt_vertices; j++){
                    if(S[j] == 0 && G->aresta[vk][j].z != 0){
                        dnovo = D[vk].z + G->aresta[vk][j].z;
                        if(dnovo < D[j].z){
                            A[j] = vk;
                            D[j].z = dnovo;
                            D[j].c = D[vk].c + G->aresta[vk][j].c;
                            D[j].d = D[vk].d + G->aresta[vk][j].d;
                            D[j].t = D[vk].t + G->aresta[vk][j].t;
                        }
                    }
                }
            }
        break;
        case 't':
            for(i = 0; i < G->qt_vertices; i++){
                if(G->aresta[V][i].t != 0 && S[i] == 0){
                    A[i] = V;
                    D[i].t = G->aresta[V][i].t;
                    D[i].c = G->aresta[V][i].c;
                    D[i].d = G->aresta[V][i].d;
                    D[i].z = G->aresta[V][i].z;
                }
            }

            for(k = 2; k <= G->qt_vertices; k++){
                menor = INT_MAX;
                for(i = 0; i < G->qt_vertices; i++){
                    if(D[i].t < menor && S[i] == 0){
                        menor = D[i].t;
                        vk = i;
                    }
                }
                S[vk] = 1;
                for(j = 0; j < G->qt_vertices; j++){
                    if(S[j] == 0 && G->aresta[vk][j].t != 0){
                        dnovo = D[vk].t + G->aresta[vk][j].t;
                        if(dnovo < D[j].t){
                            A[j] = vk;
                            D[j].t = dnovo;
                            D[j].c = D[vk].c + G->aresta[vk][j].c;
                            D[j].d = D[vk].d + G->aresta[vk][j].d;
                            D[j].z = D[vk].z + G->aresta[vk][j].z;
                        }
                    }
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
//Recebe grafo, origem, vetor de receptores, tamanho do vetor de receptores e peso-referência
void arvores_multicast(Grafo *G, int V, char M, int tam, int *R, int n){
    int *A, i;
    int custo, D_max;
    double alfa_max;
    Aresta *D;
    D = dijkstra(G, V, M, &A);
    for(i = 0; i < n; i ++){ // Caminho entre origem e receptor 'i' e calculo das metricas
        printf("Menor caminho entre %d e %d, com base em %c(e):\n", V, R[i], M);
        mostra_caminho(V, R[i], A);
        custo = D[R[i]].c;
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

int max_delay(Aresta *D, int *R, int n){
    int i, max = 0;
    for(i = 0; i < n; i++){
        if(D[R[i]].d > max)
            max = D[R[i]].d;
    }
    return max;
}

double max_enlace(Aresta *D, int *R, int n, int tam){
    int i;
    double enlace = 0, max = 0;
    for(i = 0; i < n; i++){
        enlace = (D[R[i]].t + tam) / D[R[i]].z;
        if(enlace > max)
            max = enlace;
    }
    return max;
}

void mostra_grafo(Grafo *G){
    if(G == NULL)
        printf("Grafo inexistente.\n");
    else if(G->qt_arestas == 0)
        printf("Grafo vazio.\n");
    else{
        int i;
        for(i = 0; i < G->qt_vertices; i++){
            printf("Vertice %d:\n", i);
            mostra_adjacentes(G, i);
        }
    }
}

void libera_grafo(Grafo **G){
    int i;
    for(i = 0; i < (*G)->qt_vertices; i++)
        free((*G)->aresta[i]);
    free((*G)->aresta);
    free((*G)->grau);
    free((*G));
    (*G) = NULL;
}
