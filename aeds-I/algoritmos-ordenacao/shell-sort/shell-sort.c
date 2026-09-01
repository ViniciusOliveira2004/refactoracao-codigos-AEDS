#include "shell-sort.h"

void shellSort(Vetor vetor, Indice tamanho) {
    // gap: distância entre elementos comparados (sequência de Knuth)
    int gap = 1;
    do {
        gap = gap * 3 + 1;
    } while (gap < tamanho);

    // Reduz o gap a cada iteração e aplica um insertion sort com esse gap
    do {
        gap /= 3;

        for (int i = gap + 1; i <= tamanho; i++)  { 
            // elemento: guarda temporariamente o valor que vamos inserir
            Item elemento = vetor[i];  

            // posicao: Anda para a esquerda em passos de `gap` para inserir `elemento`
            int posicao = i;

            // Enquanto o elemento `gap` posições à esquerda for maior, desloca-o para a direita
            while (vetor[posicao - gap].chave > elemento.chave) { 
                // Move maior para a direita
                vetor[posicao] = vetor[posicao - gap]; 
                posicao -= gap;
                
                // Se chegarmos até a borda da subsequência, pare
                if (posicao <= gap) {
                    break;
                }
            }
            // Insere o elemento em seu lugar
            vetor[posicao] = elemento; 
        }
    } while (gap != 1);
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

    printf("Shellsort   ");
    shellSort(ordenado, TAMANHO_VETOR);
    testarOrdenacao(ordenado, TAMANHO_VETOR);
    copiarValores(desordenado, ordenado, TAMANHO_VETOR);

    return 0;
}