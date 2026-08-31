#include "pilha.h"

void inicializaPilha(Pilha *pilha) { 
    pilha->topo = (Apontador) malloc(sizeof(Celula));
    pilha->fundo = pilha->topo;
    pilha->topo->prox = NULL;
    pilha->tamanho = 0;
} 

int pilhaEVazia(Pilha pilha) { 
    return pilha.topo == pilha.fundo; 
} 

void empilhaItem(Item item, Pilha *pilha) { 
    Apontador novaCelula = (Apontador) malloc(sizeof(Celula));
    pilha->topo->item = item;
    novaCelula->prox = pilha->topo;
    pilha->topo = novaCelula;
    pilha->tamanho++;
} 

void desempilhaItem(Item *item, Pilha *pilha) {
    if (pilhaEVazia(*pilha)) { 
        printf("Erro: pilha vazia\n"); 
        return; 
    }
    Apontador celulaRemovida = pilha->topo;
    pilha->topo = celulaRemovida->prox;
    *item = celulaRemovida->prox->item;
    free(celulaRemovida);  
    pilha->tamanho--;
} 

int main(int argc, char *argv[]) {   
    int vetor[MAXIMO]; // Vetor para armazenar as chaves a serem empilhadas
    int j, k, n; // Variáveis auxiliares para a geração da permutação aleatória

    // Gera uma permutacao aleatoria de chaves entre 1 e MAXIMO
    struct timeval semente;
    gettimeofday(&semente,NULL);
    srand((unsigned int)semente.tv_usec);
    for(int i = 0; i < MAXIMO; i++) { 
        vetor[i] = i + 1; 
    }
    for(int i = 0; i < MAXIMO; i++) { 
        k = (int) (10.0*rand()/(RAND_MAX + 1.0));
        j = (int) (10.0*rand()/(RAND_MAX + 1.0));
        n = vetor[k];
        vetor[k] = vetor[j];
        vetor[j] = n;
    }

    // Empilha cada chave
    Pilha pilha;
    Item item;
    inicializaPilha(&pilha);
    for (int i = 0; i < MAXIMO; i++) { 
        item.chave = vetor[i];
        empilhaItem(item, &pilha);
        printf("Empilhou: %d \n", item.chave);
    }
    printf("Tamanho da pilha: %d \n", pilha.tamanho);
    
    // Desempilha cada chave
    for(int i = 0; i < MAXIMO; i++) { 
        desempilhaItem(&item, &pilha);
        printf ("Desempilhou: %d \n", item.chave);
    }
    printf("Tamanho da pilha: %d\n", pilha.tamanho);

    return 0;
}
