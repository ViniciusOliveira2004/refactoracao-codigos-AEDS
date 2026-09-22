#include <sys/time.h>
#include<stdlib.h>
#include<stdio.h>
#define TRUE  1
#define FALSE 0
#define MAX 10

typedef int Chave;

typedef struct Registro {
  /* outros componentes */
  Chave chave;
} Registro;

typedef enum {
  Vertical, Horizontal
} Inclinacao;

typedef struct No* Apontador;

typedef struct No {
  Registro registro;
  Apontador esq, dir;
  Inclinacao BitE, BitD;
} No;

/* Efetua a rotação necessária quando ocorre desbalanceamento do tipo esquerda-esquerda. */
void EE(Apontador *Ap) { 
    Apontador Ap1;
    Ap1 = (*Ap)->esq; 
    (*Ap)->esq = Ap1->dir; 
    Ap1->dir = *Ap;
    Ap1->BitE = Vertical; 
    (*Ap)->BitE = Vertical; 
    *Ap = Ap1;
}  

/* Realiza a rotação para o caso em que o desbalanceamento ocorre na subárvore esquerda-direita. */
void ED(Apontador *Ap)
{ Apontador Ap1, Ap2;
  Ap1 = (*Ap)->esq; 
  Ap2 = Ap1->dir; 
  Ap1->BitD = Vertical;
  (*Ap)->BitE = Vertical; 
  Ap1->dir = Ap2->esq; 
  Ap2->esq = Ap1;
  (*Ap)->esq = Ap2->dir; 
  Ap2->dir = *Ap; 
  *Ap = Ap2;
}

/* Ajusta a árvore quando há uma rotação do tipo direita-direita. */
void DD(Apontador *Ap) {
    Apontador Ap1;
    Ap1 = (*Ap)->dir; 
    (*Ap)->dir = Ap1->esq; 
    Ap1->esq = *Ap;
    Ap1->BitD = Vertical; 
    (*Ap)->BitD = Vertical; 
    *Ap = Ap1;
}

/* Ajusta a árvore quando o desbalanceamento é do tipo direita-esquerda. */
void DE(Apontador *Ap)
{ Apontador Ap1, Ap2;
  Ap1 = (*Ap)->dir; Ap2 = Ap1->esq; Ap1->BitE = Vertical;
  (*Ap)->BitD = Vertical; Ap1->esq = Ap2->dir; Ap2->dir = Ap1;
  (*Ap)->dir = Ap2->esq; Ap2->esq = *Ap; *Ap = Ap2;
}

/* Insere uma chave recursivamente e reequilibra a árvore SBB conforme a inclinação dos filhos. */
void IInsere(Registro x, Apontador *Ap, 
             Inclinacao *IAp, short *Fim)
{ if (*Ap == NULL) 
  { *Ap = (Apontador)malloc(sizeof(No));
    *IAp = Horizontal;  (*Ap)->registro = x;
    (*Ap)->BitE = Vertical;  (*Ap)->BitD = Vertical;
    (*Ap)->esq = NULL; (*Ap)->dir = NULL; *Fim = FALSE;
    return;
  }
  if (x.chave < (*Ap)->registro.chave) 
  { IInsere(x, &(*Ap)->esq, &(*Ap)->BitE, Fim);
    if (*Fim) return;
    if ((*Ap)->BitE != Horizontal) { *Fim = TRUE; return; }
    if ((*Ap)->esq->BitE == Horizontal) 
    { EE(Ap); *IAp = Horizontal; return; }
    if ((*Ap)->esq->BitD == Horizontal) { ED(Ap); *IAp = Horizontal; }
    return;
  }
  if (x.chave <= (*Ap)->registro.chave) 
  { printf("Erro: Chave ja esta na arvore\n");
    *Fim = TRUE;
    return;
  }
  IInsere(x, &(*Ap)->dir, &(*Ap)->BitD, Fim);
  if (*Fim) return;
  if ((*Ap)->BitD != Horizontal) { *Fim = TRUE;  return; }
  if ((*Ap)->dir->BitD == Horizontal) 
  { DD(Ap); *IAp = Horizontal; return;}
  if ((*Ap)->dir->BitE == Horizontal) { DE(Ap); *IAp = Horizontal; }
}  

/* Interface pública para inserir um registro na árvore, encapsulando o controle de balanceamento. */
void Insere(Registro x, Apontador *Ap)
{ short Fim;  Inclinacao IAp;
  IInsere(x, Ap, &IAp, &Fim);
} 

/* Inicializa a árvore como vazia, preparando o dicionário para receber novos registros. */
void Inicializa(Apontador *Dicionario)
{ *Dicionario = NULL; }

/* Rebalanceia a árvore após a remoção de um nó na subárvore esquerda, quando a altura diminui. */
void EsqCurto(Apontador *Ap, short *Fim)
{ /* Folha esquerda retirada => arvore curta na altura esquerda */
  Apontador Ap1;
  if ((*Ap)->BitE == Horizontal) 
  { (*Ap)->BitE = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitD == Horizontal) 
  { Ap1 = (*Ap)->dir; (*Ap)->dir = Ap1->esq; Ap1->esq = *Ap; *Ap = Ap1;
    if ((*Ap)->esq->dir->BitE == Horizontal) 
    { DE(&(*Ap)->esq); (*Ap)->BitE = Horizontal;}
    else if ((*Ap)->esq->dir->BitD == Horizontal) 
         { DD(&(*Ap)->esq); (*Ap)->BitE = Horizontal; }
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitD = Horizontal;
  if ((*Ap)->dir->BitE == Horizontal) { DE(Ap); *Fim = TRUE; return; }
  if ((*Ap)->dir->BitD == Horizontal) {  DD(Ap); *Fim = TRUE; }
} 

/* Rebalanceia a árvore após a remoção de um nó na subárvore direita, quando a altura diminui. */
void DirCurto(Apontador *Ap, short *Fim)
{ /* Folha direita retirada => arvore curta na altura direita */
  Apontador Ap1;
  if ((*Ap)->BitD == Horizontal)
  { (*Ap)->BitD = Vertical; *Fim = TRUE; return; }
  if ((*Ap)->BitE == Horizontal) 
  { Ap1 = (*Ap)->esq; (*Ap)->esq = Ap1->dir; Ap1->dir = *Ap; *Ap = Ap1;
    if ((*Ap)->dir->esq->BitD == Horizontal) 
    { ED(&(*Ap)->dir); (*Ap)->BitD = Horizontal; } 
    else if ((*Ap)->dir->esq->BitE == Horizontal) 
         { EE(&(*Ap)->dir); (*Ap)->BitD = Horizontal;}
    *Fim = TRUE;
    return;
  }
  (*Ap)->BitE = Horizontal;
  if ((*Ap)->esq->BitD == Horizontal) { ED(Ap); *Fim = TRUE; return; }
  if ((*Ap)->esq->BitE == Horizontal) { EE(Ap); *Fim = TRUE; }
}  

/* Busca o predecessor in-order de um nó para substituir o valor removido sem quebrar a ordem da árvore. */
void Antecessor(Apontador q, Apontador *r, short *Fim)
{ if ((*r)->dir != NULL) 
  { Antecessor(q, &(*r)->dir, Fim);
    if (!*Fim) DirCurto(r, Fim);
    return;
  }
  q->registro = (*r)->registro; q = *r; *r = (*r)->esq; free(q);
  if (*r != NULL) *Fim = TRUE;
} 

/* Remove recursivamente uma chave e reaplica as rotações necessárias para manter a árvore equilibrada. */
void IRetira(Registro x, Apontador *Ap, short *Fim)
{ No *Aux;
  if (*Ap == NULL) 
  { printf("Chave nao esta na arvore\n"); *Fim = TRUE; return; }
  if (x.chave < (*Ap)->registro.chave) 
  { IRetira(x, &(*Ap)->esq, Fim);
    if (!*Fim) EsqCurto(Ap, Fim);
    return;
  }
  if (x.chave > (*Ap)->registro.chave) 
  { IRetira(x, &(*Ap)->dir, Fim);
    if (!*Fim) DirCurto(Ap, Fim);
    return;
  }
  *Fim = FALSE; Aux = *Ap;
  if (Aux->dir == NULL) 
  { *Ap = Aux->esq;  free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  if (Aux->esq == NULL) 
  { *Ap = Aux->dir; free(Aux);
    if (*Ap != NULL) *Fim = TRUE;
    return;
  }
  Antecessor(Aux, &Aux->esq, Fim);
  if (!*Fim) EsqCurto(Ap, Fim); /* Encontrou chave */
} 

/* Interface pública para remoção de um registro, ocultando a implementação recursiva interna. */
void Retira(Registro x, Apontador *Ap)
{ short Fim;
  IRetira(x, Ap, &Fim);
} 

/* Procura um registro pela chave e o retorna caso esteja presente na árvore. */
void Pesquisa(Registro *x, Apontador *p)
{ if (*p == NULL) 
  { printf("Erro: Registro nao esta presente na arvore\n");
    return;
  }
  if (x->chave < (*p)->registro.chave) 
  { Pesquisa(x, &(*p)->esq);
    return;
  }
  if (x->chave > (*p)->registro.chave)
  Pesquisa(x, &(*p)->dir);
  else
  *x = (*p)->registro;
}

/* Verifica se todas as folhas da árvore estão no mesmo nível e se a altura está correta. */
void Testa1(Apontador p, int nivel, int *NivelFolhas, short *PrimeiraFolha)
{ if (p == NULL)
  return;
  if (*PrimeiraFolha) 
  if (*NivelFolhas < nivel) *NivelFolhas = nivel;
  if (p->esq == NULL && p->dir == NULL) 
  { if (*PrimeiraFolha == TRUE)
    *PrimeiraFolha = FALSE;
    else 
    { if (nivel != *NivelFolhas) 
      { printf("Erro: Folhas em niveis diferentes\n"); exit(1); }
    }
  }
  if (p->BitE == Horizontal)
  Testa1(p->esq, nivel, NivelFolhas, PrimeiraFolha);
  else
  Testa1(p->esq, nivel + 1, NivelFolhas, PrimeiraFolha);
  if (p->BitD == Horizontal)
  Testa1(p->dir, nivel, NivelFolhas, PrimeiraFolha);
  else
  Testa1(p->dir, nivel + 1, NivelFolhas, PrimeiraFolha);
}  

/* Confere a ordem das chaves para garantir que a árvore continua sendo uma BST. */
void Testa2(Apontador p, int *NivelFolhas, short *PrimeiraFolha)
{ if (p == NULL)
  return;
  if (p->esq != NULL) 
  { if (p->registro.chave < p->esq->registro.chave) 
    { printf("Erro: %d < que filho a esquerda \n", p->registro.chave);
      exit(1);
    }
    Testa2(p->esq, NivelFolhas, PrimeiraFolha);
  }
  if (p->dir == NULL)
  return;
  if (p->registro.chave > p->dir->registro.chave) 
  { printf("Erro: %d > que filho a direita \n", p->registro.chave);
    exit(1);
  }
  Testa2(p->dir, NivelFolhas, PrimeiraFolha);
}  

/* Executa as validações de integridade da árvore SBB após inserções ou remoções. */
void Testa(Apontador Arvore)
{ int NivelFolhas = 0;
  short PrimeiraFolha = TRUE;
  Testa1(Arvore, 1, &NivelFolhas, &PrimeiraFolha);
  Testa2(Arvore, &NivelFolhas, &PrimeiraFolha);
} 

/* Gera um número aleatório no intervalo [0,1) para auxiliar na permutação de chaves. */
double rand0a1() {
  double resultado = (double) rand() / RAND_MAX; /* Dividir pelo maior inteiro */
  if (resultado > 1.0) resultado = 1.0;
  return resultado;
}

/* Cria uma permutação aleatória dos números de 1 até n para testar inserções e remoções. */
void Permut(int *A, int n)
{ /* Obtem permutacao randomica dos numeros entre 1 e n */
  int  i, j, b;
  for (i = n; i >= 1; i--) 
  { j = (int)(i * rand0a1()  + 1); b = A[i - 1];
    A[i - 1] = A[j - 1]; A[j - 1] = b;
  }
}

/* Função principal: gera chaves, realiza inserções/remoções e valida a integridade da árvore. */
int main(int argc, char *argv[])
{ Apontador  Dicionario;
  Registro x;
  int  vetor[MAX];
  int i, j, k, n;
  struct timeval semente;
  Inicializa(&Dicionario);
  /* Gera uma permutacao aleatoria de chaves entre 1 e MAX */

  /* utilizar o tempo como semente para a funcao srand()   */
  gettimeofday(&semente,NULL); 
  srand((int)(semente.tv_sec + 1000000*semente.tv_usec));  

  for (i = 1; i <= MAX; i++)
    vetor[i-1] = i;
  Permut(vetor, MAX);

  /* Insere cada chave na arvore e testa sua integridade apos cada insercao */
  for (i = 1; i <= MAX; i++) 
  { x.chave = vetor[i-1];
    Insere(x, &Dicionario);
    printf("Inseriu chave: %d\n", x.chave);
    Testa(Dicionario);
  }

  /* Retira uma chave aleatoriamente e realiza varias pesquisas */
  for (i = 1; i <= MAX; i++) 
    { k = 1 + (int)((float)MAX * rand() / (RAND_MAX + 1.0));
      n = vetor[k - 1];
      x.chave = n;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %d\n", x.chave);
      for (j = 1; j <= MAX; j++) 
      { x.chave = vetor[(int)((float)MAX * rand()/(RAND_MAX + 1.0))];
        if (x.chave != n) 
        { printf("Pesquisando chave: %d\n", x.chave);
          Pesquisa(&x, &Dicionario);
        } 
      }
      x.chave = n;
      Insere(x, &Dicionario);
      printf("Inseriu chave: %d\n", x.chave);
      Testa(Dicionario);
    }
  /* Retira a raiz da arvore ate que ela fique vazia */
  for (i = 1; i <= MAX; i++) 
    { x.chave = Dicionario->registro.chave;
      Retira(x, &Dicionario);
      Testa(Dicionario);
      printf("Retirou chave: %d\n", x.chave);
    }
  return 0;
}
/* End. */