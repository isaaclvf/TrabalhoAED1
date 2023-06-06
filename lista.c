#include "lista.h"

#include <stdbool.h>
#include <stdlib.h>

typedef struct no {
  void *dados;
  struct no *prox;
  struct no *anterior;
} No;

typedef struct lista {
  No *inicio;
  No *fim;
  int tam;
} Lista;

// criaNo
No *criaNo(void *elemento) {
  No *no = malloc(sizeof(No));
  if (no == NULL) return NULL;

  no->dados = elemento;
  no->anterior = NULL;
  no->prox = NULL;

  return no;
}

// criaLista
Lista *criaLista() {
  Lista *li = malloc(sizeof(Lista));
  if (li == NULL) return NULL;

  li->inicio = NULL;
  li->fim = NULL;
  li->tam = 0;

  return li;
}

bool vazia(Lista *lista) { return lista->tam == 0; }

// inserirInicio
void inserirInicio(Lista *lista, void *elemento) {
  No *novoNo = criaNo(elemento);

  if (vazia(lista)) {
    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->tam = 1;
    return;
  }

  lista->inicio->anterior = novoNo;
  novoNo->prox = lista->inicio;
  lista->inicio = novoNo;
  lista->tam++;
}

// removerInicio
void *removerInicio(Lista *lista) {
  void *elementoRemovido = NULL;

  if (vazia(lista)) return elementoRemovido;

  if (lista->tam == 1) {
    elementoRemovido = lista->inicio->dados;
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return elementoRemovido;
  }

  No *noRemovido = lista->inicio;
  lista->inicio = lista->inicio->prox;
  lista->inicio->anterior = NULL;
  lista->tam--;

  elementoRemovido = noRemovido->dados;
  free(noRemovido);

  return elementoRemovido;
}

// inserirFim
void inserirFim(Lista *lista, void *elemento) {
  No *novoNo = criaNo(elemento);

  if (vazia(lista)) {
    lista->inicio = novoNo;
    lista->fim = novoNo;
    lista->tam = 1;
    return;
  }

  lista->fim->prox = novoNo;
  novoNo->anterior = lista->fim;
  lista->fim = novoNo;
  lista->tam++;
}

// removerFim
void *removerFim(Lista *lista) {
  void *elementoRemovido = NULL;

  if (vazia(lista)) return elementoRemovido;

  if (lista->tam == 1) {
    elementoRemovido = lista->fim->dados;
    lista->inicio = NULL;
    lista->fim = NULL;
    lista->tam = 0;
    return elementoRemovido;
  }

  No *noRemovido = lista->fim;
  lista->fim = lista->fim->anterior;
  lista->fim->prox = NULL;
  lista->tam--;

  elementoRemovido = noRemovido->dados;
  free(noRemovido);

  return elementoRemovido;
}

// excluirLista
void excluirLista(Lista *lista) {
  if (lista == NULL) {
    return;
  }
  No *noRemove;
  while (lista->inicio != NULL) {
    noRemove = lista->inicio;
    lista->inicio = lista->inicio->prox;
    free(noRemove);
  }
  free(lista);
  return;
}

// Ordenação

void swap(No *a, No *b) {
  void *t = a->dados;
  a->dados = b->dados;
  b->dados = t;
}

No *particiona(No *inicio, No *fim, int (*compare)(void *, void *)) {
  void *pivo = fim->dados;
  No *i = inicio->anterior;

  for (No *j = inicio; j != fim; j = j->prox) {
    if (compare(j->dados, pivo) <= 0) {
      i = (i == NULL) ? inicio : i->prox;
      swap(i, j);
    }
  }

  i = (i == NULL) ? inicio : i->prox;
  swap(i, fim);
  return i;
}

void quicksort(No *inicio, No *fim, int (*compare)(void *, void *)) {
  if (fim != NULL && inicio != fim && inicio != fim->prox) {
    No *pivo = particiona(inicio, fim, compare);
    quicksort(inicio, pivo->anterior, compare);
    quicksort(pivo->prox, fim, compare);
  }
}
