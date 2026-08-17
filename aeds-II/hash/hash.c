#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#define M 7
#define N 7      
#define TAMALFABETO 256

/* typedef unsigned int  Pesos[n]; */
typedef char Chave[N];
typedef unsigned Pesos[N][TAMALFABETO];

typedef struct Item {
  Chave chave;
} Item;

typedef unsigned int Indice;
typedef struct Celula* Apontador;

typedef struct Celula {
  Item item;
  Apontador prox;
} Celula;

typedef struct Lista {
  Celula *primeiro, *ultimo;
} Lista;

typedef Lista Hash[M];

Hash tabela;
Item elemento;
Pesos p;
Apontador apontador;

void FLVazia(Lista *Lista)
{ Lista->primeiro = (Celula *)malloc(sizeof(Celula));
  Lista->ultimo = Lista->primeiro; Lista->primeiro->prox = NULL;
}  

short Vazia(Lista Lista)
{ return (Lista.primeiro == Lista.ultimo); }

void Ins(Item x, Lista *Lista)
{ Lista->ultimo->prox = (Celula *)malloc(sizeof(Celula));
  Lista->ultimo = Lista->ultimo->prox; Lista->ultimo->item = x;
  Lista->ultimo->prox = NULL;
}  

void Ret(Apontador p, Lista *Lista, Item *Item)
{  /* -- Obs.: o item a ser retirado o seguinte ao apontado por p -- */
  Apontador q;
  if (Vazia(*Lista) || p == NULL || p->prox == NULL) 
  { printf(" Erro Lista vazia ou posicao nao existe\n");
    return;
  }
  q = p->prox; *Item = q->item; p->prox = q->prox;
  if (p->prox == NULL)
  Lista->ultimo = p;
  free(q);
}

/*
void GeraPesos(Pesos p)
{ int i;
  struct timeval semente;
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));
  for (i = 0; i < n; i++)
     p[i] =  1+(int) (10000.0*rand()/(RAND_MAX+1.0));
}

Indice h(Chave Chave, Pesos p)
{ int i; 
  unsigned int Soma = 0; 
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += (unsigned int)Chave[i] * p[i];
  return (Soma % M);
}
*/

void GeraPesos(Pesos p)
{ /* Gera valores randomicos entre 1 e 10.000 */
  int i, j;
  struct timeval semente;
  /* Utilizar o tempo como semente para a funcao srand() */
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (i = 0; i < N; i++)
    for (j = 0; j < TAMALFABETO; j++)
      p[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
}

Indice h(Chave Chave, Pesos p)
{ int i; unsigned int Soma = 0; 
  int comp = strlen(Chave);
  for (i = 0; i < comp; i++) Soma += p[i][(unsigned int)Chave[i]];
  return (Soma % M);
}

void Inicializa(Hash T)
{ int i;
  for (i = 0; i < M; i++) FLVazia(&T[i]);
}

Apontador Pesquisa(Chave Ch, Pesos p, Hash T)
{ /* Obs.: Apontador de retorno aponta para o item anterior da lista */
  Indice i;
  Apontador Ap;
  i = h(Ch, p);
  if (Vazia(T[i])) return NULL;  /* Pesquisa sem sucesso */
  else 
  { Ap = T[i].primeiro;
    while (Ap->prox->prox != NULL &&
        strncmp(Ch, Ap->prox->item.chave, sizeof(Chave))) 
      Ap = Ap->prox;
    if (!strncmp(Ch, Ap->prox->item.chave, sizeof(Chave))) 
    return Ap;
    else return NULL;  /* Pesquisa sem sucesso */
  }
}  

void Insere(Item x, Pesos p, Hash T)
{ if (Pesquisa(x.chave, p, T) == NULL)
  Ins(x, &T[h(x.chave, p)]);
  else printf(" Registro ja  esta  presente\n");
} 

void Retira(Item x, Pesos p, Hash T)
{ Apontador Ap; Ap = Pesquisa(x.chave, p, T);
  if (Ap == NULL)
  printf(" Registro nao esta  presente\n");
  else Ret(Ap, &T[h(x.chave, p)], &x);
}

void Imp(Lista Lista)
{ Apontador Aux;
  Aux = Lista.primeiro->prox;
  while (Aux != NULL) 
    { printf("%.*s ", N, Aux->item.chave);
      Aux = Aux->prox;
    }
}

void Imprime(Hash tabela)
{ int i;
  for (i = 0; i < M; i++) 
    { printf("%d: ", i);
      if (!Vazia(tabela[i]))
      Imp(tabela[i]);
      putchar('\n');
    }
} 
 
void LerPalavra(char *p, int Tam)
{ char c; int i, j;
  fflush(stdin); j=0;
  while (((c=getchar())!='\n') && j<Tam-1) p[j++]= c;
  p[j]='\0';
  while(c != '\n') c=getchar();
  /* Desconsiderar espacos ao final 
    da cadeia como ocorre em Pascal.*/
  for(i=j-1;(i>=0 && p[i]==' ');i--) p[i]='\0';
}

int main(int argc, char *argv[])
{ Inicializa(tabela);
  GeraPesos(p); LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Insere(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos insercao:\n");
  Imprime(tabela);
  printf("Pesquisar :  ");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { apontador = Pesquisa(elemento.chave, p, tabela);
      if (apontador == NULL) printf("pesquisa sem sucesso \n");
      else printf("sucesso \n");
      printf("Pesquisar :  ");
/*    LerPalavra(elemento.chave,6); */
      LerPalavra(elemento.chave,N);
    }
  printf("Retirar seguintes chaves:\n");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Retira(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos retiradas:\n");
  Imprime(tabela);
  printf("Inserir de novo os elementos seguintes:\n");
  LerPalavra(elemento.chave,N);
  while (strcmp(elemento.chave, "aaaaaa") != 0) 
    { Insere(elemento, p, tabela);
      LerPalavra(elemento.chave,N);
    }
  printf("tabela apos novas insxercoes:\n");
  Imprime(tabela);
  return 0;
} 
