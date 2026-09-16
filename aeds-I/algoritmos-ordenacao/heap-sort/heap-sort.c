#include "heap-sort.h"

void refazSubArvore(Vetor vetor, Indice esq, Indice dir) { 
    Indice i = esq; // Posição atual do pai que pode estar fora de lugar
    Indice j = i * 2; // Filho da esquerda
    Item elementoPai = vetor[i]; // Guarda o valor do pai para inserir depois no lugar correto

    while (j <= dir) { 
        // Escolhe o maior filho entre os filhos da esquerda e da direita
        if (j < dir) { 
            if (vetor[j].chave < vetor[j + 1].chave) {
                j++;
            }
        }

        // Se o pai já for maior ou igual ao maior filho, a subárvore está correta
        if (elementoPai.chave >= vetor[j].chave) {
            goto L999;
        }

        // Move o filho maior para cima
        vetor[i] = vetor[j];
        i = j;  
        j = i * 2;
    }

    // Coloca o valor original do pai no ponto final correto da subárvore
    L999: vetor[i] = elementoPai;
}

void constroiHeap(Vetor vetor, Indice tamanho) { 
    Indice esq = tamanho / 2 + 1;
    while (esq > 1) { 
        esq--;
        // Reestrutura a subárvore com raiz em 'esq' para manter a propriedade do heap máximo
        refazSubArvore(vetor, esq, tamanho);
    }
}

void heapSort(Vetor vetor, Indice tamanho) {
    // Constrói o heap máximo a partir do vetor
    constroiHeap(vetor, tamanho);
    Indice esq = 1;  
    Indice dir = tamanho;

    while (dir > 1) { 
        // Coloca o maior elemento no final da parte ainda não ordenada.
        Item auxiliar = vetor[1];
        vetor[1] = vetor[dir];
        vetor[dir] = auxiliar;

        // Remove esse elemento da região do heap e reestrutura o heap.
        dir--;
        refazSubArvore(vetor, esq, dir);
    }
}

void imprimirVetor(Vetor vetor, Indice tamanho) {
    for (int i = 1; i <= tamanho; i++) {
        printf("%li ", vetor[i].chave);
    }
    printf("\n");
}

void copiarValores(Vetor fonte, Vetor destino, Indice tamanho) {
    for (int i = 1; i <= tamanho; i++) {
        destino[i] = fonte[i];
    }
}

void testarOrdenacao(Vetor vetor, Indice tamanho) {
    for (int i = 2; i <= tamanho; i++) {
        if (vetor[i].chave < vetor[i - 1].chave) {
            printf("ERRO: ");
            imprimirVetor(vetor, tamanho);
            return;
        }
    }
    printf("OK: ");
    imprimirVetor(vetor, tamanho);
}

double gerarNumeroAleatorio() {
    double resultado = (double)rand() / (double)RAND_MAX;
    if (resultado > 1.0) {
        resultado = 1.0;
    }
    return resultado;
}

void gerarPermutacao(Vetor vetor, Indice tamanho) {
    for (int i = tamanho; i > 0; i--) {
        Indice indiceAuxiliar = (i * gerarNumeroAleatorio()) + 1;
        Item itemAuxiliar = vetor[i];
        vetor[i] = vetor[indiceAuxiliar];
        vetor[indiceAuxiliar] = itemAuxiliar;
    }
}


int main(int argc, char *argv[]) {
    Vetor desordenado;
    Vetor ordenado;

    for (int i = 1; i < TAMANHO_VETOR; i++) {
        desordenado[i].chave = i;
    }

    gerarPermutacao(desordenado, TAMANHO_VETOR);

    copiarValores(desordenado, ordenado, TAMANHO_VETOR);

    printf("Desordenado: ");
    imprimirVetor(desordenado, TAMANHO_VETOR);

    printf("Heapsort  ");
    heapSort(ordenado, TAMANHO_VETOR);
    testarOrdenacao(ordenado, TAMANHO_VETOR);
    copiarValores(desordenado, ordenado, TAMANHO_VETOR);

    return 0;
}