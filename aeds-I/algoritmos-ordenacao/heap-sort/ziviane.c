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

void Refaz(TipoIndice Esq, TipoIndice Dir, TipoItem *A)
{ TipoIndice i = Esq;
  int j;
  TipoItem x;
  j = i * 2;
  x = A[i];
  while (j <= Dir) 
    { if (j < Dir) 
      { if (A[j].Chave < A[j+1].Chave)
        j++;
      }
      if (x.Chave >= A[j].Chave) goto L999;
      A[i] = A[j];
      i = j;  j = i * 2;
    }
  L999: A[i] = x;
}

void Constroi(TipoItem *A, TipoIndice n)
{ TipoIndice Esq;
  Esq = n / 2 + 1;
  while (Esq > 1) 
    { Esq--;
      Refaz(Esq, n, A);
    }
}

/*--Entra aqui a funcao Refaz do Programa 4.9 --*/
/*--Entra aqui a funcao Constroi do Programa 4.10--*/

void Heapsort(TipoItem *A, TipoIndice n)
{ TipoIndice Esq, Dir;
  TipoItem x;
  Constroi(A, n);  /* constroi o heap */
  Esq = 1;  Dir = n;
  while (Dir > 1) 
    { /* ordena o vetor */
      x = A[1];  A[1] = A[Dir];  A[Dir] = x;  Dir--; 
      Refaz(Esq, Dir, A);
    }
}

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

  printf("Heapsort  ");
  Heapsort(B, n);
  Testa(B, n);
  Copia(A, B, n);
  return 0;
}