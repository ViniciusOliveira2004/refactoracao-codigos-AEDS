#include <stdlib.h> 
#include <stdio.h> 
#include <sys/time.h>

#define TAMANHO_CHAVE 8   /* Define o número de bits máximo que a chave pode conter */

typedef unsigned char Chave; /* Valor que será armazenado nos nós externos da árvore */
typedef unsigned char Indice; /* Índice dos nós internos da árvore */
typedef unsigned char Bit; /* Bit 0 ou 1 (Utilizado na função de coletar um bit i de uma chave) */

typedef enum {
  Interno, Externo
} Tipo;

typedef struct No* Arvore;

typedef struct No {
  Tipo tipo;
  union {
    struct {
      Indice indice;
      Arvore esq, dir;
    } noInterno ;
    Chave chave;
  } no;
} No;

/**
Retorna o bit "indice" da chave "chave" a partir da esquerda
  @param indice Indice do bit que será retornado
  @param chave Chave onde seja coletado o bit de número "indice"
  @returns Retorna o bit "indice" da chave "chave"
*/
Bit coletaBit(Indice indice, Chave chave) {
  int bit;
  if (indice == 0) {
    return 0;
  } else { 
    bit = chave;
    for (int j = 1; j <= TAMANHO_CHAVE - indice; j++) {
      bit /= 2;
    }
    return bit & 1;
  }
} 

/**
Verifica se o nó "no" é externo
  @param no Nó que será verificado
  @returns 1 se o nó for externo, e 0 se for interno
*/
short noEExterno(Arvore no) {
  return no->tipo == Externo;
}

/**
Cria um nó interno, alocando memória para ele e preenchendo seus campos.    
  @param indice O índice do bit que será usado para a decisão no nó interno.
  @param esq Um ponteiro para a subárvore esquerda do nó interno.
  @param dir Um ponteiro para a subárvore direita do nó interno.
  @returns Um ponteiro para o nó interno recém-criado.
*/
Arvore criaNoInterno(int indice, Arvore *esq,  Arvore *dir) { 
  Arvore arvore;
  arvore = (Arvore)malloc(sizeof(No));
  arvore->tipo = Interno; 
  arvore->no.noInterno.esq = *esq;
  arvore->no.noInterno.dir = *dir;
  arvore->no.noInterno.indice = indice; 
  return arvore;
} 

/**
Cria um nó externo, alocando memória para ele e preenchendo seus campos.    
  @param chave Chave que será armazenada no nó.
  @returns Um ponteiro para o nó externo recém-criado.
*/
Arvore criaNoExterno(Chave chave){ 
  Arvore arvore;
  arvore = (Arvore) malloc(sizeof(No));
  arvore->tipo = Externo;
  arvore->no.chave = chave; 
  return arvore;
}  

/**
Verifica se uma chave existe na árvore, e exibe o resultado no terminal.
  @param chave Chave que será pesquisada.
  @param arvore Árvore onde a chave será pesquisada.
*/
void pesquisaChave(Chave chave, Arvore arvore) { 
  if (noEExterno(arvore)) { 
    if (chave == arvore->no.chave) {
      printf("Elemento encontrado\n");
    } else {
      printf("Elemento nao encontrado\n");
    }
    return;
  }

  if (coletaBit(arvore->no.noInterno.indice, chave) == 0) {
    pesquisaChave(chave, arvore->no.noInterno.esq);
  } else {
    pesquisaChave(chave, arvore->no.noInterno.dir);
  }
} 

/**
Função auxiliar para inserir uma chave na árvore, criando nós internos e externos conforme necessário.
  @param chave Chave que será inserida.
  @param arvore Árvore onde a chave será inserida.
  @returns Um ponteiro para a árvore atualizada após a inserção da chave.
*/
Arvore insereChaveEntre(Chave chave, Arvore *arvore, int indice) { 
  Arvore arvoreAuxiliar;
  if (noEExterno(*arvore) || indice < (*arvore)->no.noInterno.indice) { 
    /* Cria um novo nó externo */
    arvoreAuxiliar = criaNoExterno(chave);
    if (coletaBit(indice, chave) == 1) {
      return criaNoInterno(indice, arvore, &arvoreAuxiliar);
    } else {
      return criaNoInterno(indice, &arvoreAuxiliar, arvore);
    }
  } else { 
    if (coletaBit((*arvore)->no.noInterno.indice, chave) == 1) {
      (*arvore)->no.noInterno.dir = insereChaveEntre(chave, &(*arvore)->no.noInterno.dir, indice);
    } else {
      (*arvore)->no.noInterno.esq = insereChaveEntre(chave, &(*arvore)->no.noInterno.esq, indice);
    }
    return (*arvore);
  }
}

/**
Insere uma chave na árvore, criando nós internos e externos conforme necessário.
  @param chave Chave que será inserida.
  @param arvore Árvore onde a chave será inserida.
  @returns Um ponteiro para a árvore atualizada após a inserção da chave.
*/
Arvore insereChave(Chave chave, Arvore *arvore) { 
  Arvore arvoreAuxiliar;
  int i;
  if (*arvore == NULL) {
    return (criaNoExterno(chave));
  } else {
    arvoreAuxiliar = *arvore;
    while (!noEExterno(arvoreAuxiliar)) { 
      if (coletaBit(arvoreAuxiliar->no.noInterno.indice, chave) == 1) {
        arvoreAuxiliar = arvoreAuxiliar->no.noInterno.dir;
      } else {
        arvoreAuxiliar = arvoreAuxiliar->no.noInterno.esq;
      }
    }

    i = 1;
    while ((i <= TAMANHO_CHAVE) & (coletaBit(i, chave) == coletaBit(i, arvoreAuxiliar->no.chave))) {
      i++;
    }

    if (i > TAMANHO_CHAVE) { 
      printf("Erro: chave ja esta na arvore\n");  
      return (*arvore); 
    } else {
      return insereChaveEntre(chave, arvore, i);
    }
  }
}

int main(int argc, char *argv[])
{ Arvore a = NULL;
  Chave c;
  int  i, j, k, n;
  int  min = 32, max = 126;
  Chave vetor[95];
  /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
  struct timeval semente;
  gettimeofday(&semente,NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));  
  for (i = min; i <= max; i++)
  vetor[i - 32] = i;
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0)); 
      j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n; 
    }
  /* insereChave cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("Inserindo chave: %c\n", c);
      a = insereChave(c, &a);
    }
  /* Gera outra permutacao aleatoria de chaves */
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
    }
  /* pesquisaChave cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("pesquisaChavendo chave: %c\n", c);
      pesquisaChave(c, a);
    }
  return 0;
} 
