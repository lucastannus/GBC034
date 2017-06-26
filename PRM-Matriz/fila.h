#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct fila Fila;
typedef struct no No;

Fila *cria_fila();
int tamanho_fila(Fila *f);
int fila_vazia(Fila *f);
int cabeca(Fila *f);
int enfileira(Fila *f, int data);
int desenfileira(Fila *f);
void mostra_fila(Fila *f);
void libera_fila(Fila *f);

#endif // FILA_H_INCLUDED
