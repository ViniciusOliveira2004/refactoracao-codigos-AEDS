#include <stdlib.h> 
#include <stdio.h> 
#include <sys/time.h>

#ifndef ARVORE_PATRICIA_H
#define ARVORE_PATRICIA_H

#define TAMANHO_CHAVE 8   // Define o número de bits máximo que a chave pode conter
typedef unsigned char Chave; // Valor que será armazenado nos nós externos da árvore
typedef unsigned char Indice; // Índice dos nós internos da árvore
typedef unsigned char Bit; // Bit 0 ou 1 (Utilizado na função de coletar um bit i de uma chave)

// Tipos de nós da árvore
typedef enum {
  Interno, Externo
} Tipo;

// Representa a árvore como um ponteiro para um nó
typedef struct No* Arvore;

// Estrutura de um nó da árvore
typedef struct No {
  Tipo tipo;
  union {
    // Caso o nó seja interno, ele terá um índice e ponteiros para os nós esquerdo e direito
    struct {
      Indice indice;
      Arvore esq, dir;
    } noInterno ;

    // Caso o nó seja externo, ele terá uma chave que será armazenada
    Chave chave;
  } no;
} No;

/** Retorna o bit `indice` da chave `chave` a partir da esquerda
 * @param indice Indice do bit que será retornado
 * @param chave Chave onde seja coletado o bit de número `indice`
 * @returns Retorna o bit `indice` da chave `chave` */
Bit coletaBit(Indice indice, Chave chave);

/** Verifica se o nó `no` é externo
 * @param no Nó que será verificado
 * @returns 1 se o nó for externo, e 0 se for interno */
short noEExterno(Arvore no);

/** Cria um nó interno, alocando memória para ele e preenchendo seus campos.
 * @param indice O índice do bit que será usado para a decisão no nó interno.
 * @param esq Um ponteiro para a subárvore esquerda do nó interno.
 * @param dir Um ponteiro para a subárvore direita do nó interno.
 * @returns Um ponteiro para o nó interno recém-criado. */
Arvore criaNoInterno(int indice, Arvore *esq,  Arvore *dir);

/** Cria um nó externo, alocando memória para ele e preenchendo seus campos.    
 * @param chave Chave que será armazenada no nó.
 * @returns Um ponteiro para o nó externo recém-criado. */
Arvore criaNoExterno(Chave chave);

/** Verifica se uma chave existe na árvore, e exibe o resultado no terminal.
 * @param chave Chave que será pesquisada.
 * @param arvore Árvore onde a chave será pesquisada. */
void pesquisaChave(Chave chave, Arvore arvore);

/** Função auxiliar para inserir uma chave na árvore, criando nós internos e externos conforme necessário.
 * @param chave Chave que será inserida.
 * @param arvore Árvore onde a chave será inserida.
 * @param indice Índice do bit que será usado para a decisão no nó interno.
 * @returns Um ponteiro para a árvore atualizada após a inserção da chave. */
Arvore insereChaveEntre(Chave chave, Arvore *arvore, int indice);

/** Insere uma chave na árvore, criando nós internos e externos conforme necessário.
 * @param chave Chave que será inserida.
 * @param arvore Árvore onde a chave será inserida.
 * @returns Um ponteiro para a árvore atualizada após a inserção da chave. */
Arvore insereChave(Chave chave, Arvore *arvore);

#endif