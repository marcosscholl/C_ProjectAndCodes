procura(char str[], char ref[],)
{	int i, j, tam;
tam = strlen(str);
tam2 = strlen(str);
	
	for (i = 0; i < tam; i++)
	{
		//if(str[i] == ref[0] && str[i+(ref-2)] == ref[tam2-2] &&  str[i+(tam2-1)] == str[tam-1])  printf("%d", i);

		if(str[i++] == ref[j] && ref[j] != '\0') j++;
			
	}
	
}