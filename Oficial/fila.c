#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct node{
    int data;
    struct node *prox;
};

typedef struct node Node;

struct fila{
    int size;
    Node *head;
    Node *tail;
};

Fila* cria_fila(){
    Fila *fila;

    fila = (Fila*)malloc(sizeof(Fila));
    if(fila == NULL)
        return fila;

    fila->head = NULL;
    fila->tail = NULL;
    fila->size = 0;

    return fila;
}

int fila_vazia(Fila *fila){
    if(fila->size == 0)
        return 1;
    else
        return 0;
}

int insere_fila(Fila *fila, int data){
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
        return -1;

    new_node->data = data;

    if(fila_vazia(fila)){
        fila->tail = new_node;
        fila->head = new_node;
        fila->tail->prox = NULL;
    }else{
        fila->tail->prox = new_node;
        fila->tail = new_node;
        fila->tail->prox = NULL;
    }
    fila->size++;
    return 1;
}

int remove_fila(Fila *fila, int *data){
    int *aux;

    //fila vazia
    if(fila->size == 0)
        return 0;

    (*data) = fila->head->data;

    aux = fila->head;
    fila->head = fila->head->prox;
    free(aux);

    fila->size--;

    return 1;
}

void libera_fila(Fila *fila){
    int data;

    while(!(fila_vazia(fila)))
        remove_fila(fila, &data);

    free(fila);
}

void imprime_fila(Fila *fila){
    Node *aux;

    aux = fila->head;

    while(aux != NULL){
        printf("%d ", aux->data);
        aux = aux->prox;
    }
}
