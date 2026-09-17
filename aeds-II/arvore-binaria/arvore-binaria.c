#include "arvore-binaria.h"

void inicializaArvore(Arvore *arvore) { 
  *arvore = NULL; 
}

void pesquisaRegistro(Registro *registro, Arvore *arvore) { 
  if (*arvore == NULL) { 
    printf("Erro: Registro nao esta presente na arvore\n");
    return;
  }

  if (registro->chave < (*arvore)->registro.chave) { 
    pesquisaRegistro(registro, &(*arvore)->esq);
    return;
  }

  if (registro->chave > (*arvore)->registro.chave) { 
    pesquisaRegistro(registro, &(*arvore)->dir);
  } else { 
    *registro = (*arvore)->registro;
  }
} 

void insereRegistro(Registro registro, Arvore *arvore) { 
  if (*arvore == NULL) { 
    *arvore = (Apontador) malloc(sizeof(No));
    (*arvore)->registro = registro; 
    (*arvore)->esq = NULL; 
    (*arvore)->dir = NULL;
    return;
  }

  if (registro.chave < (*arvore)->registro.chave) { 
    insereRegistro(registro, &(*arvore)->esq); 
    return; 
  }

  if (registro.chave > (*arvore)->registro.chave) {
    insereRegistro(registro, &(*arvore)->dir);
  } else {
    printf("Erro : Registro ja existe na arvore\n");
  }
}

void removePredecessor(Apontador noRemovido, Arvore *arvore) { 
  if ((*arvore)->dir != NULL) { 
    removePredecessor(noRemovido, &(*arvore)->dir);
    return;
  }
  noRemovido->registro = (*arvore)->registro;
  noRemovido = *arvore; 
  *arvore = (*arvore)->esq;
  free(noRemovido);
} 

void retiraRegistro(Registro registro, Arvore *arvore) {  
  if (*arvore == NULL) { 
    printf("Erro : Registro nao esta na arvore\n");
    return;
  }

  if (registro.chave < (*arvore)->registro.chave) { 
    retiraRegistro(registro, &(*arvore)->esq); 
    return; 
  }

  if (registro.chave > (*arvore)->registro.chave) { 
    retiraRegistro(registro, &(*arvore)->dir); 
    return; 
  }

  Apontador auxiliar;
  if ((*arvore)->dir == NULL) { 
    auxiliar = *arvore;  
    *arvore = (*arvore)->esq;
    free(auxiliar);
    return;
  }

  if ((*arvore)->esq != NULL) { 
    removePredecessor(*arvore, &(*arvore)->esq);
    return;
  }
  auxiliar = *arvore;  
  *arvore = (*arvore)->dir;
  free(auxiliar);
} 


void verificaArvore(Arvore arvore) { 
  if (arvore == NULL) {
    return;
  }
  if (arvore->esq != NULL) { 
    if (arvore->registro.chave < arvore->esq->registro.chave) { 
      printf("Erro: Pai %ld menor que filho a esquerda %ld\n", arvore->registro.chave, arvore->esq->registro.chave);
      exit(1);
    }
  }
  if (arvore->dir != NULL) { 
    if (arvore->registro.chave > arvore->dir->registro.chave) { 
      printf("Erro: Pai %ld maior que filho a direita %ld\n",  arvore->registro.chave, arvore->dir->registro.chave);
      exit(1);
    }
  }
  verificaArvore(arvore->esq);
  verificaArvore(arvore->dir);
}

double gerarNumeroAleatorio() { 
    double resultado = (double) rand() / (double) RAND_MAX;
    if (resultado > 1.0) { 
        resultado = 1.0;
    }
    return resultado;
}

void gerarPermutacao(Chave vetor[], int tamanho) {
  for(int i = tamanho; i > 0; i--) { 
      int indiceAuxiliar = (i * gerarNumeroAleatorio());
      Chave chaveAuxiliar = vetor[i];
      vetor[i] = vetor[indiceAuxiliar];
      vetor[indiceAuxiliar] = chaveAuxiliar;
  }
}

int main(int argc, char *argv[]) {
  // Gera uma permutação aleatoria de chaves entre 1 e TAMANHO_VETOR
  Chave vetor[TAMANHO_VETOR];
  for (int i = 0; i < TAMANHO_VETOR; i++) {
    vetor[i] = i+1;
  }
  struct timeval semente;
  gettimeofday(&semente,NULL);
  srand((unsigned int) semente.tv_usec);
  gerarPermutacao(vetor,TAMANHO_VETOR-1);
  
  Arvore arvore;
  Registro auxiliar;
  inicializaArvore(&arvore);
  // Insere cada chave na arvore e testa sua integridade apos cada insercao
  for (int i = 0; i < TAMANHO_VETOR; i++) { 
    auxiliar.chave = vetor[i];
    insereRegistro(auxiliar, &arvore);
    printf("Inseriu chave: %d\n", auxiliar.chave);
    verificaArvore(arvore);
  }

  // Retira uma chave aleatoriamente e realiza varias pesquisas
  for (int i = 0; i <= TAMANHO_VETOR; i++) { 
    int k = (int) (10.0 * rand() / (RAND_MAX + 1.0));
    int n = vetor[k];
    auxiliar.chave = n;
    retiraRegistro(auxiliar, &arvore);
    verificaArvore(arvore);
    printf("Retirou chave: %ld\n", auxiliar.chave);
    for (int j = 0; j < TAMANHO_VETOR; j++)  { 
      auxiliar.chave = vetor[(int) (10.0*rand()/(RAND_MAX+1.0))];
      if (auxiliar.chave != n) { 
        printf("Pesquisando chave: %ld\n", auxiliar.chave);
        pesquisaRegistro(&auxiliar, &arvore);
      }
    }
    auxiliar.chave = n;
    insereRegistro(auxiliar, &arvore);
    printf("Inseriu chave: %ld\n", auxiliar.chave);
    verificaArvore(arvore);
  }

  // Retira a raiz da arvore ate que ela fique vazia
  for (int i = 0; i < TAMANHO_VETOR; i++) { 
    auxiliar.chave = arvore->registro.chave;
    retiraRegistro(auxiliar, &arvore);
    verificaArvore(arvore);
    printf("Retirou chave: %ld\n", auxiliar.chave);
  }

  return 0;
} 