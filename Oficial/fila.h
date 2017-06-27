#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct fila Fila;
Fila* cria_fila();
int fila_vazia(Fila *fila);
int insere_fila(Fila *fila, int data);
int remove_fila(Fila *fila, int *data);
void libera_fila(Fila *fila);
void imprime_fila(Fila *fila);

#endif // FILA_H_INCLUDED
