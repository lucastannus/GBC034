#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

int main()
{
    Grafo *g = cria_grafo(15);
    int R[4];

    R[0] = 1;
    R[1] = 8;
    R[2] = 12;
    R[3] = 13;

    insere_aresta(g, 0, 1, 1, 1, 1, 1);
    insere_aresta(g, 0, 2, 5, 5, 5, 5);
    insere_aresta(g, 0, 3, 10, 10, 10, 10);
    insere_aresta(g, 1, 4, 3, 3, 3, 3);
    insere_aresta(g, 2, 5, 1, 1, 1, 1);
    insere_aresta(g, 2, 6, 7, 7, 7, 7);
    insere_aresta(g, 3, 7, 3, 3, 3, 3);
    insere_aresta(g, 3, 8, 1, 1, 1, 1);
    insere_aresta(g, 4, 9, 8, 8, 8, 8);
    insere_aresta(g, 5, 9, 5, 5, 5, 5);
    insere_aresta(g, 6, 10, 15, 15, 15, 15);
    insere_aresta(g, 7, 10, 2, 2, 2, 2);
    insere_aresta(g, 8, 10, 12, 12, 12, 12);
    insere_aresta(g, 9, 11, 9, 9, 9, 9);
    insere_aresta(g, 9, 12, 3, 3, 3, 3);
    insere_aresta(g, 10, 12, 21, 21, 21, 21);
    insere_aresta(g, 11, 13, 4, 4, 4, 4);
    insere_aresta(g, 12, 14, 10, 10, 10, 10);
    insere_aresta(g, 13, 14, 1, 1, 1, 1);

    arvores_multicast(g, 0, R, 4, 'd', 10);

    busca_largura(g, 0);

    dfs(g, 0);

    libera_grafo(&g);
    return 0;
}
