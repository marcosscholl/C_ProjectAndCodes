char tamanho(char *s)
{	int p;

	for (p = 0; (s[p]); p++);
	return(p);
}

char procura(char *s, char c) //O(n^2)
{	int p;

	for (p = 0; (p < tamanho(s)); p++)
		if (s[p] == c) return(1);
	return(-1);
}

char procura(char *s, char c) //O(2*n)
{	int p,t;

	for (t = tamanho(s),p = 0; (p < t); p++)
		if (s[p] == c) return(1);
	return(-1);
}

char procura(char *s, char c) //O(n)
{	int p;

	for (p = 0; (s[p]); p++)
		if (s[p] == c) return(1);
	return(-1);
}

char *substring(char *s, int i, int q) //ERROS!
{	int p;
	char *r = new(char[q]);
	for (p = i; (p < i+q); p++)
	{	r[p-i] = s[p];
		if (!s[p]) break;
	}
	if (r[0]) return(r)
	else
	{	delete[](r);
		return(NULL);
	}
}

char *substring(char *s, int i, int q) //O(2*n)
{	if ((i < 0) || (q <= 0)) return(NULL);	
	int t = tamanho(s);
	if (i > t) return(NULL);
	q = (i+q-1 < t)?q:t-i;
	char *r = new(char[q+1]);
	int p;
	for (p = i; (p < i+q); p++)
		r[p-i] = s[p];
	r[p-i] = 0;
	return(r);
}

int quantidade_repeticoes(char *s1, char *s2) //O(n*m)
{	int i,j,r = 0,p;

	for (j = i = 0; (s1[i]); i++)
	{	if (s1[i] == s2[j])
		{	if (!j) p = i;
			j++;
			if (!s2[j])
			{	r++;
				j = 0;
				i = p+1;
			}
		}
		else j = 0;
	}
}

