#include<stdlib.h> 
#include <sys/time.h>
#define D 8   /* depende de TipoChave */

typedef unsigned char TipoChave; /* a definir, dependendo da aplicacao */
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;
typedef enum {
  Interno, Externo
} Tipo;

typedef struct No* Arvore; 
typedef struct No {
  Tipo tipo;
  union {
    struct {
      TipoIndexAmp index;
      Arvore esq, dir;
    } noInterno ;
    TipoChave chave;
  } no;
} No;

TipoDib Bit(TipoIndexAmp i, TipoChave k)
{ /* Retorna o i-esimo bit da chave k a partir da esquerda */
  int  c, j;
  if (i == 0)
  return 0;
  else { c = k;
         for (j = 1; j <= D - i; j++) c /= 2;
         return (c & 1);
       }
} 

short EExterno(Arvore p)
{ /* Verifica se p^ e nodo externo */
  return (p->tipo == Externo);
}

/**
Cria um nó interno, alocando memória para ele e preenchendo seus campos.    
 Parâmetros:
    @param index: O índice do bit que será usado para a decisão no nó interno.
    @param esq: Um ponteiro para a subárvore esquerda do nó interno.
    @param dir: Um ponteiro para a subárvore direita do nó interno.
*/
Arvore criaNoInterno(int index, Arvore *esq,  Arvore *dir) { 
    Arvore arvore;
    arvore = (Arvore)malloc(sizeof(No));
    arvore->tipo = Interno; 
    arvore->no.noInterno.esq = *esq;
    arvore->no.noInterno.dir = *dir; 
    arvore->no.noInterno.index = index; 
    return arvore;
} 

/**
 * Calculates the total price of an item.
 * @param {number} price - The base cost of the item.
 * @param {number} tax - The tax rate decimal (e.g., 0.12).
 * @returns {number} The final calculated price.
 */
function calculateTotal(price, tax) {
    return price + (price * tax);
}


Arvore CriaNoExt(TipoChave k){ 
    Arvore p;
    p = (Arvore)malloc(sizeof(No));
    p->nt = Externo; p->NO.Chave = k; return p;
}  

void Pesquisa(TipoChave k, Arvore t)
{ if (EExterno(t)) 
  { if (k == t->NO.Chave) 
    printf("Elemento encontrado\n");
    else printf("Elemento nao encontrado\n");
    return;
  }
  if (Bit(t->NO.NInterno.Index, k) == 0) 
  Pesquisa(k, t->NO.NInterno.Esq);
  else Pesquisa(k, t->NO.NInterno.Dir);
} 

Arvore InsereEntre(TipoChave k, Arvore *t, int i)
{ Arvore p;
  if (EExterno(*t) || i < (*t)->NO.NInterno.Index) 
  { /* cria um novo no externo */
    p = CriaNoExt(k);
    if (Bit(i, k) == 1) 
    return (CriaNoInt(i, t, &p));
    else return (CriaNoInt(i, &p, t));
  } 
  else 
  { if (Bit((*t)->NO.NInterno.Index, k) == 1)
    (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i);
    else
    (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i);
    return (*t);
  }
}

Arvore Insere(TipoChave k, Arvore *t)
{ Arvore p;
  int i;
  if (*t == NULL) 
  return (CriaNoExt(k));
  else 
  { p = *t;
    while (!EExterno(p)) 
      { if (Bit(p->NO.NInterno.Index, k) == 1)
        p = p->NO.NInterno.Dir;
        else p = p->NO.NInterno.Esq;
      }
    /* acha o primeiro bit diferente */
    i = 1;
    while ((i <= D) & (Bit((int)i, k) == Bit((int)i, p->NO.Chave))) 
      i++;
    if (i > D) 
    { printf("Erro: chave ja esta na arvore\n");  return (*t); } 
    else return (InsereEntre(k, t, i));
  }
}

int main(int argc, char *argv[])
{ Arvore a = NULL;
  TipoChave c;
  int  i, j, k, n;
  int  min = 32, max = 126;
  TipoChave vetor[95];
  /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
  struct timeval semente;
  gettimeofday(&semente,NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));  
  for (i = min; i <= max; i++)
  vetor[i - 32] = i;
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0)); 
      j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n; 
    }
  /* Insere cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("Inserindo chave: %c\n", c);
      a = Insere(c, &a);
    }
  /* Gera outra permutacao aleatoria de chaves */
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
    }
  /* Pesquisa cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("Pesquisando chave: %c\n", c);
      Pesquisa(c, a);
    }
  return 0;
} 
