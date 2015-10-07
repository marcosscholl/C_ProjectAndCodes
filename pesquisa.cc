char pesquisa_sequencial_nao_ordenada1(int *v, int n, int r) //O(n)
{	int i;

	for (i = 0; (i < n); i++) if (v[i] == r) return(1);
	return(0);
}

char pesquisa_sequencial_nao_ordenada2(int *v, int n, int r) //O(n)
{	int i, j;

	for (i = 0, j = n-1; (i <= j); i++, j--) if ((v[i] == r) || (v[j] == r)) return(1);
	return(0);
}

char pesquisa_sequencial_ordenada(int *v, int n, int r) //O(n)
{	int i;

	for (i = 0; (i < n); i++)
	{	if (v[i] == r) return(1);
		if (v[i] > r) return(0);
	}
	return(0);
}

char pesquisa_binaria(int *v, int n, int r) //O(log2(n))
{	int i,f,m;

	for (i = 0, f = n-1; (i <= f); )
	{	if (v[m = (i+f)/2] == r) return(1);
		if (r < v[m]) f = m-1;
		else i = m+1;
	}
	return(0);
}

void ordenacao_bolha(int *v, int n) //O(n^2)
{	int i, j, t;	

	for (i = 0; (i < n-1); i++)
	{	for (j = 0; (j < n-1); j++)
		{	if (v[j] > v[j+1])
			{	t = v[j];
				v[j] = v[j+1];
				v[j+1] = t;
			}
		}
	}
}

void ordenacao_selecao_direta(int *v, int n) //O((n^2+n)/2)
{	int i, j, m, t;

	for (i = 0; (i < n-1); i++)
	{	for (j = i+1, m = i; (j < n), j++) if (v[j] < v[m]) m = j;
		t = v[m];
		v[m] = v[i];
		v[i] = t;
	}
}

//quicksort O(n*log(n))

