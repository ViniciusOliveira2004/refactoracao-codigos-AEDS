#include "quick-sort.h"

void gerarParticao(Indice esq, Indice dir, Indice *i, Indice *j, Vetor vetor) {
    *i = esq; // Índice inicial da esquerda
    *j = dir; // Índice inicial da direita

    Item aux;
    Item pivo = vetor[(*i + *j) / 2]; // Seleciona o pivô como o elemento do meio do vetor
    do {
        // Avança o índice da esquerda enquanto o valor for menor que o pivô
        while (pivo.chave > vetor[*i].chave) {
            (*i)++;
        }
        // Retrocede o índice da direita enquanto o valor for maior que o pivô
        while (pivo.chave < vetor[*j].chave) {
            (*j)--;
        }
        // Se os índices ainda não se cruzaram, troca os elementos
        if (*i <= *j) {
            aux = vetor[*i];
            vetor[*i] = vetor[*j];
            vetor[*j] = aux;

            // Depois da troca, ambos os índices continuam avançando/recuando
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j); // Continua até que os índices se cruzem
}

void ordenarParticao(Indice esq, Indice dir, Vetor vetor) {
    Indice i, j; // Índices gerados pela partição

    // Divide o vetor em duas partes em torno do pivô
    gerarParticao(esq, dir, &i, &j, vetor);

    // Ordena a parte esquerda enquanto houver elementos antes do índice j
    if (esq < j) {
        ordenarParticao(esq, j, vetor);
    }
    // Ordena a parte direita enquanto houver elementos depois do índice i
    if (i < dir) {
        ordenarParticao(i, dir, vetor);
    }
}

void quickSort(Vetor vetor, Indice tamanho) {
    ordenarParticao(1, tamanho, vetor);
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

    printf("QuickSort   ");
    quickSort(ordenado, TAMANHO_VETOR);
    testarOrdenacao(ordenado, TAMANHO_VETOR);
    copiarValores(desordenado, ordenado, TAMANHO_VETOR);

    return 0;
}