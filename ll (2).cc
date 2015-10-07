#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int posicaoStart = (int)(SIZE/2);
int inicio = 0;
int fim = inicio-1; 

struct ll
{	int dado[SIZE];
	int qtde;
} lista;

void inicializa(struct ll &l)
{	int i;

	for (i = 0; (i < SIZE); i++) l.dado[i] = 0;
	inicio = posicaoStart;
	fim = inicio-1;
}

void controlaPosicao (struct ll &l, int p)
{
		if (fim-inicio > 1) 
		{	if(p < inicio) 
			{	inicio = p;
			} else if (p > fim) 
			{	fim = p;
			}
		} else if (fim-inicio == 1 )
		{	inicio = p;
			fim = inicio;
		}
}

char procura(struct ll l, int v)
{	int i;
	
	for (i = inicio; (i <= fim); i++) if (v == l.dado[i]) return(1);
	return(0);
}

int encontra(struct ll l, int v)
{	int i;
	
	for (i = inicio; (i <= fim); i++) if (v == l.dado[i]) return(i);
	return(-1);
}

void incluifim(struct ll &l, int v)
{		
	if ( (fim == SIZE-1) && (inicio != 0) ) 
	{	for (int i = inicio; (i <= fim); i++) l.dado[i-1] = l.dado[i];
		l.dado[fim] = v;
		inicio--;	
	}

	if (fim < SIZE-1) l.dado[++fim] = v;
}

void incluiinicio(struct ll &l, int v)
{	int i;	
	if (fim - inicio < SIZE-1) 
	{
		if (inicio > 0 )
		{	for (i = --inicio; (i); i--) l.dado[i] = l.dado[i-1];
			l.dado[inicio] = v;
		} 
		else if (inicio == 0) 
		{	for (i = fim; (i >= inicio); i--) l.dado[i+1] = l.dado[i];
			l.dado[0] = v;
			fim++;			
		}
	}

}


int analiza(struct ll l, int p) 
{ int i, aux1 = 0, aux2 = 0;
	for (i = p; i >= 0; i--)
	{	if(l.dado[i] != 0) aux1++;
	}
	for (i = p; i < SIZE; i++) 
	{ 	if(l.dado[i] != 0) aux2++;
	}	
	if (aux1 > aux2) 
	{	if (fim == SIZE-1) return 1;
	 	return 0;
	} 
	else if (aux1 == aux2) 
	{
		if (inicio == 0) return 0;
		if (p < ((SIZE-1)- fim) ) return 0;
		if ( (inicio - 0) < ((SIZE-1) - fim) )  return 0;
		return 1;
	} 
	else 
	{	if (inicio == 0) return 0;
		return 1;
	}		

}



void incluimeio(struct ll &l, int v, int p)
{	int i, aux;	

	if ( (fim-inicio) < SIZE-1 )
	{	
		if( (p >= inicio) && (p <= fim) ) 
		{	if (l.dado[p] == 0) 
			{
				for (i = l.qtde++; (i > p); i--) l.dado[i] = l.dado[i-1];
				l.dado[p] = v;
				controlaPosicao(l,p);
			} 
			else 
			{	aux = analiza(l, p);
				if (aux == 0)
				{	if ((p+1) < SIZE) 
					{	//printf("MOVE Á DIREITA\n");
						for (i = fim; (i >= p); i--) l.dado[i+1] = l.dado[i];
						l.dado[p] = v;
						if (p = fim) fim++;
						l.qtde++;
					}
				} 
				else 
				{	if ((p-1) > 0) 
					{						
						for (i = inicio; (i <= p); i++) l.dado[i-1] = l.dado[i];
						l.dado[p] = v;
						if (p = inicio) inicio--;
						l.qtde++;
					} 
				}
			}
		}
	}
}

int analizaExc(struct ll l, int p) 
{ int i, aux1 = 0, aux2 = 0;
		aux1 = p - inicio;
		aux2 = fim - p;

		//printf("\nAUX1 = %d\n AUX2 = %d\n",aux1, aux2 );
		if (aux1 > aux2) 
		{	return 0;
		} 
		else if (aux1 == aux2) 
		{	if ( (inicio - 0) > ((SIZE-1) - fim) )  return 0;
			else return 1;
		} 	
		else 
		{	return 1;
		}	
}



void excluiposicao(struct ll &l, int p)
{	int i, aux;

	if ( ((fim-inicio) >= 0) && ((p >= inicio) && (p <= fim)))
	{	
		if(p == inicio) 
		{	l.dado[p] = 0; 
			inicio++;
		} else if(p == fim)
		{ 
			l.dado[p] = 0; 
			fim--; 
		} else 
		{
			aux = analizaExc(l, p);
			if (aux == 0) 
			{	//printf("MOVE Á ESQUERDA\n");
				for (i = p; i < fim; i++) 
				{ 	l.dado[i] = l.dado[i+1];
				}
				l.dado[fim] = 0;
				fim--;

			} 
			else if (aux == 1)
			{	//printf("MOVE Á DIREITA\n");
				for (i = p; i >= inicio; i--) 
				{	l.dado[i] = l.dado[i-1];
				}
				l.dado[inicio] = 0;
				inicio++;
			} 
		}
	}
}

void excluivalor(struct ll &l, int v)
{	excluiposicao(l,encontra(l,v));
}

void mostra(struct ll l)
{	int i;

	for (i = 0; (i < SIZE); i++) printf("%d ",l.dado[i]);
	printf("\n");
	for (i = inicio; (i <= fim); i++) printf("%d ",l.dado[i]);
	printf("\nQtd = %d\n",fim-inicio +1);

	printf("Inicio = %d\n", inicio);
	printf("Fim = %d\n", fim);
}

int main()
{	int o, v, p;
	printf("A lista Comeca com a opção 4, IncluiInicio\n");
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

