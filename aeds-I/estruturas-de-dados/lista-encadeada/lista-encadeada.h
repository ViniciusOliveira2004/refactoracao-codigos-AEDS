#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#define MAXIMO_ITEMS 10 // Define o número máximo de itens que serão inseridos na lista encadeada

typedef int Chave; // Tipo de dado para a chave

// Estrutura de um item da lista encadeada
typedef struct {
  Chave chave;
} Item;

// Ponteiro para uma célula da lista encadeada
typedef struct Celula *Apontador;

// Estrutura de uma célula da lista encadeada
typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

// Estrutura de uma lista encadeada, contendo ponteiros para o primeiro e último elementos
typedef struct {
  Apontador primeiro, ultimo;
} Lista;

/** Inicializa a lista encadeada como vazia, alocando memória para o primeiro nó e configurando os ponteiros adequadamente.
 *  @param lista Ponteiro para a lista que será inicializada */
void inicializaListaVazia(Lista *lista);

/** Verifica se a lista está vazia.
 *  @param lista A lista a ser verificada
 *  @return 1 se a lista estiver vazia, 0 caso contrário */
int listaEVazia(Lista lista);

/** Insere um item no final da lista.
 *  @param item O item a ser inserido
 *  @param lista Ponteiro para a lista onde o item será inserido */
void insereItem(Item item, Lista *lista);

/** Retira um item da lista `lista`, removendo o elemento seguinte ao apontado por `anterior` e 
 * atualizando os ponteiros da lista.
 * @param anterior Ponteiro para o nó anterior ao que será removido
 * @param lista Lista da qual o item será retirado
 * @param item Ponteiro para onde o item removido será copiado */
void retiraItem(Apontador anterior, Lista *lista, Item *item);

/** Imprime os elementos da lista.
 *  @param lista A lista a ser impressa */
void imprimeLista(Lista lista);

#endif