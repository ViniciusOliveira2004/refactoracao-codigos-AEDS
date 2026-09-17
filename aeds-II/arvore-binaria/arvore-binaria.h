#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#ifndef ARVORE_BINARIA_H
#define ARVORE_BINARIA_H

#define TAMANHO_VETOR 10 // Tanho do vetor utilizado nos testes da árvore binária

// Tipo de dados para a chave
typedef long Chave;

// Tipo de dados para um registro na árvore
typedef struct Registro {
  Chave chave;
} Registro;

// Tipo de dados para um ponteiro para um nó da árvore
typedef struct No * Apontador;

// Tipo de dados para um nó da árvore
typedef struct No {
  Registro registro;
  Apontador esq, dir;
} No;

// Tipo de dados para a árvore binária
typedef Apontador Arvore;

/** Inicializa uma árvore, atribuindo NULL a ela.
 *  @param arvore A árvore a ser inicializada */
void inicializaArvore(Arvore *arvore);

/** Busca um registro na árvore e copia o valor encontrado para o ponteiro informado.
 *  Se a chave não estiver presente, imprime uma mensagem de erro.
 *  @param registro Ponteiro para o registro que será pesquisado e que receberá o valor encontrado
 *  @param arvore Ponteiro para a raiz da árvore na qual a pesquisa será realizada */
void pesquisaRegistro(Registro *registro, Arvore *arvore);

/** Insere um registro na árvore.
 *  @param registro O registro a ser inserido
 *  @param arvore A árvore na qual o registro será inserido */
void insereRegistro(Registro registro, Arvore *arvore);

/** Remove o maior nó da subárvore esquerda, copia o registro desse predecessor para o nó informado
 *  e libera o nó predecessor da subárvore.
 *  @param noRemovido Ponteiro para o nó que receberá o registro do predecessor
 *  @param arvore Ponteiro para a raiz da subárvore esquerda */
void removePredecessor(Apontador noRemovido, Arvore *arvore);

/** Retira um registro da árvore.
 *  @param registro O registro a ser retirado
 *  @param arvore A árvore da qual o registro será retirado */
void retiraRegistro(Registro registro, Arvore *arvore);

/** Verifica a integridade da árvore.
 *  @param arvore A árvore a ser verificada */
void verificaArvore(Arvore arvore);

/** Gera um número aleatório entre 0 e 1.
 *  @return Um número aleatório do tipo double */
double gerarNumeroAleatorio();

/** Gera uma permutação aleatória do vetor.
 *  @param vetor O vetor a ser permutado
 *  @param tamanho O número de elementos no vetor */
void gerarPermutacao(Chave vetor[], int tamanho);

#endif