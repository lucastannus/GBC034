#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila{
    int size;
    No *head;
};

struct no{
    int data;
    No *prox;
};

Fila *cria_fila(){
    Fila *f = (Fila *)malloc(sizeof(Fila));
    if(f == NULL)
        return NULL;

    f->head = NULL;
    f->size = 0;
    return f;
}

int fila_vazia(Fila *f){
    if(f == NULL)
        return -1;
    if(f->size == 0)
        return 1;
    else
        return 0;
}

int tamanho_fila(Fila *f){
    return f->size;
}

int cabeca(Fila *f){
    if(f == NULL)
        printf("Erro\n");
    else if(fila_vazia(f))
        printf("Fila vazia\n");
    else
        return f->head->data;
}

int enfileira(Fila *f, int data){
    if(f == NULL)
        return -1;

    No *aux = f->head;
    No *novo = (No *)malloc(sizeof(No));
    if(novo == NULL)
        return 0;
    novo->data = data;
    novo->prox = NULL;
    if(fila_vazia(f)){
        f->head = novo;
        f->size++;
        return 1;
    }
    else{
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
        f->size++;
        return 1;
    }
}

int desenfileira(Fila *f){
    if(f == NULL)
        return -1;
    if(fila_vazia(f))
        return 0;

    No *aux = f->head;
    f->head = f->head->prox;
    free(aux);
    f->size--;

    return 1;
}

void mostra_fila(Fila *f){
    if(f == NULL){
        printf("Fila invalida\n");
        return;
    }
    if(fila_vazia(f)){
        printf("Fila vazia\n");
        return;
    }
    No *aux = f->head;

    printf("CABECA: ");
    while(aux != NULL){
        printf("%d ", aux->data);
        aux = aux->prox;
    }
    printf(":CAUDA\n");
}

void libera_fila(Fila *f){
    while(f->head != NULL)
        desenfileira(f);
    free(f);
}
