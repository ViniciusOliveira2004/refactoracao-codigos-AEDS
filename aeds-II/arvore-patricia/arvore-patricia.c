#include "arvore-patricia.h"

Bit coletaBit(Indice indice, Chave chave) {
  if (indice == 0) {
    return 0;
  } else { 
    int bit = chave;
    for (int j = 1; j <= TAMANHO_CHAVE - indice; j++) {
      bit /= 2;
    }
    return bit & 1;
  }
} 

short noEExterno(Arvore no) {
  return no->tipo == Externo;
}

Arvore criaNoInterno(int indice, Arvore *esq,  Arvore *dir) { 
  Arvore arvore;
  arvore = (Arvore)malloc(sizeof(No));
  arvore->tipo = Interno; 
  arvore->no.noInterno.esq = *esq;
  arvore->no.noInterno.dir = *dir;
  arvore->no.noInterno.indice = indice; 
  return arvore;
} 

Arvore criaNoExterno(Chave chave){ 
  Arvore arvore;
  arvore = (Arvore) malloc(sizeof(No));
  arvore->tipo = Externo;
  arvore->no.chave = chave; 
  return arvore;
}  

void pesquisaChave(Chave chave, Arvore arvore) { 
  if (noEExterno(arvore)) { 
    if (chave == arvore->no.chave) {
      printf("Elemento encontrado\n");
    } else {
      printf("Elemento nao encontrado\n");
    }
    return;
  }

  if (coletaBit(arvore->no.noInterno.indice, chave) == 0) {
    pesquisaChave(chave, arvore->no.noInterno.esq);
  } else {
    pesquisaChave(chave, arvore->no.noInterno.dir);
  }
} 

Arvore insereChaveEntre(Chave chave, Arvore *arvore, int indice) { 
  if (noEExterno(*arvore) || indice < (*arvore)->no.noInterno.indice) { 
    // Cria um novo nó externo
    Arvore arvoreAuxiliar = criaNoExterno(chave);
    if (coletaBit(indice, chave) == 1) {
      return criaNoInterno(indice, arvore, &arvoreAuxiliar);
    } else {
      return criaNoInterno(indice, &arvoreAuxiliar, arvore);
    }
  } else { 
    if (coletaBit((*arvore)->no.noInterno.indice, chave) == 1) {
      (*arvore)->no.noInterno.dir = insereChaveEntre(chave, &(*arvore)->no.noInterno.dir, indice);
    } else {
      (*arvore)->no.noInterno.esq = insereChaveEntre(chave, &(*arvore)->no.noInterno.esq, indice);
    }
    return (*arvore);
  }
}

Arvore insereChave(Chave chave, Arvore *arvore) {
  if (*arvore == NULL) {
    return (criaNoExterno(chave));
  } else {
    Arvore arvoreAuxiliar = *arvore;
    while (!noEExterno(arvoreAuxiliar)) { 
      if (coletaBit(arvoreAuxiliar->no.noInterno.indice, chave) == 1) {
        arvoreAuxiliar = arvoreAuxiliar->no.noInterno.dir;
      } else {
        arvoreAuxiliar = arvoreAuxiliar->no.noInterno.esq;
      }
    }

    int i = 1;
    while ((i <= TAMANHO_CHAVE) & (coletaBit(i, chave) == coletaBit(i, arvoreAuxiliar->no.chave))) {
      i++;
    }

    if (i > TAMANHO_CHAVE) { 
      printf("Erro: chave ja esta na arvore\n");  
      return (*arvore); 
    } else {
      return insereChaveEntre(chave, arvore, i);
    }
  }
}

int main(int argc, char *argv[]) { 
  Chave chave; // Variável auxiliar para guarda uma chave individual
  int j, k, n; // Variáveis auxiliares para gerar uma ordem aleatória
  int  min = 32, max = 126; // Definem definem o intervalo de caracteres usados "32 = espaço" e "126 = ~"
  Chave vetor[95]; // Vetor que armazena os caracteres ASCII de 32 a 126 em uma ordem aleatória

  // Gera uma permutação aleatória de chaves dos caracteres ASCII 32 a 126
  struct timeval semente;
  gettimeofday(&semente, NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));  
  for (int i = min; i <= max; i++) { 
    vetor[i - 32] = i; 
  }
  for (int i = min; i <= max; i++) { 
    k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0)); 
    j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
    n = vetor[k - 32]; 
    vetor[k - 32] = vetor[j - 32]; 
    vetor[j - 32] = n; 
  }

  // Insere cada chave na árvore
  Arvore arvore = NULL;
  for (int i = min; i <= max; i++) { 
    chave = vetor[i - 32]; printf("Inserindo chave: %c\n", chave);
    arvore = insereChave(chave, &arvore);
  }

  // Gera outra permutação aleatória de chaves
  for (int i = min; i <= max; i++) { 
    k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
    j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
    n = vetor[k - 32]; 
    vetor[k - 32] = vetor[j - 32];
    vetor[j - 32] = n;
  }

  // Pesquisa cada chave na árvore
  for (int i = min; i <= max; i++) { 
    chave = vetor[i - 32]; printf("Pesquisando chave: %c\n", chave);
    pesquisaChave(chave, arvore);
  }
  return 0;
} 
