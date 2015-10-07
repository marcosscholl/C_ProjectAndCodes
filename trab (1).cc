#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

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


//PILHA
struct pilha
{	float valor[MAX];
	int qtde;
} valor, operacao;

void pop(struct pilha &p, float v)
{	if (p.qtde < MAX) p.valor[p.qtde++] = v;
}


void inicializa(struct pilha &p)
{	p.qtde = 0;
}
//PILHA


void mostraPilha(struct pilha p)
{	int i;
	for (i = 0; (i < MAX); i++) printf("%f ",p.valor[i]);
	printf("\n");
	for (i = 0; (i < p.qtde); i++) printf("%f ",p.valor[i]);
	printf("\nq = %d\n",p.qtde);
}



void tamExpress(char str[])
{	int i, tam, tam2;
	for(i = 0; i < 26; i++) printf("Char = %c, i = %d\n", str[i], i);

	tam = strlen(str);
	printf("Tamanho Expressao%d\n", tam);

	
	
}


void calcula(char str[]) 
{	int tam, i, j;


	tam = strlen(str);

	//tam = tamExpress(str);
	//printf("Tamanho Expressao%d\n", tam);

	for ( i= 0; i < tam; i++)
	{
		if (str[i] == ')')
		{
			for (int j = i; str[j] != '('; j--)
			{
				if (str[j] == '+' || str[j] == '-' || str[j] == '*' || str[j] == '/' || str[j] == '^' )
				{	//EMPILHA OPERACAO()
					float op;
					sscanf((str+j), "%f", &op);
					pop(operacao, (int)op);
				} 
				else 
				{	//EMPILHA NUMERO
					float vlr;
					sscanf((str+j), "%f", &vlr);
					pop(valor, vlr);
				}
			}
		}
	}
}






int main()
{	int o, v, p;

	char expressao[] = "(((20+10)/2)+(4*(2+3)))";

	//inicializa(lista);
	do
	{	printf("1) inicializa    2)Calcula  3)MostraPilha_Valor  4) 3)MostraPilha_Operacoes   0) sair: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: //inicializa(lista);
			tamExpress(expressao);
					break;
			case 2: calcula(expressao);
					break;
			case 3: 
				mostraPilha(valor);
					break;
			case 4: 
				mostraPilha(operacao);
					break;

			case 8: //mostra(espressao);
					break;
		}
	}
	while (o);

	return(0);
}




