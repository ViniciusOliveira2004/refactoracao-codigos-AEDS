#include   <limits.h>
#include   <stdio.h>
#include   <stdlib.h>
#define MAXTAM 20

typedef long TipoChave;
typedef struct TipoItem {
  TipoChave Chave;
  /* outros componentes */
} TipoItem;

typedef int TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1]; 
/* MAXTAM+1 por causa da sentinela em Insercao */
TipoVetor A;
TipoIndice i, n;

void Particao(TipoIndice Esq, TipoIndice Dir, 
              TipoIndice *i, TipoIndice *j, TipoItem *A)
{ TipoItem x, w;
  *i = Esq;  *j = Dir;
  x = A[(*i + *j) / 2]; /* obtem o pivo x */
  do 
    { while (x.Chave > A[*i].Chave) (*i)++;
      while (x.Chave < A[*j].Chave) (*j)--;
      if (*i <= *j) 
      { w = A[*i]; A[*i] = A[*j]; A[*j] = w;
        (*i)++; (*j)--;
      }
    } while (*i <= *j);
}

void Ordena(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i, j;
  Particao(Esq, Dir, &i, &j, A);
  if (Esq < j) Ordena(Esq, j, A);
  if (i < Dir) Ordena(i, Dir, A);
}

void QuickSort(TipoItem *A, TipoIndice n)
{ Ordena(1, n, A); }


void Imprime(TipoItem *V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%li ", V[i].Chave);  printf("\n");
}

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

void Testa(TipoItem *V, TipoIndice n)
{ for (i = 2; i <= n; i++) {
    if (V[i].Chave < V[i-1].Chave) {
      printf("ERRO: ");
      Imprime(V, n);
      return;
    }
  }
  printf("OK: ");
  Imprime(V, n);
}

double rand0a1() 
{ double resultado=  (double) rand()/ INT_MAX; /* Dividir pelo maior inteiro */
  if(resultado>1.0) resultado= 1.0;
  return resultado;
}

void Permut( TipoItem *A, int n) 
{ int i,j;
  TipoItem b;

  for(i = n-1; i>0; i --) 
  { j = (i * rand0a1()) +1 ;
    b = A[i];
    A[i] = A[j];
    A[j] = b;
  }
}

int main(int argc, char *argv[])
{ TipoVetor B;
  n = 20;   /*Tamanho do arranjo a ser ordenado*/
  for (i = 1; i <= n; i++) 
    A[i].Chave = i;

  Permut (A,n);
  Copia (A,B,n);
 
  printf("Desordenado : ");
  Imprime(A, n);

  printf("Quicksort ");
  QuickSort(B, n);
  Testa(B, n);
  Copia(A, B, n);
  return 0;
}