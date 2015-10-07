#include <stdio.h>
#include <stdlib.h>

#define MAX 10

/**************************************************
LISTAS DUPLAMENTE ENCADEADAS

  0   1   2   3   4
+---+---+---+---+---+
| C | A | C | B | E | INFORMAÇÃO
+---+---+---+---+---+
| 3 | -1| 2 | 1 | 0 | ANTERIOR
+---+---+---+---+---+
| -1| 3 | 3 | 0 |-1 | PROXIMO
+---+---+---+---+---+
| V | V | F | V | F | ALOCADO
+---+---+---+---+---+
Inicio = 1

-- A <-> B <-> C --
**************************************************/

struct no
{	int informacao;
	int anterior, proximo;
	char alocado;
};

struct lde
{	struct no dado[MAX];
	int inicio;
} lista;

void inicializa(struct lde &l)
{	int i;	

	l.inicio = -1;
	for (i = 0; (i < MAX); i++) l.dado[i].alocado = 0;
}

int aloca(struct lde &l)
{	int i;

	for (i = 0; (i < MAX); i++)
		if (!l.dado[i].alocado)
		{	l.dado[i].alocado = 1;
			return(i);
		}
	return(-1);
}

void desaloca(struct lde &l, int p)
{	if ((p >= 0) && (p < MAX))
		if (l.dado[p].alocado)
			l.dado[p].alocado = 0;
}

void mostra(struct lde l)
{	int i;

	printf("inicio = %d\n",l.inicio);
	for (i = l.inicio; (i != -1); i = l.dado[i].proximo) printf("%d ",l.dado[i].informacao);
	printf("\n");
	for (i = 0; (i < MAX); i++) printf("%d\t",i);
	printf("\n");
	for (i = 0; (i < MAX); i++) printf("%d\t",l.dado[i].informacao);
	printf(" informacao\n");
	for (i = 0; (i < MAX); i++) printf("%d\t",l.dado[i].anterior);
	printf(" anterior\n");
	for (i = 0; (i < MAX); i++) printf("%d\t",l.dado[i].proximo);
	printf(" proximo\n");
	for (i = 0; (i < MAX); i++) printf("%d\t",l.dado[i].alocado);
	printf(" alocado\n");
}

char encontra(struct lde l, int v)
{	int i;

	for (i = l.inicio; (i != -1); i = l.dado[i].proximo)
		if (l.dado[i].informacao == v) return(1);
	return(0);
}

int procura(struct lde l, int v)
{	int i;

	for (i = l.inicio; (i != -1); i = l.dado[i].proximo)
		if (l.dado[i].informacao == v) return(i);
	return(-1);
}

void incluiinicio(struct lde &l, int v)
{	int n;

	if ((n = aloca(l)) != -1)
	{	l.dado[n].informacao = v;
		l.dado[n].anterior = -1;
		l.dado[n].proximo = l.inicio;
		if (l.inicio != -1) l.dado[l.inicio].anterior = n;
		l.inicio = n;
	}
}

void incluifim(struct lde &l, int v)
{	int n, p;

	if ((n = aloca(l)) != -1)
	{	l.dado[n].informacao = v;
		l.dado[n].proximo = -1;
		if (l.inicio == -1)
		{	l.dado[n].anterior = -1;
			l.inicio = n;
		}
		else
		{	for (p = l.inicio; (l.dado[p].proximo != -1); p = l.dado[p].proximo);
			l.dado[p].proximo = n;
			l.dado[n].anterior = p;
		}
	}
}

void incluidepoisde(struct lde &l, int r, int v)
{	int n, p;

	if ((p = procura(l,r)) != -1)
	{	if ((n = aloca(l)) != -1)
		{	l.dado[n].informacao = v;
			l.dado[n].anterior = p;
			l.dado[n].proximo = l.dado[p].proximo;
			l.dado[p].proximo = n;
			if (l.dado[n].proximo != -1) l.dado[l.dado[n].proximo].anterior = n;
		}
	}
}

void incluiantesde(struct lde &l, int r, int v)
{	int p, n;

	if ((p = procura(l,r)) != -1)
	{	if ((n = aloca(l)) != -1)
		{	l.dado[n].informacao = v;
			l.dado[n].anterior = l.dado[p].anterior;
			l.dado[n].proximo = p;
			l.dado[p].anterior = n;
			if (l.dado[n].anterior == -1) l.inicio = n;
			else l.dado[l.dado[n].anterior].proximo = n;
		}
	}
}

void incluiemordem(struct lde &, int v)
{
}

void exclui(struct lde &l, int r)
{	int p;

	if ((p = procura(l,r)) != -1)
	{	if (l.dado[p].anterior == -1) l.inicio = l.dado[p].proximo;
		else l.dado[l.dado[p].anterior].proximo = l.dado[p].proximo;
		if (l.dado[p].proximo != -1) l.dado[l.dado[p].proximo].anterior = l.dado[p].anterior;
		desaloca(l,p);
	}
}

int main()
{	int o, v, r;

	inicializa(lista);
	do
	{	printf("1)inicializa 2)mostra 3)procura 4)incluiinicio 5)incluifim 6)incluidepoisde 7)incluiantesde 8)exclui 0)sai: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(lista);
					break;
			case 2: mostra(lista);
					break;
			case 3: printf("valor: "); scanf("%d",&v);
					printf("%sencontrado\n",(procura(lista,v) != -1)?"":"nao ");
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

	return(0);
}

