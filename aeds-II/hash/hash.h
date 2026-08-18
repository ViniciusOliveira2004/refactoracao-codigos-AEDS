#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

#ifndef HASH_H
#define HASH_H

#define TAMANHO_HASH 7 // Tamanho da tabela hash
#define TAMANHO_CHAVE 7 // Tamanho máximo da chave
#define TAMANHO_ALFABETO 256 // Número de caracteres distintos possíveis (256 = ASCII completo)

typedef char Chave[TAMANHO_CHAVE]; // Tipo de dado para a chave
typedef unsigned int Pesos[TAMANHO_CHAVE][TAMANHO_ALFABETO]; // Tipo de dado para os pesos, que é uma matriz de inteiros
typedef unsigned int Indice; // Tipo de dado para o índice da tabela hash

// Tipo de dado para o índice da tabela hash
typedef struct Item {
  Chave chave;
} Item;

// Estrutura de uma célula da lista encadeada
typedef struct Celula* Apontador;

// Estrutura de uma célula da lista encadeada
typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

// Estrutura de uma lista encadeada
typedef struct Lista {
  Celula *primeiro, *ultimo;
} Lista;

// Estrutura da tabela hash, que é um array de listas encadeadas
typedef Lista Hash[TAMANHO_HASH];

/** Verifica se a lista `lista` está vazia, comparando o ponteiro do primeiro elemento com o ponteiro do último elemento.
 * @param lista Lista que será verificada
 * @returns 1 se a lista estiver vazia, 0 caso contrário */
short listaEVazia(Lista lista);

/** Inicializa uma lista da tabela Hash, alocando memória para o primeiro elemento 
 *  e definindo o último elemento como o primeiro.
 * @param lista Lista que será inicializada */
void inicializaLista(Lista *lista);

/** Inicializa a tabela hash, criando uma lista encadeada para cada posição.
 * @param tabela Tabela hash a ser inicializada */
void inicializaHash(Hash tabela);

/** Calcula o índice da tabela hash para uma dada chave usando os pesos gerados.
 * @param chave Chave para a qual calcular o índice
 * @param pesos Tabela de pesos
 * @return Índice da tabela hash */
Indice hash(Chave chave, Pesos pesos);

/** Pesquisa por uma chave na tabela hash.
 * @param chave Chave a ser pesquisada
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash
 * @return Apontador para o item anterior da lista, ou `NULL` se não encontrado */
Apontador pesquisaChave(Chave chave, Pesos pesos, Hash tabela);

/** Adiciona um item `item` ao final da lista `lista`, alocando memória para um novo elemento 
 * e atualizando o ponteiro do último elemento.
 * @param item Item que será adicionado
 * @param lista Lista à qual o item será adicionado */
void insereItemLista(Item item, Lista *lista);

/** Insere um item na tabela hash.
 * @param item Item a ser inserido
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash */
void insereItem(Item item, Pesos pesos, Hash tabela);

/** Retira um item da lista `lista`, removendo o elemento seguinte ao apontado por `anterior` e 
 * atualizando os ponteiros da lista.
 * @param anterior Ponteiro para o nó anterior ao que será removido
 * @param lista Lista da qual o item será retirado
 * @param item Ponteiro para onde o item removido será copiado */
void retiraItemLista(Apontador anterior, Lista *lista, Item *item);

/** Retira um item da tabela hash.
 * @param item Item a ser retirado
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash */
void retiraItem(Item item, Pesos pesos, Hash tabela);

/** Gera uma tabela de valores aleatórios chamada `pesos`, que será usada pela função de hash `hash()` 
 * para calcular em qual posição da tabela cada chave deve entrar. 
 * @param pesos Tabela de pesos que será preenchida com valores aleatórios */
void geraPesos(Pesos pesos);

/** Imprime a lista encadeada.
 * @param lista Lista a ser impressa */
void imprimeLista(Lista lista);

/** Imprime a tabela hash.
 * @param tabela Tabela hash a ser impressa */
void imprimeTabela(Hash tabela);

/** Lê uma palavra do teclado.
 * @param string Ponteiro para a string onde a palavra será armazenada
 * @param tamanho Tamanho máximo da string */
void lerPalavra(char *string, int tamanho);

#endif

