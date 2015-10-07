#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static struct no *raiz= NULL;
//static struct nodo *raiz2=NULL;

static int npal=0;
static int k=0;

#define MAXPAL 100


void erro_mem(void);
typedef char boolean;

//Dicionario
struct vertice
{	char letra_INI;
	int repeticoes;
	int palavra;
	struct aresta *arestas;
	struct vertice *proximo;
} *vertice = NULL;



struct aresta
{	char letra_FIM;
	struct vertice *origem;
	struct aresta *proximo;
};


//////////////////////////
//ArvorePalvaras
struct no {
  char *valor;
  struct no *esq;
  struct no *dir;
  
};

struct nodo {
  char *valor;
  int pos;
  int peso;
  struct nodo *linha;
  struct nodo *esq;
  struct nodo *dir;
};



void insere(struct no **arvore, char *palavra)
{ 
	int res;
  
	if((*arvore)==NULL) 
	{	if (((*arvore)=(new struct no))== NULL) erro_mem();
		{	/* inicializa um novo nó */
			char *novo;
		    if ((novo = (char *)malloc( (unsigned)(strlen(palavra)+1) )) == NULL) erro_mem();
			if ( ( (*arvore)->valor = (char *)strdup(palavra) ) == NULL) erro_mem();
			(*arvore)->esq = NULL;
			(*arvore)->dir = NULL;
			npal++;
			return;
		}
	} 
    res = strcmp((*arvore)->valor, palavra );
    if (res == 0) 
    	return;
    if (res < 0) 
      	insere(&(*arvore)->dir, palavra);
    else
      	insere(&(*arvore)->esq, palavra);
}


void lista_arvore(struct no *arvore) {
	if (arvore == NULL) return;

	lista_arvore(arvore->esq);
	printf("%s, ",arvore->valor);
	lista_arvore(arvore->dir);
  
}


void erro_mem(void) {
	fprintf(stderr,"Erro: falta de memoria");
	exit(0);
}

boolean separador (char c) {
	switch(c) 
	{	case '\n': 
		case '\r':
		case '\t':
		case '.':
		case '!':
		case ',':
		case ';':
		case ':':
		case '?': 
		case '#':
		case '%':
			return 1;
		default: 
			return 0;
	}
}

boolean separador2 (char c) {
	switch(c) 
	{	case '\n': 
		case '\r':
		case '\t':
		case '.':
		case '!':
		case ',':
		case ' ':
		case ';':
		case ':':
		case '?': 
		case '#':
		case '%':
			return 1;
		default: 
			return 0;
	}
}



/////////////////////////////////////////////////////
int maiorLado(int v1, int v2)
{	return((v1 > v2)?v1:v2);
}

int altura(struct nodo *r)
{	return((r == NULL)?-1:1+maiorLado(altura(r->esq),altura(r->dir)));
}


void peso(struct nodo *r)
{	if (r != NULL)
	{	peso(r->esq);
		peso(r->dir);
		r->peso = altura(r->dir)-altura(r->esq);
	}
}

int maior;
struct nodo *desbalanceado;

void encontra(struct nodo *r, int n)
{	if (r != NULL)
	{	encontra(r->esq,n+1);
		encontra(r->dir,n+1);
		if ((abs(r->peso) > 1) && (n > maior))
		{	maior = n;
			desbalanceado = r;
		}
	}
}

void rebalanceia(struct nodo *&r)
{	struct nodo *a, *b, *c, *f, *p;

	peso(r);
	maior = -1;
	desbalanceado = NULL;
	encontra(r,0);
	while (desbalanceado != NULL)
	{	for (f = NULL, p = r; (p != desbalanceado); f = p, p = (desbalanceado->valor < p->valor)?p->esq:p->dir);
		a = desbalanceado;
		b = (a->peso < 0)?a->esq:a->dir;
		c = (b->peso < 0)?b->esq:b->dir;
		if (a->peso < 0)
		{	if (b->peso < 0) 
			{ 	//printf ("\n LL\n"); //LL
				a->esq = b->dir;
				b->dir = a;
				if (f == NULL)	r = b;
				else 
					if (f->dir == a) f->dir = b;
					else f->esq = b;

			}
			else
			{ 	//printf ("\n LR\n"); //LR
				a->esq = c->dir;
				b->dir = c->esq;
				c->esq = b;
				c->dir = a;
				if (f == NULL)	r = c;
				else 
					if (f->dir == a) f->dir = c;
					else f->esq = c;
			}
		}
		else
		{	if (b->peso < 0)
			{ 	//printf ("\n RL\n"); //RL
				b->esq = c->dir;
				a->dir = c->esq;
				c->esq = a;
				c->dir = b;
				if (f == NULL)	r = c;
				else 
					if (f->dir == a) f->dir = c;
					else f->esq = c;
			}
			else 
			{ 	//printf ("\n RR\n"); //RR
				a->dir = b->esq;
				b->esq = a;
				if (f == NULL)	r = b;
				else 
					if (f->dir == a) f->dir = b;
					else f->esq = b;
			}
		}
		peso(r);
		maior = -1;
		desbalanceado = NULL;
		encontra(r,0);
	}
}

///////////////////////////////////
///////////////////////////////////
/*GRAFO*/


struct vertice *procuravertice(struct vertice *dic, char l)
{	struct vertice *v;

	for (v = dic; (v != NULL); v = v->proximo) 
	{	if (v->letra_INI == l) 
		{	
			return(v);
		}
	}
	return(NULL);
}


struct aresta *procuraaresta(struct vertice *dic, char li, char lf)
{	struct vertice *v;
	struct aresta *a;

	if ((v = procuravertice(dic,li)) == NULL) return(NULL);
	v->repeticoes = v->repeticoes++;
	for (a = v->arestas; (a != NULL); a = a->proximo) 
	{	if (a->letra_FIM == lf) 
		{	if (lf == '#') v->palavra = v->palavra++;
			return(a);
		}
	}
	return(NULL);
}



void incluivertice(struct vertice *&dic, char letra)
{	struct vertice *n, *v;

	if ((v = procuravertice(dic,letra)) != NULL) { v->repeticoes = v->repeticoes--; return;} //Montenegro nao 
	n = new(struct vertice);
	n->letra_INI = letra;
	n->repeticoes = 0;
	n->palavra=0;
	n->arestas = NULL;
	n->proximo = dic;

	dic = n;
}

void incluiaresta(struct vertice *&dic, char letra_INI, char letra_FIM)
{	struct aresta *n;
	struct vertice *v;

	if (procuraaresta(dic, letra_INI, letra_FIM)) return;

	incluivertice(dic,letra_INI);
	if (procuraaresta(dic,letra_INI,letra_FIM) != NULL) return;
	n = new(struct aresta);
	n->letra_FIM = letra_FIM;
	n->proximo = (v = procuravertice(dic,letra_INI))->arestas;

	if (letra_INI == '#' || letra_FIM == '#'  ) v->palavra = v->palavra++;

	v->arestas = n;
}



void inicializaaresta(struct aresta *&a)
{	struct aresta *t;

	while (a != NULL)
	{	t = a;
		a = a->proximo;
		delete(t);
	}
}

void inicializavertice(struct vertice *&g)
{	struct vertice *t;

	while (g != NULL)
	{	t = g;
		g = g->proximo;
		inicializaaresta(t->arestas);
		delete(t);
	}
}


void mostra(struct vertice *g)
{	struct vertice *v;
	struct aresta *a;

	for (v = g; (v != NULL); v = v->proximo)
	{	printf("%c: ",v->letra_INI);
		for (a = v->arestas; (a != NULL); a = a->proximo) printf("%c ->", a->letra_FIM);
		printf("\n");
	}
}


void scan(struct vertice *&dic) {
	char palavra[MAXPAL];
	//FILE *f;
	char ch ;
	int i;

	FILE *arquivo;

	char continua=' ';

	char atual, prox;
	int x = 0; 
  
	if((arquivo=fopen("texto.txt","r"))==NULL) {
		fprintf(stderr,"Erro: nao posso abrir o ficheiro!\n");
		exit(0);
	}

	//Montando Dicionario
	while (1){

		while (1) {
			ch = fgetc(arquivo);
			if (!separador(ch) || ch==EOF) break;
		}
		if (ch == EOF) break;
		palavra[0]=ch;
		for(i = 1; i < sizeof(palavra); i++) {
		   atual = ch;
    	   prox = ch = fgetc(arquivo);

		   if (separador(ch) || ch==EOF) break;
		   
		   if (prox == ' ') prox = '#';
    	   incluiaresta(dic, atual, prox);
		   palavra[i] = ch;

			if (ch == ' ') 
    		{	ch=fgetc(arquivo);
    			incluiaresta(dic, prox, ch);			
    		}
		}

	}
	fclose(arquivo);

	//Montando Arvore De Palavras
	if((arquivo = fopen("texto.txt","r")) == NULL) {
		fprintf(stderr,"Erro: nao posso abrir o ficheiro!\n");
		exit(0);
	}

	while(1){
		while(1) {
			ch = fgetc(arquivo);
			if (!separador2(ch) || ch == EOF) break;
		}

		if (ch == EOF) break;

		palavra[0]=ch;
		for(i = 1; i < sizeof(palavra); i++) {
    	   ch = fgetc(arquivo);
		   if (separador2(ch) || ch == EOF) break;
		   palavra[i] = ch;
		}
		palavra[i]='\0';
		insere(&raiz,palavra);
	}
	fclose(arquivo);
}

//////////////////////////
/* COMPACTACAO */
char bytes[300];
int tamanhoDaLista;
char bytesR[320000];

void gravaByte(char b[], FILE *a)
{   unsigned char c = 0;
    for (int i=7; i>=0; i--)
    {   if (b[i]=='1') c=c|(1<<((i-7)*-1));
    }
    fwrite(&c, sizeof(char), 1, a);
}

void preparaByte(char b[])
{   unsigned char c = 0;
    for (int i=7; i>=0; i--)
    {   if (b[i]=='1') c=c|(1<<((i-7)*-1));
    }
}

void gravaBytes(FILE *a)
{   fwrite(bytesR, sizeof(char), 1, a);
}

void gira(char b[])
{   for (int i=8; i<=strlen(b); i++)
        b[i-8] = b[i];
}


int compacta(struct vertice *dic, struct no *r)
{	

	FILE *origem, *saida;
	char palavra[MAXPAL];
	char ch ;
	int i;

	FILE *arquivo;

	char continua=' ';
    if ((origem = fopen("texto.txt", "rb")) == NULL)
    {   fprintf(stderr,"Erro: Nao posso abrir o ficheiro!\n");
        exit(0);
    }

    unsigned char chars[10000];

    saida = fopen("texto", "wt");
    tamanhoDaLista = 0;
    int lidosLista = 0;
    lidosLista = fread(chars, sizeof(char), 10000, origem);
    tamanhoDaLista = 13;
    printf("Tamanho: %d\n", tamanhoDaLista);
    fclose(origem);

    fwrite(&tamanhoDaLista, sizeof(int), 1, saida);
    printf("Gravando %s\n", "texto");
    	
    for (struct vertice *n = dic; n!= NULL; n=n->proximo)
    {   fwrite(&n->repeticoes, sizeof(int), 1, saida);
    	fwrite(&n->palavra, sizeof(char), 1, saida);
        fwrite(&n->letra_INI, sizeof(char), 1, saida);
    }

    origem = fopen("texto.txt", "rt");
    int lidos;
  
    if((arquivo = fopen("texto.txt","r")) == NULL) {
		fprintf(stderr,"Erro: Nao posso abrir o ficheiro!\n");
		exit(0);
	}
	//Lendo Lista de Palavars
	while(1){
		while(1) {
			ch = fgetc(arquivo);
			if (!separador2(ch) || ch == EOF) break;
		}

		if (ch == EOF) break;

		palavra[0]=ch;
		for(i = 1; i < sizeof(palavra); i++) {
    	   ch = fgetc(arquivo);
		   if (separador2(ch) || ch == EOF) break;
		   palavra[i] = ch;
		}

		strcat(bytes,palavra);

    	
    	while (strlen(palavra) >= 8)
        {   gira(palavra);
        }
        gravaBytes(saida);
        palavra[i]='\0';
	}
	fclose(arquivo);
    //fwrite(bytes, sizeof(char *), 1, saida);
    gravaByte(bytes, saida);
    
    if (*bytes!=0)
    {   strcat(bytes, "0000000");
        gravaByte(bytes, saida);
    }
    fclose(origem);
    fclose(saida);
    printf("> Fim!\n");
 
}



int main()
{	int o, i=0;

	FILE *arquivo;
	struct vertice *dic;


	do
	{	printf("\n1)Criando Dicionario | 0) fim\n");
		printf("Opcao: "); scanf("%d",&o);
		switch (o)
		{	case 1:
			printf("Vai fazer\n");
			
			scan(vertice);
			lista_arvore(raiz);
			printf("MOSTRANDO\n");
			dic = vertice;
			mostra(vertice);

			printf("Dicionario:\n");
			while(vertice != NULL)
			{	printf("Letra '%c', Repete: %d  || FimPalavra?= %d\n",vertice->letra_INI, vertice->repeticoes, vertice->palavra );
				vertice = vertice->proximo;
			}
			printf("\n\nCOMPACTANDOOOOO\n");
			compacta(dic,raiz);
			printf("\nCOMPACTADO\n");
			printf("\nTentei! :/\n");

			break;


		case 2:
			break;

		}
	}
	while (o);
	return(0);
}


