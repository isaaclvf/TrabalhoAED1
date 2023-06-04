#include "lista.c"

// criar lista
Lista *criaLista();
// função de adicinar
void inserirInicio();
void inserirFim();
// função de remover
void *removerInicio(Lista *lista);
void *removerFim(Lista *lista);
// função de busca
Lista *buscaLista(Lista *lista);
// função de tamanho
// função de imprimir lista
void imprimirLista(Lista *lista);
// excluir lista
void excluirLista(Lista *lista);
void swap(No *a, No *b);
No *particiona(No *inicio, No *fim, int (*compare)(void *, void *));
void quicksort(No *inicio, No *fim, int (*compare)(void *, void *));