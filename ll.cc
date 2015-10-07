#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct ll
{	int dado[SIZE];
	int qtde;
} lista;

void inicializa(struct ll &l)
{	int i;

	for (i = 0; (i < SIZE); i++) l.dado[i] = 0;
	l.qtde = 0;
}

char procura(struct ll l, int v)
{	int i;
	
	for (i = 0; (i < l.qtde); i++) if (v == l.dado[i]) return(1);
	return(0);
}

int encontra(struct ll l, int v)
{	int i;
	
	for (i = 0; (i < l.qtde); i++) if (v == l.dado[i]) return(i);
	return(-1);
}

void incluifim(struct ll &l, int v)
{	if (l.qtde < SIZE) l.dado[l.qtde++] = v;
}

void incluiinicio(struct ll &l, int v)
{	int i;	

	if (l.qtde < SIZE)
	{	for (i = l.qtde++; (i); i--) l.dado[i] = l.dado[i-1];
		l.dado[0] = v;
	}
}

void incluimeio(struct ll &l, int v, int p)
{	int i;	

	if ((l.qtde < SIZE) && ((p >= 0) && (p < l.qtde)))
	{	for (i = l.qtde++; (i > p); i--) l.dado[i] = l.dado[i-1];
		l.dado[p] = v;
	}
}

void excluiposicao(struct ll &l, int p)
{	int i;

	if ((l.qtde > 0) && ((p >= 0) && (p < l.qtde)))
	{	for (i = p; (i < l.qtde-1); i++) l.dado[i] = l.dado[i+1];
		l.qtde--;
	}
}

void excluivalor(struct ll &l, int v)
{	excluiposicao(l,encontra(l,v));
}

void mostra(struct ll l)
{	int i;

	for (i = 0; (i < SIZE); i++) printf("%d ",l.dado[i]);
	printf("\n");
	for (i = 0; (i < l.qtde); i++) printf("%d ",l.dado[i]);
	printf("\nq = %d\n",l.qtde);
}

int main()
{	int o, v, p;

	inicializa(lista);
	do
	{	printf("1) inicializa 2) encontra 3) incluifim 4) incluiinicio 5) incluimeio 6) excluiposicao 7) excluivalor 8) mostra 0) sair: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(lista);
					break;
			case 2: printf("valor: ");
					scanf("%d",&v);
					printf("posicao: %d\n",encontra(lista,v));
					break;
			case 3: printf("valor: ");
					scanf("%d",&v);
					incluifim(lista,v);
					break;
			case 4: printf("valor: ");
					scanf("%d",&v);
					incluiinicio(lista,v);
					break;
			case 5: printf("valor: ");
					scanf("%d",&v);
					printf("posicao: ");
					scanf("%d",&p);
					incluimeio(lista,v,p);
					break;
			case 6: printf("posicao: ");
					scanf("%d",&p);
					excluiposicao(lista,p);
					break;
			case 7: printf("valor: ");
					scanf("%d",&v);
					excluivalor(lista,v);
					break;
			case 8: mostra(lista);
					break;
		}
	}
	while (o);

	return(0);
}

