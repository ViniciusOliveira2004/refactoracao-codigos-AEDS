#include "lista-encadeada.h"

void inicializaListaVazia(Lista *lista) {
    lista->primeiro = (Apontador) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

int listaEVazia(Lista lista) { 
    return lista.primeiro == lista.ultimo;
}

void insereItem(Item item, Lista *lista) { 
    lista->ultimo->prox = (Apontador) malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item = item;
    lista->ultimo->prox = NULL;
}

void retiraItem(Apontador anterior, Lista *lista, Item *item) {
    Apontador itemRemovido; // Ponteiro para o item que será removido

    if (listaEVazia(*lista) || anterior == NULL || anterior->prox == NULL) { 
        printf(" Erro: Lista vazia ou posicao nao existe\n");
        return;
    }

    itemRemovido = anterior->prox; 
    *item = itemRemovido->item; 
    anterior->prox = itemRemovido->prox;
    if (anterior->prox == NULL) {
        lista->ultimo = anterior;
    }
    free(itemRemovido);
}

void imprimeLista(Lista lista) { 
    Apontador auxiliar;
    auxiliar = lista.primeiro->prox;
    while (auxiliar != NULL) { 
        printf("%d\n", auxiliar->item.Chave);
        auxiliar = auxiliar->prox;
    }
}

int main(int argc, char *argv[]) { 
    struct timeval t;
    Lista lista;
    Item item;
    Apontador p;
    inicializaListaVazia(&lista);

    int vetor[MAXIMO_ITEMS];
    int i, j, k, n;
    float tamanho = 0;

    gettimeofday(&t,NULL);
    srand((unsigned int)t.tv_usec);

    // Gera uma permutação aleatória de chaves entre 1 e MAX
    for (i = 0; i < MAXIMO_ITEMS; i++) { 
        vetor[i] = i + 1;
    }
    for (i = 0; i < MAXIMO_ITEMS; i++) { 
        k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        n = vetor[k];
        vetor[k] = vetor[j];
        vetor[j] = n;
    }

    // Insere cada chave na lista
    for (i = 0; i < MAXIMO_ITEMS; i++) { 
        item.Chave = vetor[i];
        insereItem(item, &lista);
        tamanho++;
        printf("Inseriu: %d \n", item.Chave);
    }
    imprimeLista(lista);

    // Retira cada chave da lista
    for(i = 0; i < MAXIMO_ITEMS; i++) {
        // Escolhe uma chave aleatoriamente
        k = (int) ((tamanho) * rand() / (RAND_MAX + 1.0));
        p = lista.primeiro;

        // Retira a chave apontada
        retiraItem(p, &lista, &item);
        tamanho--;
        printf("Retirou: %d\n", item.Chave);
    }

    imprimeLista(lista);
    return 0;
}