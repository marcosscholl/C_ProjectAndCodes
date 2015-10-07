#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Marcos Vinicius Scholl - 63789
struct no
{	int informacao;
	int peso;
	struct no *esquerda, *direita;
};


void inicializa (struct no *&r)
{	if (r!=NULL)
	 { inicializa(r->esquerda );
	   inicializa(r->direita);
	   delete(r);
	   r=NULL;
	 }
}	


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

int maiorLado(int v1, int v2)
{	return((v1 > v2)?v1:v2);
}

int altura(struct no *r)
{	return((r == NULL)?-1:1+maiorLado(altura(r->esquerda),altura(r->direita)));
}

void mostranivel(struct no *r, int n)
{	if (r != NULL)
	{	
		if (!n) printf("%d ",r->informacao);
		else
		{	mostranivel(r->esquerda,n-1);
			mostranivel(r->direita,n-1);
		}
	}
}

void niveis(struct no *r)
{	int n, a;

	for (n = 0, a = altura(r); (n < a); n++)
	{	mostranivel(r,n);
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
	return( (v == r->informacao) + conta(r->esquerda, v) + conta(r->direita, v)  );
}

int ateraiz(struct no *r, int v)
{	int s;

	if (r == NULL) return(0);
	s = (v == r->informacao)+ateraiz(r->esquerda, v)+ateraiz(r->direita, v);
	if (s) printf("%d ",r->informacao);
	return(s);
}

void exclui(struct no *&r, int v)
{	struct no *p, *a, *m, *repetido;

	for (a = NULL, p = r; (p != NULL); a = p, p = (v < p->informacao)?p->esquerda:p->direita)
	{	
		if (p->informacao == v)
		{	if ((p->esquerda == NULL) || (p->direita == NULL))
			{	if (a == NULL)	r = (p->esquerda == NULL)?p->direita:p->esquerda;
				else
					if (a->esquerda == p) a->esquerda = (p->esquerda == NULL)?p->direita:p->esquerda;
					else	a->direita = (p->esquerda == NULL)?p->direita:p->esquerda;
				delete(p);
			}
			else
			{	//usleep(10500);
				if (p->direita->informacao == v) 
				{	for (a = NULL, repetido = p; (repetido->direita != NULL && repetido->direita->informacao == v); a = repetido, repetido = repetido->direita);

					if (repetido->direita != NULL) a->direita = repetido->direita;
					if (repetido->esquerda != NULL) a->esquerda = r->esquerda;
					delete(repetido);
				}
				else 
				{	for (m = p->direita; (m->esquerda != NULL); m = m->esquerda);
					exclui(r,v = m->informacao);
					p->informacao = v;	
				}
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
{	struct no *a, *b, *c, *f, *p;

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
		{	if (b->peso < 0) 
			{ 	printf ("\n LL\n"); //LL
				a->esquerda = b->direita;
				b->direita = a;
				if (f == NULL)	r = b;
				else 
					if (f->direita == a) f->direita = b;
					else f->esquerda = b;

			}
			else
			{ 	printf ("\n LR\n"); //LR
				a->esquerda = c->direita;
				b->direita = c->esquerda;
				c->esquerda = b;
				c->direita = a;
				if (f == NULL)	r = c;
				else 
					if (f->direita == a) f->direita = c;
					else f->esquerda = c;
			}
		}
		else
		{	if (b->peso < 0)
			{ 	printf ("\n RL\n"); //RL
				b->esquerda = c->direita;
				a->direita = c->esquerda;
				c->esquerda = a;
				c->direita = b;
				if (f == NULL)	r = c;
				else 
					if (f->direita == a) f->direita = c;
					else f->esquerda = c;
			}
			else 
			{ 	printf ("\n RR\n"); //RR
				a->direita = b->esquerda;
				b->esquerda = a;
				if (f == NULL)	r = b;
				else 
					if (f->direita == a) f->direita = b;
					else f->esquerda = b;
			}
		}
		peso(r);
		maior = -1;
		desbalanceado = NULL;
		encontra(r,0);
	}
}



int main()
{	int o,r,i, v;
	struct no *arv;
	inicializa(arv);


	do
	{	printf("1)Inicializa  2)Procurar  3)Rebalanceia  4)Inserir  5)Pre  6)Pos  7)IN  8)Exclui   9)Mostra Niveis  10)Mostra Nivel  11)Mostra ate Raiz  12)ContaRepetido | 0) fim\n");
		printf("Opcao: "); scanf("%d",&o);
		switch (o)
		{	case 1: inicializa(arv);
					break;
					
			case 2: printf("numero: "); scanf("%d",&i);
					if (procura(arv,i)) printf("Encontrado\n");
					else printf("Nao encontrado\n");
					break;
					
			case 3: printf("Rebalanceia Arvore: \n");
					rebalanceia(arv);
					break;
					
			case 4: printf("informacao: \n"); scanf("%d",&i);
					inclui(arv,i);
					break;
					
			case 5: printf("Mostrando PRE: \n"); 
					pre(arv);
					break;
					
			case 6: printf("Mostrando POS: \n"); 
					pos(arv);
					break;
					
			case 7: printf("Mostrando IN: \n"); 
					in(arv);
					break;
			
			case 8: printf("Excluir referencia: \n"); scanf("%d",&v);
					exclui(arv,v);
					break;
					
			case 9: printf("\nNiveis:\n");
					niveis(arv);
					printf("\n");
					break;
					
			case 10: printf("Referencia:\n"); scanf("%d",&v);
					 mostranivel(arv, v);
					 break;
					
			case 11: printf("Mostra Ate a Raiz: \nReferencia:\n"); scanf("%d",&v);
					 ateraiz(arv,v);
					 break;

			case 12: printf("Quantidade de Repetições: \nReferencia:\n"); scanf("%d",&v);
					 printf("%d repete %d vezes!\n", v, conta(arv,v));
					 break;
		}
	}
	while (o);
	return(0);
}