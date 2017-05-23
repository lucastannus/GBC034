#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;

Grafo *cria_grafo(int n_vertices);
int insere_aresta(Grafo *G, int V1, int V2, int P);
int verifica_aresta(Grafo *G, int V1, int V2);
int remove_aresta(Grafo *G, int V1, int V2);
int consulta_aresta(Grafo *G, int V1, int V2, int *P);
void mostra_adjacentes(Grafo *G, int V);
void mostra_grafo(Grafo *G);
void libera_grafo(Grafo **G);

#endif // GRAFO_H_INCLUDED
