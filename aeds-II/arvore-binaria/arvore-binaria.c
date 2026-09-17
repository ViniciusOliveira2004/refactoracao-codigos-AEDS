#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

#define TAMANHO_VETOR  10

typedef long Chave;

typedef struct Registro {
  Chave chave;
} Registro;

typedef struct No * Apontador;

typedef struct No {
  Registro registro;
  Apontador esq, dir;
} No;

typedef Apontador Arvore;

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

void inicializaArvore(Arvore *arvore) { 
  *arvore = NULL; 
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

void retiraRegistro(Registro x, Apontador *p) {  
  Apontador Aux;
  
  if (*p == NULL) { 
    printf("Erro : Registro nao esta na arvore\n");
    return;
  }
  if (x.chave < (*p)->registro.chave) { 
    retiraRegistro(x, &(*p)->esq); 
    return; 
  }

  if (x.chave > (*p)->registro.chave) { 
    retiraRegistro(x, &(*p)->dir); 
    return; 
  }

  if ((*p)->dir == NULL) { 
    Aux = *p;  
    *p = (*p)->esq;
    free(Aux);
    return;
  }

  if ((*p)->esq != NULL) { 
    removePredecessor(*p, &(*p)->esq);
    return;
  }
  Aux = *p;  *p = (*p)->dir;
  free(Aux);
}  

void Central(Apontador p)
{ if (p == NULL) return;
  Central(p->esq);
  printf("%ld\n", p->registro.chave);
  Central(p->dir);
} 

void TestaI(No *p, int pai)
{ if (p == NULL) return;
  if (p->esq != NULL) 
  { if (p->registro.chave < p->esq->registro.chave) 
    { printf("Erro: Pai %ld menor que filho a esquerda %ld\n", p->registro.chave, 
             p->esq->registro.chave);
      exit(1);
    }
  }
  if (p->dir != NULL) 
  { if (p->registro.chave > p->dir->registro.chave) 
    { printf("Erro: Pai %ld maior que filho a direita %ld\n",  p->registro.chave, 
             p->dir->registro.chave);
    exit(1);
    }
  }
  TestaI(p->esq, p->registro.chave);
  TestaI(p->dir, p->registro.chave);
}


void Testa(No *p)
{ if (p != NULL)
  TestaI(p, p->registro.chave);
}

double rand0a1() {
  double resultado=  (double) rand()/ RAND_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado = 1.0;
  return resultado;
}

void Permut( Chave A[], int n) {
  int i,j; Chave b;
  for(i = n; i>0; i --) 
    { j = (i * rand0a1());
      b = A[i];
      A[i] = A[j];
      A[j] = b;
    }
}

int main(int argc, char *argv[])
{
  struct timeval t; 
  No *Dicionario;
  Registro x; 
  Chave vetor[TAMANHO_VETOR];
  int i, j, k, n;

  inicializaArvore(&Dicionario);
  /* Gera uma permutação aleatoria de chaves entre 1 e MAX */
  for (i = 0; i < TAMANHO_VETOR; i++) vetor[i] = i+1;
  gettimeofday(&t,NULL);
  srand((unsigned int)t.tv_usec);
  Permut(vetor,TAMANHO_VETOR-1);
  
  /* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 0; i < TAMANHO_VETOR; i++) 
    { x.chave = vetor[i];
      insereRegistro(x, &Dicionario);
      printf("Inseriu chave: %d\n", x.chave);
     Testa(Dicionario);
    }

  /* Retira uma chave aleatoriamente e realiza varias pesquisas */
  for (i = 0; i <= TAMANHO_VETOR; i++) 
    { k = (int) (10.0*rand()/(RAND_MAX+1.0));
      n = vetor[k];
      x.chave = n;
      retiraRegistro(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.chave);
      for (j = 0; j < TAMANHO_VETOR; j++) 
        { x.chave = vetor[(int) (10.0*rand()/(RAND_MAX+1.0))];
          if (x.chave != n) 
          { printf("Pesquisando chave: %ld\n", x.chave);
            pesquisaRegistro(&x, &Dicionario);
          }
        }
      x.chave = n;
      insereRegistro(x, &Dicionario);
      printf("Inseriu chave: %ld\n", x.chave);
      Testa(Dicionario);
    }

  /* Retira a raiz da arvore ate que ela fique vazia */
  for (i = 0; i < TAMANHO_VETOR; i++) 
    { x.chave = Dicionario->registro.chave;
      retiraRegistro(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %ld\n", x.chave);
    }
  return 0;
} 