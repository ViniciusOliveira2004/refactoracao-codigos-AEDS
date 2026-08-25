#include "fila.h"

void inicializaFila(Fila *fila) { 
    fila->inicio = (Apontador) malloc(sizeof(Celula));
    fila->final = fila->inicio;
    fila->inicio->prox = NULL;
}

int filaEVazia(Fila fila) { 
    return fila.inicio == fila.final; 
} 

void enfileiraItem(Item item, Fila *fila) { 
    fila->final->prox = (Apontador) malloc(sizeof(Celula));
    fila->final = fila->final->prox;
    fila->final->item = item;
    fila->final->prox = NULL;
} 

void desenfileiraItem(Item *item, Fila *fila) { 
    if (filaEVazia(*fila)) { 
        printf("Erro fila esta vazia\n"); 
        return; 
    }

    Apontador celulaRemovida; // Ponteiro para a célula que será removida
    celulaRemovida = fila->inicio;
    fila->inicio = fila->inicio->prox;
    *item = fila->inicio->item;
    free(celulaRemovida);
} 

void imprimeFila(Fila fila) { 
    Apontador auxiliar = fila.inicio->prox;
    while (auxiliar != NULL) { 
        printf("%d\n", auxiliar->item.chave);
        auxiliar = auxiliar->prox;
    }
}

int main(int argc, char *argv[]) { 
    int vetor[MAXIMO]; // Armazena os items que serão inseridos na fila
    int j, k, n; // Variáveis auxiliares para gerar uma ordem aleatória

    // Gera uma permutacao aleatoria de chaves entre 1 e MAXIMO
    struct timeval semente;
    gettimeofday(&semente,NULL);
    srand((unsigned int) semente.tv_usec);
    for(int i = 0; i < MAXIMO; i++) { 
        vetor[i] = i + 1;
    }
    for(int i = 0; i < MAXIMO; i++) { 
        k =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        j =  (int) (10.0 * rand()/(RAND_MAX + 1.0));
        n = vetor[k];
        vetor[k] = vetor[j];
        vetor[j] = n;
    }

    // Insere cada chave na lista
    Item item;
    Fila fila;
    inicializaFila(&fila);
    for (int i = 0;i < MAXIMO; i++) { 
        item.chave = vetor[i];
        enfileiraItem(item, &fila);
        printf("Enfileirou: %d \n", item.chave);
    }

    // Desenfileira cada chave
    for (int i = 0;i < MAXIMO; i++) { 
        desenfileiraItem(&item, &fila);
        printf("Desenfileirou: %d \n", item.chave);
    }

    return 0;
}