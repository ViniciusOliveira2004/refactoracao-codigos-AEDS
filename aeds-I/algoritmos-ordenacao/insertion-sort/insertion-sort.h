#include <stdio.h>
#include <stdlib.h>

#ifndef SELECT_SORT_H
#define SELECT_SORT_H

#define TAMANHO_VETOR 20 // Tamanho do vetor a ser ordenado

// Tipo de dados para a chave
typedef long Chave;

// Tipo de dados para um item do vetor
typedef struct Item {
  Chave chave;
} Item;

// Tipo de dados para um indice do vetor
typedef int Indice;

// Tipo de dados para o vetor
typedef Item Vetor[TAMANHO_VETOR];

/** Ordena o vetor utilizando o algoritmo de inserção.
 *  @param vetor O vetor a ser ordenado
 *  @param tamanho O número de elementos no vetor */
void insertionSort(Vetor vetor, Indice tamanho);

/** Imprime os elementos do vetor.
 *  @param vetor O vetor a ser impresso
 *  @param tamanho O número de elementos no vetor */
void imprimirVetor(Vetor vetor, Indice tamanho);

/** Copia os valores de um vetor para outro.
 *  @param fonte O vetor de origem
 *  @param destino O vetor de destino
 *  @param tamanho O número de elementos a serem copiados */
void copiarValores(Vetor fonte, Vetor destino, Indice tamanho);

/** Testa se o vetor está ordenado, exibindo uma mensagem indicando o resultado.
 *  @param vetor O vetor a ser testado
 *  @param tamanho O número de elementos no vetor */
void testarOrdenacao(Vetor vetor, Indice tamanho);

/** Gera um número aleatório entre 0 e 1.
 *  @return Um número aleatório do tipo double */
double gerarNumeroAleatorio();

// Trocou int por Indice e no j também
/** Gera uma permutação aleatória do vetor.
 *  @param vetor O vetor a ser permutado
 *  @param tamanho O número de elementos no vetor */
void gerarPermutacao(Vetor vetor, Indice tamanho);

#endif