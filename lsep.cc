#include <stdio.h>
#include <stdlib.h>

#define MAX 10

/**************************************************
LISTAS SIMPLESMENTE ENCADEADAS

  0   1   2   3   4
+---+---+---+---+---+
| C | A | C | B | E | INFORMAÇÃO
+---+---+---+---+---+
| -1| 3 | 3 | 0 |-1 | PROXIMO
+---+---+---+---+---+
| V | V | F | V | F | ALOCADO
+---+---+---+---+---+
Inicio = 1

A -> B -> C --
**************************************************/


struct lse
{	int informacao;
	struct lse * proximo;

} *lista = NULL;;

void inicializa(struct lse *&l)
{	struct lse *t;

	while(l != NULL)
	{
		t = l;
		l = l->proximo;
		delete(t);
	}
}


void mostra(struct lse *l)
{	struct lse *i;

	for (i = l; (i != NULL); i = i->proximo) printf("%d ",i->informacao);
	printf("\n");
	
}

char encontra(struct lse *l, int v)
{	struct lse *i;

	for (i = l; (i != NULL); i = i->proximo)
		if (i->informacao == v) return(1);
	return(0);
}

struct lse *procura(struct lse *l, int v)
{	/*
	int i;

	for (i = l.inicio; (i != -1); i = l.dado[i].proximo)
		if (l.dado[i].informacao == v) return(i);
	return(-1);
	*/
	struct lse *i;
	for (i = l; (i != NULL); i = i->proximo )
		if(i -> informacao == v) return (i);
	return (0);
}

void incluiinicio(struct lse *&l, int v)
{	struct lse * n;

	n = new (struct lse);
	n -> informacao = v;
	n -> proximo = l;
	l = n;
	/*
	{	l.dado[n].informacao = v;
		l.dado[n].proximo = l.inicio;
		l.inicio = n;
	}
	*/
}

void incluifim(struct lse *&l, int v)
{	/*int n, p;

	if ((n = aloca(l)) != -1)
	{	l.dado[n].informacao = v;
		l.dado[n].proximo = -1;
		if (l.inicio == -1) l.inicio = n;
		else
		{	for (p = l.inicio; (l.dado[p].proximo != -1); p = l.dado[p].proximo);
			l.dado[p].proximo = n;
		}
	}
	*/
	struct lse *n, *p;

	n = new (struct lse);
	n -> informacao = v;
	n -> proximo = NULL;
	if (l == NULL) l = n;  // if(l != 0)
	else
	{
		for (p = l; (l-> proximo != NULL); p = p->proximo );
			p -> proximo = n;
	}
}

void incluidepoisde(struct lse *&l, int r, int v)
{	/*
	int n, p;

	if ((p = procura(l,r)) != -1)
	{	if ((n = aloca(l)) != -1)
		{	l.dado[n].informacao = v;
			l.dado[n].proximo = l.dado[p].proximo;
			l.dado[p].proximo = n;
		}
	}
	*/
	struct lse *n, *p;
	if ((p = procura(l,r)) != NULL)
	{
		n = new (struct lse);
		n -> informacao = v;
		n -> proximo = l->proximo;
		p -> proximo = n;
	}



}

void incluiantesde(struct lse *&l, int r, int v)
{	struct lse *p, *a, *n;

	for (a = NULL, p = l; (p != NULL); a = p, p = p->proximo)
		if ( p->informacao == r)
		{	n->informacao = v;
			n->proximo = p;
			if (a == NULL) l = n;
			else a->proximo = n;
			
			break;
		}
}


void exclui(struct lse *&l, int r)
{	struct lse *p, *a;

	for (a = NULL, p = l; (p != NULL); a = p, p = p->proximo)
		if (p->informacao == r)
		{	if (a == NULL) l = p->proximo;
			else a->proximo = p->proximo;
			delete(p);
			break;
		}
}

int main()
{	int o, v, r;

	do
	{	printf(" 2)mostra 3)procura 4)incluiinicio 5)incluifim 6)incluidepoisde 7)incluiantesde 8)exclui 0)sai: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(lista);
					break;
			case 2: mostra(lista);
					break;
			case 3: printf("valor: "); scanf("%d",&v);
					printf("%sencontrado\n",(procura(lista,v) != NULL)?"":"nao ");
					break;
			case 4: printf("valor: "); scanf("%d",&v);
					incluiinicio(lista,v);
					break;
			case 5: printf("valor: "); scanf("%d",&v);
					incluifim(lista,v);
					break;
			case 6: printf("referencia: "); scanf("%d",&r);
					printf("valor: "); scanf("%d",&v);
					incluidepoisde(lista,r,v);
					break;
			case 7: printf("referencia: "); scanf("%d",&r);
					printf("valor: "); scanf("%d",&v);
					incluiantesde(lista,r,v);
					break;
			case 8: printf("referencia: "); scanf("%d",&r);
					exclui(lista,r);
					break;
		}
	}
	while (o);

	inicializa(lista); // desaloca a memorias

	return(0);
}
