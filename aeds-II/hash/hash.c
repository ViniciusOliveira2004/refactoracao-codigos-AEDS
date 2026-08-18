#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 7
#define N 7      
#define TAMANHO_ALFABETO 256

typedef char Chave[N];
typedef unsigned int Pesos[N][TAMANHO_ALFABETO];

typedef struct Item {
  Chave chave;
} Item;

typedef unsigned int Indice;
typedef struct Celula* Apontador;

typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

typedef struct Lista {
  Celula *primeiro, *ultimo;
} Lista;

typedef Lista Hash[M];

Hash tabela;
Item elemento;
Pesos p;
Apontador apontador;

/** Inicializa uma lista da tabela Hash, alocando memória para o primeiro elemento 
 *  e definindo o último elemento como o primeiro.
 * @param lista Lista que será inicializada */
void inicializaLista(Lista *lista) {
    lista->primeiro = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro; 
    lista->primeiro->prox = NULL;
}  

/** Verifica se a lista `lista` está vazia, comparando o ponteiro do primeiro elemento com o ponteiro do último elemento.
 * @param lista Lista que será verificada
 * @returns 1 se a lista estiver vazia, 0 caso contrário */
short listaEVazia(Lista lista) { 
    return lista.primeiro == lista.ultimo; 
}

/** Adiciona um item `item` ao final da lista `lista`, alocando memória para um novo elemento 
 * e atualizando o ponteiro do último elemento.
 * @param item Item que será adicionado
 * @param lista Lista à qual o item será adicionado */
void insereItemLista(Item item, Lista *lista) { 
    lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox; 
    lista->ultimo->item = item;
    lista->ultimo->prox = NULL;
}  

/** Retira um item da lista `lista`, removendo o elemento seguinte ao apontado por `anterior` e 
 * atualizando os ponteiros da lista.
 * @param anterior Ponteiro para o nó anterior ao que será removido
 * @param lista Lista da qual o item será retirado
 * @param item Ponteiro para onde o item removido será copiado */
void retiraItemLista(Apontador anterior, Lista *lista, Item *item) {
    Apontador noRemovido; // Ponteiro para o nó que será removido

    if (listaEVazia(*lista) || anterior == NULL || anterior->prox == NULL) { 
        printf(" Erro: Lista vazia ou posicao nao existe\n");
        return;
    }

    noRemovido = anterior->prox; 
    *item = noRemovido->item; 
    anterior->prox = noRemovido->prox;
    if (anterior->prox == NULL) {
        lista->ultimo = anterior;
    }
    free(noRemovido);
}

/*
void geraPesos(Pesos p)
{ int i;
  struct timeval semente;
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
  for (i = 0; i < n; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

Indice hash(Chave Chave, Pesos p)
{ int i; 
  unsigned int Soma = 0; 
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}
*/

/** Gera uma tabela de valores aleatórios chamada `pesos`, que será usada pela função de hash `hash()` 
 * para calcular em qual posição da tabela cada chave deve entrar. 
 * @param pesos Tabela de pesos que será preenchida com valores aleatórios */
void geraPesos(Pesos pesos) { 
    struct timeval semente;

    gettimeofday(&semente, NULL); // Utilizar o tempo como semente para a funcao srand()
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < TAMANHO_ALFABETO; j++) {
            pesos[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
        }
    }
}

/** Calcula o índice da tabela hash para uma dada chave usando os pesos gerados.
 * @param chave Chave para a qual calcular o índice
 * @param pesos Tabela de pesos
 * @return Índice da tabela hash */
Indice hash(Chave chave, Pesos pesos) { 
    unsigned int soma = 0; 
    int tamanhoChave = strlen(chave);
    for (int i = 0; i < tamanhoChave; i++) {
        soma += pesos[i][(unsigned int)chave[i]];
    }
    return (soma % M);
}

/** Inicializa a tabela hash, criando uma lista encadeada para cada posição.
 * @param tabela Tabela hash a ser inicializada */
void inicializaHash(Hash tabela) { 
    for (int i = 0; i < M; i++) {
        inicializaLista(&tabela[i]);
    }
}

/** Pesquisa por uma chave na tabela hash.
 * @param chave Chave a ser pesquisada
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash
 * @return Apontador para o item anterior da lista, ou `NULL` se não encontrado */
Apontador pesquisaChave(Chave chave, Pesos pesos, Hash tabela) { 
    Indice i;
    Apontador apontador; // Apontador de retorno aponta para o item anterior da lista
    i = hash(chave, pesos);
    if (listaEVazia(tabela[i])) { 
        return NULL;  // Pesquisa sem sucesso
    } else {
        apontador = tabela[i].primeiro; 
        while (apontador->prox->prox != NULL && strncmp(chave, apontador->prox->item.chave, sizeof(Chave))) {
            apontador = apontador->prox;
        }
        if (!strncmp(chave, apontador->prox->item.chave, sizeof(Chave))) {
            return apontador;
        } else {
            return NULL; // Pesquisa sem sucesso
        }
    }
}  

void Insere(Item x, Pesos p, Hash T)
{ if (Pesquisa(x.chave, p, T) == NULL)
  insereItemLista(x, &T[hash(x.chave, p)]);
  else printf(" Registro ja  esta  presente\n");
} 

void Retira(Item x, Pesos p, Hash T){ 
    Apontador Ap; 
    Ap = Pesquisa(x.chave, p, T);
    if (Ap == NULL)
    printf(" Registro nao esta  presente\n");
    else retiraItemLista(Ap, &T[hash(x.chave, p)], &x);
}

void Imp(Lista Lista)
{ Apontador Aux;
  Aux = Lista.primeiro->prox;
  while (Aux != NULL) 
    { printf("%.*s ", N, Aux->item.chave);
      Aux = Aux->prox;
    }
}

void Imprime(Hash tabela)
{ int i;
  for (i = 0; i < M; i++) 
    { printf("%d: ", i);
      if (!listaEVazia(tabela[i]))
      Imp(tabela[i]);
      putchar('\n');
    }
} 
 
void LerPalavra(char *p, int Tam)
{ char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && j<Tam-1) p[j++]= c;
  p[j]='\0';
  while(c != '\n') c=getchar();
  /* Desconsiderar espacos ao final 
    da cadeia como ocorre em Pascal.*/
  for(i=j-1;(i>=0 && p[i]==' ');i--) p[i]='\0';
}

int main(int argc, char *argv[])
{ inicializaHash(tabela);
  geraPesos(p); LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Insere(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos insercao:\n");
  Imprime(tabela);
  printf("Pesquisar :  ");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { apontador = Pesquisa(elemento.chave, p, tabela);
      if (apontador == NULL) printf("pesquisa sem sucesso \n");
      else printf("sucesso \n");
      printf("Pesquisar :  ");
/*    LerPalavra(elemento.chave,6); */
      LerPalavra(elemento.chave,N);
    }
  printf("Retirar seguintes chaves:\n");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Retira(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos retiradas:\n");
  Imprime(tabela);
  printf("Inserir de novo os elementos seguintes:\n");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Insere(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos novas insxercoes:\n");
  Imprime(tabela);
  return 0;
} 
