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

/** Verifica se a lista `lista` está vazia, comparando o ponteiro do primeiro elemento com o ponteiro do último elemento.
 * @param lista Lista que será verificada
 * @returns 1 se a lista estiver vazia, 0 caso contrário */
short listaEVazia(Lista lista) { 
    return lista.primeiro == lista.ultimo; 
}

/** Inicializa uma lista da tabela Hash, alocando memória para o primeiro elemento 
 *  e definindo o último elemento como o primeiro.
 * @param lista Lista que será inicializada */
void inicializaLista(Lista *lista) {
    lista->primeiro = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro; 
    lista->primeiro->prox = NULL;
}  

/** Inicializa a tabela hash, criando uma lista encadeada para cada posição.
 * @param tabela Tabela hash a ser inicializada */
void inicializaHash(Hash tabela) { 
    for (int i = 0; i < M; i++) {
        inicializaLista(&tabela[i]);
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

/** Insere um item na tabela hash.
 * @param item Item a ser inserido
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash */
void insereItem(Item item, Pesos pesos, Hash tabela) { 
    if (pesquisaChave(item.chave, pesos, tabela) == NULL) {
        insereItemLista(item, &tabela[hash(item.chave, pesos)]);
    } else {
        printf("Registro ja esta presente\n");
    }
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

/** Retira um item da tabela hash.
 * @param item Item a ser retirado
 * @param pesos Tabela de pesos
 * @param tabela Tabela hash */
void retiraItem(Item item, Pesos pesos, Hash tabela){ 
    Apontador apontador = pesquisaChave(item.chave, pesos, tabela);
    if (apontador == NULL) {
        printf("Registro nao esta presente\n");
    } else {
        retiraItemLista(apontador, &tabela[hash(item.chave, pesos)], &item);
    }
}

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

/** Imprime a lista encadeada.
 * @param lista Lista a ser impressa */
void imprimeLista(Lista lista) { 
    Apontador auxiliar = lista.primeiro->prox;
    while (auxiliar != NULL) { 
        printf("%.*s ", N, auxiliar->item.chave);
        auxiliar = auxiliar->prox;
    }
}

/** Imprime a tabela hash.
 * @param tabela Tabela hash a ser impressa */
void imprimeTabela(Hash tabela) {
    for (int i = 0; i < M; i++) { 
        printf("%d: ", i);
        if (!listaEVazia(tabela[i])){
            imprimeLista(tabela[i]);
        }
        putchar('\n');
    }
} 

/** Lê uma palavra do teclado.
 * @param p Ponteiro para a string onde a palavra será armazenada
 * @param Tam Tamanho máximo da string */
void lerPalavra(char *p, int Tam) { 
    char c; 
    int i, j = 0;
    fflush(stdin);
    while (((c = getchar()) != '\n') && j < Tam - 1) {
        p[j++] = c;
    }
    p[j] = '\0';

    while (c != '\n') { 
        c = getchar();
    }
    // Desconsiderar espacos ao final da cadeia como ocorre em Pascal.
    for (i= j - 1; (i >= 0 && p[i] == ' '); i--) { 
        p[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    Hash tabela;
    Item elemento;
    Pesos p;
    Apontador apontador;
    inicializaHash(tabela);
    geraPesos(p);

    lerPalavra(elemento.chave,N);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        insereItem(elemento, p, tabela);
        lerPalavra(elemento.chave,N);
    }

    printf("Tabela apos insercao:\n");
    imprimeTabela(tabela);

    printf("Pesquisar :  ");
    lerPalavra(elemento.chave,N);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        apontador = pesquisaChave(elemento.chave, p, tabela);
        if (apontador == NULL) { 
            printf("Pesquisa sem sucesso \n");
        } else {
            printf("Pesquisa com sucesso \n");
        }
        printf("Pesquisar :  ");
        lerPalavra(elemento.chave,N);
    }

    printf("Retirar seguintes chaves:\n");
    lerPalavra(elemento.chave,N);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        retiraItem(elemento, p, tabela);
        lerPalavra(elemento.chave,N);
    }

    printf("Tabela apos retiradas:\n");
    imprimeTabela(tabela);

    printf("Inserir de novo os elementos seguintes:\n");
    lerPalavra(elemento.chave,N);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        insereItem(elemento, p, tabela);
        lerPalavra(elemento.chave,N);
    }

    printf("Tabela apos novas insercoes:\n");
    imprimeTabela(tabela);
    return 0;
} 
