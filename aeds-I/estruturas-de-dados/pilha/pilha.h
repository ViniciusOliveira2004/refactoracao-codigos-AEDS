#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifndef PILHA_H
#define PILHA_H

#define MAXIMO 10 // Número máximo de items a serem incluídos na pilha

// Tipo de dadoS para a chave
typedef int Chave; 

// Estrutura de um item da pilha
typedef struct {
  Chave chave;
} Item;

// Ponteiro para uma célula da PILHA
typedef struct Celula *Apontador;

// Estrutura de uma célula da pilha
typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

// Estrutura de uma pilha, contendo ponteiros para o topo e o fundo da pilha
typedef struct {
  Apontador fundo, topo;
  int tamanho;
} Pilha;

/** Inicializa a Pilha como vazia, alocando memória para a primeira célula, 
 * configurando os ponteiros adequadamente e definindo o tamanho como 0.
 * @param pilha Ponteiro para a pilha que será inicializada */
void inicializaPilha(Pilha *pilha);

/** Verifica se a pilha está vazia.
 * @param pilha Estrutura da pilha a ser verificada
 * @return 1 se a pilha estiver vazia, 0 caso contrário */
int pilhaEVazia(Pilha pilha);

/** Empilha um item na pilha.
 * @param item Item a ser empilhado
 * @param pilha Ponteiro para a pilha onde o item será empilhado */
void empilhaItem(Item item, Pilha *pilha);

/** Desempilha um item da pilha.
 * @param item Ponteiro para o item que será desempilhado
 * @param pilha Ponteiro para a pilha de onde o item será desempilhado */
void desempilhaItem(Item *item, Pilha *pilha);

#endif