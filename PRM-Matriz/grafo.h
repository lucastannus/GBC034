#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;
typedef struct aresta Aresta;

Grafo *cria_grafo(int n_vertices);
int numVertices(Grafo *G);
int grauVertice(Grafo *G, int V);
int verifica_aresta(Grafo *G, int V1, int V2);
int insere_aresta(Grafo *G, int V1, int V2, int C, int D, int Z, int T);
int remove_aresta(Grafo *G, int V1, int V2);
int consulta_aresta(Grafo *G, int V1, int V2, char M, int *P);
Aresta *dijkstra(Grafo *G, int V, char M, int **A);
void arvores_multicast(Grafo *G, int V, char M, int tam, int *R, int n);
double max_enlace(Aresta *D, int *R, int n, int tam);
void mostra_grafo(Grafo *G);
void libera_grafo(Grafo **G);

#endif // GRAFO_H_INCLUDED
