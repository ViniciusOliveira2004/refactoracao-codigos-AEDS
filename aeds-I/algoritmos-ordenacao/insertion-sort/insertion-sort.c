#include "insertion-sort.h"

void insertionSort(Vetor vetor, Indice tamanho) {
    for (int i = 2; i <= tamanho; i++) { 
        // elemento: item que vamos inserir na posição correta
        Item elemento = vetor[i];  
        vetor[0] = elemento;  // sentinela: facilita a verificação do início

        // posicao: índice que anda para a esquerda procurando onde inserir elemento
        Indice posicao = i - 1;
        while (elemento.chave < vetor[posicao].chave) { 
            vetor[posicao + 1] = vetor[posicao];  // Move elemento maior para a direita
            posicao--;
        }
        
        // Insere elemento na posição encontrada
        vetor[posicao + 1] = elemento;
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
        if (vetor[i].chave < vetor[i-1].chave) {
            printf("ERRO: ");
            imprimirVetor(vetor, tamanho);
            return;
        }
    }
    printf("OK: ");
    imprimirVetor(vetor, tamanho);
}

double gerarNumeroAleatorio() { 
    double resultado = (double) rand() / (double) RAND_MAX;
    if (resultado > 1.0) { 
        resultado = 1.0;
    }
    return resultado;
}

void gerarPermutacao(Vetor vetor, Indice tamanho) {
    for(int i = tamanho; i > 0; i--) { 
        Indice indiceAuxiliar = (i * gerarNumeroAleatorio()) + 1 ;
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

    printf("Insercao   ");
    insertionSort(ordenado, TAMANHO_VETOR);
    testarOrdenacao(ordenado, TAMANHO_VETOR);
    copiarValores(desordenado, ordenado, TAMANHO_VETOR);

    return 0;
}