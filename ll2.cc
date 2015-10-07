#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

struct ll
{	int dado[SIZE];
	int qtde;
} lista;

/* LISTA LINEAR IMPLEMENTADA COMO PILHA */
int excluiposicao(struct ll &l, int p)
{	int i;	
	if ((l.qtde > 0) && ((p >= 0) && (p < l.qtde)))
	{	for (i = p; (i < l.qtde-1); i++) l.dado[i] = l.dado[i+1];
		l.qtde--;
	}

}

int exclui(struct ll &p)
{	int v = p.dado[p.qtde];
	excluiposicao(p, p.qtde--);
	return(v);
}



void incluifim(struct ll &l, int v)
{	if (l.qtde < SIZE) l.dado[l.qtde++] = v;
}

void inclui(struct ll &p, int v) 
{	incluifim(p, v);
}


void inicializa(struct ll &l)
{	l.qtde = 0;
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
	{	printf("1) inicializa    2) inclui    3) exclui    5)    mostra    0) sair: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(lista);
					break;
			
			case 2: printf("valor: ");
					scanf("%d",&v);
					inclui(lista, v);
					break;
			case 3: printf("posicao: ");
					//scanf("%d",&p);
					exclui(lista);
					//excluiposicao(lista,p);
					break;

			case 8: mostra(lista);
					break;
		}
	}
	while (o);

	return(0);
}
