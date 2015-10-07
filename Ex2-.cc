#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Rotacionar r (int r) vezes um número inteiro n (int n). Se r for negativo, n deve ser rotacionado para
esquerda. Se r for positivo, n deve ser rotacionado para direita. A quantidade de dígitos de n pode ser obtida
utilizando a função log10, disponível em math.h.

*/

int main()
{	int n, r, m , c;
	printf("Numero:");
	scanf("%d", &n);
	printf("Rotacao:");
	scanf("%d", &r);

	

	int tamanhoCaracteresNumero = ((int)log10(n)+1);

	//Descobre o 1000
	for (m = 1, c = tamanhoCaracteresNumero; (--c); m *= 10);

	if (r < 0)
		for (; (r++); n = 10*(n%m)+(int)n/10);
	else
		for (; (r--); n = (n%10)*m+(int)n/10);
	printf("%d\n", n);
	return(0);
}