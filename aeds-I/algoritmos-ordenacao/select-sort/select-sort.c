#include <stdio.h>
#include <stdlib.h>
#define MAXTAM 20

typedef long Chave;
typedef struct TipoItem {
  Chave chave;
} TipoItem;

typedef int TipoIndice;
typedef TipoItem TipoVetor[MAXTAM + 1];
TipoVetor A;
TipoIndice i, n;

void Selecao(TipoItem *A, TipoIndice n)
{ TipoIndice i, j, Min;
  TipoItem x;
  for (i = 1; i <= n - 1; i++) 
    { Min = i;
      for (j = i + 1; j <= n; j++) 
        if (A[j].chave < A[Min].chave) Min = j;
      x = A[Min]; A[Min] = A[i]; A[i] = x;
    }
}


void Imprime(TipoItem *V, TipoIndice n)
{ for (i = 1; i <= n; i++)
    printf("%li ", V[i].chave);  printf("\n");
}

void Copia(TipoItem *Fonte, TipoItem *Destino, TipoIndice n)
{ for (i = 1; i <= n; i++)
    Destino[i] = Fonte[i];
}

void Testa(TipoItem *V, TipoIndice n)
{ for (i = 2; i <= n; i++) {
    if (V[i].chave < V[i-1].chave) {
      printf("ERRO: ");
      Imprime(V, n);
      return;
    }
  }
  printf("OK: ");
  Imprime(V, n);
}

double rand0a1() 
{ double resultado = (double) rand() / (double) RAND_MAX; /* dividir pelo maior inteiro retornado por rand() */
  if (resultado > 1.0) resultado = 1.0;
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
    A[i].chave = i;

  Permut (A,n);
  Copia (A,B,n);
 
  printf("Desordenado : ");
  Imprime(A, n);

  printf("Selecao   ");
  Selecao(B, n);
  Testa(B, n);
  Copia(A, B, n);
  return 0;
}