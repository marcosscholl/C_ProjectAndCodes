#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int posicaoStart = 5;
int inicio = 5;
int fim = inicio-1; 

struct ll
{	int dado[SIZE];
	int qtde;
} lista;

void inicializa(struct ll &l)
{	int i;

	for (i = 0; (i < SIZE); i++) l.dado[i] = 0;
	l.qtde = 0;
}

void controlaPosicao (struct ll &l, int p)
{
		if (l.qtde > 1) {
			if(p < inicio) {
				inicio = p;
			} else if (p > fim) {
				fim = p;
			}
		} else if (l.qtde == 1 ){
			inicio = p;
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
{	//if (l.qtde < SIZE) l.dado[l.qtde++] = v;
	
	if ( (fim == SIZE-1) && (inicio != 0) ) 
	{
		for (int i = inicio; (i <= fim); i++) l.dado[i-1] = l.dado[i];
			l.dado[fim] = v;
			inicio--;
			
	}

	if (fim < SIZE-1) l.dado[++fim] = v;
	/*if (fim == SIZE) {
		int i, p = SIZE-1;
		for (i = inicio; (i <= p); i++) l.dado[i-1] = l.dado[i];
			l.dado[p] = v;
			if (p = inicio) inicio--;
			//l.qtde++;
	}
	l.qtde = fim - inicio;
	*/
	//controlaPosicao(l, fim++);
}

void incluiinicio(struct ll &l, int v)
{	int i;	
if (fim - inicio < SIZE-1) {
	if (inicio > 0 )
	{	
		//if ( (inicio <= fim)) {
			for (i = --inicio; (i); i--) l.dado[i] = l.dado[i-1];
			l.dado[inicio] = v;
			//inicio = p;
			//controlaPosicao(l, inicio);
			
		//} 
	} else if (inicio == 0) {
			for (i = fim; (i >= inicio); i--) l.dado[i+1] = l.dado[i];
				l.dado[0] = v;
				fim++;
			//if (p = inicio) inicio--;
			// CORRIGIR O FIM
			
	}
}

}


int analiza(struct ll l, int p) 
{ int i, aux1 = 0, aux2 = 0;
	//if(l.dado[p] != 0) {
		for (i = p; i >= 0; i--)	{
			if(l.dado[i] != 0) aux1++;
		}
		for (i = p; i < SIZE; i++) {
		 	if(l.dado[i] != 0) aux2++;
		}	
		//printf("\nAUX1 = %d\n AUX2 = %d\n",aux1, aux2 );
		if (aux1 > aux2) {	
			if (fim == SIZE-1) return 1;
		 	return 0;
		} else if (aux1 == aux2) {
			if (inicio == 0) return 0;
			if (p < ((SIZE-1)- fim) ) return 0;
			if ( (inicio - 0) < ((SIZE-1) - fim) )  return 0;
			return 1;
		} else {
			if (inicio == 0) return 0;
			return 1;
		}		
	//}
	//return -1;
}
/*
4 100 103 102 101 5 6 7 8 9  0   0   0  10  11  12  13  14  15  20 
4 100 103 102 101 5 6 7 8 9  0   0   0  10  11  12  13  14  15  20
0  1   2   3   4  5 6 7 8 9  10  11  12 13  14  15  16  17  18  19
SE TENTAR PREENCHER A POSIÇÃO 10, NÃO PREENCHE.
0 0 0 1 1 1 1 1 1 0  0  0    0  0  0
0 1 2 3 4 5 6 7 8 9  10 11  12 13 14  15  16  17  18  19
      I         F
 3  

 14
*/


void incluimeio(struct ll &l, int v, int p)
{	int i, aux;	

	//if ((l.qtde < SIZE) && ((p >= 0) && (p < SIZE)))
	if ( (fim-inicio) < SIZE-1 )
	{	
		if( (p >= inicio) && (p <= fim) ) {
			if (l.dado[p] == 0) 
			{
				for (i = l.qtde++; (i > p); i--) l.dado[i] = l.dado[i-1];
				l.dado[p] = v;
				controlaPosicao(l,p);
			} else {
				aux = analiza(l, p);
				if (aux == 0)
				{	if ((p+1) < SIZE) {
						//printf("MOVE Á DIREITA\n");
						for (i = fim; (i >= p); i--) l.dado[i+1] = l.dado[i];
						l.dado[p] = v;
						if (p = fim) fim++;
						l.qtde++;
					}

				} else {
					if ((p-1) > 0) {
						//printf("MOVE Á ESQUERDA\n");
						for (i = inicio; (i <= p); i++) l.dado[i-1] = l.dado[i];
						l.dado[p] = v;
						if (p = inicio) inicio--;
						l.qtde++;
					} 
				}
			}
		}

		/*
		if (p >= fim) fim = p;
		printf("QTD, %d", l.qtde);
		if (l.qtde == 1)  fim = inicio;
		*/
	}
}




int analizaExc(struct ll l, int p) 
{ int i, aux1 = 0, aux2 = 0;
	//if(l.dado[p] != 0) {
		aux1 = p - inicio;
		aux2 = fim - p;
		/*
		for (i = p; i < SIZE; i++) {
		 	if(l.dado[i] != 0) aux2++;
		}	
		*/
		//printf("\nAUX1 = %d\n AUX2 = %d\n",aux1, aux2 );
		if (aux1 > aux2) {	
			//printf("Move p Direita!\n");
			//if (fim == SIZE-1) return 1;
		 	return 0;
		} else if (aux1 == aux2) {
			//if (inicio == 0) return 1;
			//if (p < ((SIZE-1)- fim) ) return 0;
			if ( (inicio - 0) > ((SIZE-1) - fim) )  return 0;
			else return 1;
		} 	else {
			return 0;
		}	
	//}
	//return -1;
}



/*
         E
 0 0 0 1 2 3 4 5 0 0 0
 0 1 2 3 4 5 6 7 0 0 0

 */

 /*
            E
0 0 0 0 5 6 7 8 9 0 
0 0 0 0 0 5 5 8 9 0 
0 1 2 3 4 5 6 7 8 9

0 0 0 0 5 6 8 9 0 0
*/


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
			//printf("TETA");
		} else 
		{
			//printf("Analizando...\n");
			aux = analizaExc(l, p);
			if (aux == 0) 
			{
				//printf("MOVE Á ESQUERDA\n");
				for (i = p; i < fim; i++) 
				{ 	//printf("l.dado[i-1] %d\n", l.dado[i-1] );
					//printf("l.dado[i] %d\n", l.dado[i] );
					l.dado[i] = l.dado[i+1];
				}
				l.dado[fim] = 0;
				fim--;

				/*
				0 1 2 3 4 5 6 7 8 9
				I   p     F
				9 1 2 3 4 8 0 0 0 0 
				    E
				0 9 1 3 4 8
				
				0 9 9 3 4 8 0 0 0 0
				*/

			} else if (aux == 1)
			{	//printf("MOVE Á DIREITA\n");
				/*
				for (i = inicio; i < p; i++) 
				{	printf("l.dado[i+1] = %d  ||  l.dado[i] = %d\n", l.dado[i+1] ,l.dado[i] );
					l.dado[i+1] = l.dado[i];
				}
				*/
				for (i = p; i >= inicio; i--) 
				{	//printf("l.dado[i+1] = %d  ||  l.dado[i] = %d\n", l.dado[i+1] ,l.dado[i] );
					l.dado[i] = l.dado[i-1];
				}
				l.dado[inicio] = 0;
				inicio++;
			} /* else 
			{	//Ve para que lado da lista, tem mais espacos sobrando
				if ( (inicio - 0) > ((SIZE-1) - fim) ) 
				{ //Tem mais espaco no Inicio, Move para esquerda;
					printf("Tem mais espaco no Inicio, Move para esquerda\n");
					for (i = p; i < fim; i++) 
					{ 	
						l.dado[i] = l.dado[i+1];
					}
					l.dado[fim] = 0;
					fim--;
				} else 
				{	//Tem mais espaco no FIM, Move para direita;
					for (i = inicio; i < p; i++) l.dado[i+1] = l.dado[i];
					l.dado[inicio] = 0;
					inicio++;
				}
				
			}
			*/
		}


		/*
		for (i = p; (i < l.qtde-1); i++) l.dado[i] = l.dado[i+1];
		l.qtde--;
		*/
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
	printf("\nq = %d\n",fim-inicio);

	printf("Inicio = %d\n", inicio);
	printf("Fim = %d\n", fim);
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

