#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;
typedef struct aresta ArestaLista;
Grafo *cria_grafo(int qnt_vertices);
int verifica_aresta(Grafo *grafo, int vO, int vD);
int insere_aresta(Grafo *grafo, int vO, int vD, int capacidade, int custo, int delay, int trafego);
int remove_aresta(Grafo *grafo, int vO, int vD);
int consulta_aresta(Grafo *grafo, int vO, int vD, int peso);
void libera_grafo(Grafo **grafo);
int num_vertices(Grafo *grafo);
int grau_vertice(Grafo *grafo, int v);
int eh_adjacente(Grafo *grafo, int v1, int v2);
void mostra_adjacentes(Grafo *grafo, int v);
void mostra_grafo(Grafo *grafo);
void dfs(Grafo *grafo, int vO);
void busca_largura(Grafo *grafo, int v);

#endif // GRAFO_H_INCLUDED
