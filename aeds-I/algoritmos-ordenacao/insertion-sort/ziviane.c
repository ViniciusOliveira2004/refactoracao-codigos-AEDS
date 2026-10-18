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

void Insercao(TipoItem *A, TipoIndice n)
{ TipoIndice i, j;
  TipoItem x;
  for (i = 2; i <= n; i++) 
    { x = A[i];  j = i - 1;
      A[0] = x;  /* sentinela */
      while (x.Chave < A[j].Chave) 
        { A[j+1] = A[j];  j--;
        }
      A[j+1] = x;
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

  printf("Insercao  ");
  Insercao(B, n);
  Testa(B, n);
  Copia(A, B, n);
  return 0;
}