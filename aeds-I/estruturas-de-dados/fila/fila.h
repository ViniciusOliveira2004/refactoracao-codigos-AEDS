#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>

#ifndef FILA_H
#define FILA_H

#define MAXIMO 10 // Número máximo de items a serem incluídos na fila

// Ponteiro para uma célula da fila
typedef struct Celula *Apontador;

// Tipo de dado para a chave
typedef int Chave;

// Estrutura de um item da fila
typedef struct Item {
  Chave chave;
} Item;

// Estrutura de uma célula da fila
typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

// Estrutura de uma fila, contendo ponteiros para o início e o final da fila
typedef struct Fila {
  Apontador inicio, final;
} Fila;

/** Inicializa a Fila como vazia, alocando memória para a primeira célula e configurando os ponteiros adequadamente.
 *  @param fila Ponteiro para a fila que será inicializada */
void inicializaFila(Fila *fila);

/** Verifica se a fila está vazia.
 *  @param fila A fila a ser verificada
 *  @return 1 se a fila estiver vazia, 0 caso contrário */
int filaEVazia(Fila fila);

/** Adiciona um item no final da fila
 * @param item item que será inserido
 * @param fila Ponteiro para a fila onde o item será inserido */
void enfileiraItem(Item item, Fila *fila);

/** Remove um item do início da fila
 * @param item Ponteiro para onde o item removido será copiado
 * @param fila Ponteiro para a fila da qual o item será removido */
void desenfileiraItem(Item *item, Fila *fila);

/** Imprime a fila no terminal
 * @param fila Fila que será imprimida */
void imprimeFila(Fila fila);

#endif