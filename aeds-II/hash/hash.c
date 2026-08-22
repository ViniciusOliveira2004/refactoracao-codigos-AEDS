#include "hash.h"

short listaEVazia(Lista lista) { 
    return lista.primeiro == lista.ultimo; 
}

void inicializaLista(Lista *lista) {
    lista->primeiro = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro; 
    lista->primeiro->prox = NULL;
}  

void inicializaHash(Hash tabela) { 
    for (int i = 0; i < TAMANHO_HASH; i++) {
        inicializaLista(&tabela[i]);
    }
}

Indice hash(Chave chave, Pesos pesos) { 
    unsigned int soma = 0; 
    int tamanhoChave = strlen(chave);
    for (int i = 0; i < tamanhoChave; i++) {
        soma += pesos[i][(unsigned int)chave[i]];
    }
    return (soma % TAMANHO_HASH);
}

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

void insereItemLista(Item item, Lista *lista) { 
    lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox; 
    lista->ultimo->item = item;
    lista->ultimo->prox = NULL;
}  

void insereItem(Item item, Pesos pesos, Hash tabela) { 
    if (pesquisaChave(item.chave, pesos, tabela) == NULL) {
        insereItemLista(item, &tabela[hash(item.chave, pesos)]);
    } else {
        printf("Registro ja esta presente\n");
    }
} 

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

void retiraItem(Item item, Pesos pesos, Hash tabela){ 
    Apontador apontador = pesquisaChave(item.chave, pesos, tabela);
    if (apontador == NULL) {
        printf("Registro nao esta presente\n");
    } else {
        retiraItemLista(apontador, &tabela[hash(item.chave, pesos)], &item);
    }
}

void geraPesos(Pesos pesos) { 
    struct timeval semente;

    gettimeofday(&semente, NULL); // Utilizar o tempo como semente para a funcao srand()
    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));

    for (int i = 0; i < TAMANHO_CHAVE; i++) {
        for (int j = 0; j < TAMANHO_ALFABETO; j++) {
            pesos[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
        }
    }
}

void imprimeLista(Lista lista) { 
    Apontador auxiliar = lista.primeiro->prox;
    while (auxiliar != NULL) { 
        printf("%.*s ", TAMANHO_CHAVE, auxiliar->item.chave);
        auxiliar = auxiliar->prox;
    }
}

void imprimeTabela(Hash tabela) {
    for (int i = 0; i < TAMANHO_HASH; i++) { 
        printf("%d: ", i);
        if (!listaEVazia(tabela[i])){
            imprimeLista(tabela[i]);
        }
        putchar('\n');
    }
} 

void lerPalavra(char *string, int tamanho) { 
    char caractere; 
    int i, j = 0;
    fflush(stdin);

    while (((caractere = getchar()) != '\n') && j < tamanho - 1) {
        string[j++] = caractere;
    }
    string[j] = '\0';

    while (caractere != '\n') { 
        caractere = getchar();
    }

    for (i= j - 1; (i >= 0 && string[i] == ' '); i--) { 
        string[i] = '\0';
    }
}

int main(int argc, char *argv[]) {
    Hash tabela;
    Item elemento;
    Pesos p;
    Apontador apontador;
    inicializaHash(tabela);
    geraPesos(p);

    lerPalavra(elemento.chave, TAMANHO_CHAVE);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        insereItem(elemento, p, tabela);
        lerPalavra(elemento.chave,TAMANHO_CHAVE);
    }

    printf("Tabela apos insercao:\n");
    imprimeTabela(tabela);

    printf("Pesquisar :  ");
    lerPalavra(elemento.chave,TAMANHO_CHAVE);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        apontador = pesquisaChave(elemento.chave, p, tabela);
        if (apontador == NULL) { 
            printf("Pesquisa sem sucesso \n");
        } else {
            printf("Pesquisa com sucesso \n");
        }
        printf("Pesquisar :  ");
        lerPalavra(elemento.chave,TAMANHO_CHAVE);
    }

    printf("Retirar seguintes chaves:\n");
    lerPalavra(elemento.chave,TAMANHO_CHAVE);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        retiraItem(elemento, p, tabela);
        lerPalavra(elemento.chave,TAMANHO_CHAVE);
    }

    printf("Tabela apos retiradas:\n");
    imprimeTabela(tabela);

    printf("Inserir de novo os elementos seguintes:\n");
    lerPalavra(elemento.chave,TAMANHO_CHAVE);
    while (strcmp(elemento.chave, "aaaaaa") != 0) { 
        insereItem(elemento, p, tabela);
        lerPalavra(elemento.chave,TAMANHO_CHAVE);
    }

    printf("Tabela apos novas insercoes:\n");
    imprimeTabela(tabela);
    return 0;
} 
