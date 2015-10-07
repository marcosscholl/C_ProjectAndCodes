#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int procura(char str[], char ref[])
{	int i, j = 0, tam, tam2, aux;
	tam = strlen(str);
	tam2 = strlen(ref);
	printf("TAM = %d\n", tam );
	printf("TAM2 = %d\n", tam2 );
	
	/*
	for (i = 0; i < tam;)
	{
		//if(str[i] == ref[0] && str[i+(ref-2)] == ref[tam2-2] &&  str[i+(tam2-1)] == str[tam-1])  printf("%d", i);
		aux=i;
		//printf("STR[i] = %c, REF[j] = %c\n",str[i], ref[j] );

		if(str[i] == ref[j] && ref[j] != '\0') 
		{	j++; printf("%c\n", str[i] );
		}

		i++;
		
			
	}
	*/

	for (; str[i] == ref[j], ref[j] != '/o'; i++, j++)
	{	
		printf("%c\n",str[i] );
	}
	
}

int main()
{	char s1[1001], s2[1001];
	strcpy(s1, "banana");
	strcpy(s2, "ana");

	printf("%d\n", procura(s1, s2));

	return(0);
	
}