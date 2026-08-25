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
    if (listaEVazia(*lista) || anterior == NULL || anterior->prox == NULL) { 
        printf(" Erro: Lista vazia ou posicao nao existe\n");
        return;
    }

    Apontador itemRemovido; // Ponteiro para o item que será removido
    itemRemovido = anterior->prox; 
    *item = itemRemovido->item; 
    anterior->prox = itemRemovido->prox;
    if (anterior->prox == NULL) {
        lista->ultimo = anterior;
    }
    free(itemRemovido);
}

void imprimeLista(Lista lista) { 
    Apontador auxiliar = lista.primeiro->prox;
    while (auxiliar != NULL) { 
        printf("%d\n", auxiliar->item.chave);
        auxiliar = auxiliar->prox;
    }
}

int main(int argc, char *argv[]) {
    int vetor[MAXIMO_ITEMS]; // Armazena as chaves que serão inseridas na lista encadeada
    int j, k, n; // Variáveis auxiliares para gerar uma ordem aleatória

    struct timeval semente;
    gettimeofday(&semente,NULL);
    srand((unsigned int) semente.tv_usec);

    // Gera uma permutação aleatória de chaves entre 1 e MAX
    for (int i = 0; i < MAXIMO_ITEMS; i++) { 
        vetor[i] = i + 1;
    }
    for (int i = 0; i < MAXIMO_ITEMS; i++) { 
        k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        n = vetor[k];
        vetor[k] = vetor[j];
        vetor[j] = n;
    }

    Lista lista; // Lista encadeada que será utilizada para armazenar os itens
    Item item; // Variável auxiliar para guardar um item individual
    Apontador apontador; // Variável auxiliar para percorrer a lista encadeada
    float tamanho = 0; // Guarda a quantidade de elementos atualmente na lista.
    inicializaListaVazia(&lista);
    
    // Insere cada chave na lista
    for (int i = 0; i < MAXIMO_ITEMS; i++) { 
        item.chave = vetor[i];
        insereItem(item, &lista);
        tamanho++;
        printf("Inseriu: %d \n", item.chave);
    }
    imprimeLista(lista);

    // Retira cada chave da lista
    for(int i = 0; i < MAXIMO_ITEMS; i++) {
        // Escolhe uma chave aleatoriamente
        k = (int) ((tamanho) * rand() / (RAND_MAX + 1.0));
        apontador = lista.primeiro;

        // Retira a chave apontada
        retiraItem(apontador, &lista, &item);
        tamanho--;
        printf("Retirou: %d\n", item.chave);
    }

    imprimeLista(lista);
    return 0;
}