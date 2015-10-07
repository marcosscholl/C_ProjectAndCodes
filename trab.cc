#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

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

struct no
{	float informacao;
	int proximo;
	char alocado;
};

struct lse
{	struct no dado[MAX];
	int inicio;
} valores, operacoes;










int main()
{	int o, v, p;

	char expressao[] = "( ((20+10)/2)) + (4*(2+3)))"

	inicializa(lista);
	do
	{	printf("1) inicializa    2)mostra    0) sair: ");
		scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(lista);
					break;

			case 8: mostra(lista);
					break;
		}
	}
	while (o);

	return(0);
}




