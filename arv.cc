struct no
{	int informacao;
	int peso;
	struct no *esquerda, *direita;
} arv1 = NULL;

void inclui(struct no *&r, int v)
{	struct no *n, *p, *a;

	n = new(struct no);
	n->informacao = v;
	n->esquerda = n->direita = NULL;	
	if (r == NULL) r = n;
	else
	{	for (a = NULL, p = r; (p != NULL); a = p, p = (v < p->informacao)?p->esquerda:p->direita);
		if (v < a->informacao) a->esquerda = n;
		else a->direita = n;
	}
}

void pre(struct no *r)
{	if (r != NULL)
	{	printf("%d ",r->informacao);
		pre(r->esquerda);
		pre(r->direita);
	}
}

void in(struct no *r)
{	if (r != NULL)
	{	in(r->esquerda);
		printf("%d ",r->informacao);
		in(r->direita);
	}
}

void pos(struct no *r)
{	if (r != NULL)
	{	pos(r->esquerda);
		pos(r->direita);
		printf("%d ",r->informacao);	
	}
}

int maior(int v1, int v2)
{	return((v1 > v2)?v1:v2));
}

int altura(struct no *r)
{	return((r == NULL)?-1:1+maior(altura(r->esquerda),altura(r->direita)));
}

void mostranivel(struct no *r, int n)
{	if (r != NULL)
	{	if (!n) printf("%d ",r->info);
		else
		{	mostranivel(r->esquerda,n-1);
			mostranivel(r->direita,n-1);
		}
	}
}

void niveis(struct no *r)
{	int n, a;

	for (n = 0, a = altura(r); (n < a); n++)
	{	mostraniveis(r,n);
		printf("  ");
	}
}

char procura(struct no *r, int v)
{	struct no *p;

	for (p = r; (p != NULL); p = (v < p->informacao)?p->esquerda:p->direita) if (v == p->informacao) return(1);
	return(0);
}

int conta(struct no *r, int v)
{	if (r == NULL) return(0);
	return((v == r->informacao)+conta(r->esquerda)+conta(r->direita));
}

int ateraiz(struct no *r, int v)
{	int s;

	if (r == NULL) return(0);
	s = (v == r->informacao)+ateraiz(r->esquerda)+ateraiz(r->direita);
	if (s) printf("%d ",r->informacao);
	return(s);
}

void exclui(struct no *&r, int v)
{	struct no *p, *a, *m;

	for (a = NULL, p = r; (p != NULL); a = p, p = (v < p->informacao)?p->esquerda:p->direita)
	{	if (p->informacao == v)
		{	if ((p->esquerda == NULL) || (p->direita == NULL))
			{	if (a == NULL) r = (p->esquerda == NULL)?p->direita:p->esquerda;
				else
				{	if (a->esquerda == p) a->esquerda = (p->esquerda == NULL)?p->direita:p->esquerda;
					else a->direita = (p->esquerda == NULL)?p->direita:p->esquerda;
				}
				delete(p);
			}
			else
			{	for (m = p->direita; (m->esquerda != NULL); m = m->esquerda);
				exclui(r,v = m->informacao);
				p->informacao = v;
			}
			break;
		}
	}
}

void peso(struct no *r)
{	if (r != NULL)
	{	peso(r->esquerda);
		peso(r->direita);
		r->peso = altura(r->direita)-altura(r->esquerda);
	}
}

int maior;
struct no *desbalanceado;

void encontra(struct no *r, int n)
{	if (r != NULL)
	{	encontra(r->esquerda,n+1);
		encontra(r->direita,n+1);
		if ((abs(r->peso) > 1) && (n > maior))
		{	maior = n;
			desbalanceado = r;
		}
	}
}

void rebalanceia(struct no *&r)
{	struct no *a, *b, *c, *f;

	peso(r);
	maior = -1;
	desbalanceado = NULL;
	encontra(r,0);
	while (desbalanceado != NULL)
	{	for (f = NULL, p = r; (p != desbalanceado); f = p, p = (desbalanceado->informacao < p->informacao)?p->esquerda:p->direita);
		a = desbalanceado;
		b = (a->peso < 0)?a->esquerda:a->direita;
		c = (b->peso < 0)?b->esquerda:b->direita;
		if (a->peso < 0)
		{	if (b->peso < 0) //LL
			else //LR
		}
		else
		{	if (b->peso < 0) //RL
			else //RR
		}
		peso(r);
		maior = -1;
		desbalanceado = NULL;
		encontra(r,0);
	}
}

