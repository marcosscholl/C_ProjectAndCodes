#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

struct no
{	int informacao;
	int peso;
	struct no *esquerda, *direita, *centro;
}*arv=NULL;


void inicializa (struct no *&r)
{	if (r!=NULL)
	 { inicializa(r->esquerda );
	   inicializa(r->direita);
	   inicializa(r->centro);
	   delete(r);
	   r=NULL;
	 }
}	


void inclui(struct no *&r, int v)
{	struct no *n, *p, *a;

	n = new(struct no);
	n->informacao = v;
	n->esquerda = n->centro = n->direita = NULL;	
	if (r == NULL) r = n;
	else
	{	if (r->informacao == v)
	    {   if (r->centro != NULL)
	        {   for(a = NULL, p = r; (p != NULL); a = p, p = p->centro);
	            a->centro = n;
	        }else r->centro = n; 
	    }else
	        {   p = r;
	            a = p;
	            while (p != NULL)
	            {   if (a->informacao == v) break;
	                a  = p;
	                p = (v < p->informacao)?p->esquerda:p->direita;
	            }
	            if (v == a->informacao)
	            {   for (p = a, a = NULL; (p != NULL); a = p, p = p->centro);
	                a->centro = n;
	            }
	            else 
	                if (v < a->informacao) a->esquerda = n;
	                else a->direita = n;  
	        }
	}
}

void pre(struct no *r)
{	if (r != NULL)
	{	printf("%d ",r->informacao);
		pre(r->esquerda);
		pre(r->centro);
		pre(r->direita);
	}
}


void in(struct no *r)
{	if (r != NULL)
	{	
		
		in(r->esquerda);
		in(r->centro);
		printf("%d ",r->informacao);
		in(r->direita);
	}
}


void pos(struct no *r)
{	if (r != NULL)
	{	pos(r->esquerda);
		pos(r->centro);
		pos(r->direita);
		printf("%d ",r->informacao);	
	}
}

/*
int maiorLado(int v1, int v2, int v3)
{	if ((v1 >= v2) && (v1 >= v3)) return v1;
	if ((v2 >= v1) && (v2 >= v3)) return v2;
	if ((v3 >= v2) && (v3 >= v1)) return v3;
}

int altura(struct no *r)
{	return((r == NULL)?-1:1+maiorLado(altura(r->esquerda),altura(r->centro),altura(r->direita)));
}
*/
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
			mostranivel(r->centro,n-1);
			mostranivel(r->direita,n-1);
		}
	}
}

void niveis(struct no *r)
{	int n, a;

	for (n = 0, a = altura(r); (n <= a); n++)
	{	mostranivel(r,n);
		printf("\n");
	}
	printf("Altura = %d\n", altura(r) );
}

char procura(struct no *r, int v)
{	struct no *p;

	for (p = r; (p != NULL); p = (v < p->informacao)?p->esquerda:p->direita) if (v == p->informacao) return(1);
	return(0);
}

int conta(struct no *r, int v)
{	if (r == NULL) return(0);
	return( (v == r->informacao) + conta(r->esquerda, v) + conta(r->centro, v)+ conta(r->direita, v)  );
}

int ateraiz(struct no *r, int v)
{	int s;

	if (r == NULL) return(0);
	s = (v == r->informacao)+ateraiz(r->esquerda, v)+ateraiz(r->centro, v)+ateraiz(r->direita, v);
	if (s) printf("%d ",r->informacao);
	return(s);
}

/*
void exclui(struct no *&r, int v)
{	struct no *p, *a, *aux, *m;
                            
	for (a = NULL, p = r; (p != NULL); a = p, p = (v < p->informacao)?p->esquerda:p->direita)
	{	if (p->informacao == v)
        {   if ((p->esquerda == NULL) || (p->direita == NULL))
            {	if (a == NULL)
                {   for (; (p->centro != NULL); a = p, p = p->centro);
                    if (a != NULL)
                    {   a->centro = NULL;
                        break;
                    }
                    else
                        r = (p->esquerda == NULL)?p->direita:p->esquerda;
                }
                else
                {   aux = a;
                    for (a = NULL; (p->centro != NULL); a = p, p = p->centro);
                    if (a != NULL)
                    {   a->centro = NULL;
                        break;
                    }
                    a = aux;
                    if (a->esquerda == p)
                        a->esquerda = (p->esquerda == NULL)?p->direita:p->esquerda;
                    else
                        a->direita = (p->esquerda == NULL)?p->direita:p->esquerda;
                }
                delete(p);
            }    
            else
            {   for (m = p->direita, a = NULL; (m->esquerda != NULL); a = m, m = m->esquerda);
				if (m->informacao == v) 
				{	if (a == NULL) 
				        p->direita = a;
					else 
						if (a->esquerda == m) 
						    a->esquerda = (m->esquerda == NULL) ? m->direita: m->esquerda;
					delete(m);
					break; 
				}
				exclui(p, v = m->informacao);
				p->informacao = v;                
            }
        break;
        }
    }
}
*/
void exclui(struct no *&r, int v)
{	struct no *p, *a, *m, *repetido;

	for (a = NULL, p = r; (p != NULL); a = p, p = (v < p->informacao)?p->esquerda:p->direita)
	{	
		if (p->informacao == v)
		{	if ((p->esquerda == NULL) || (p->direita == NULL))
			{	if (a == NULL)	r = (p->esquerda == NULL)?p->direita:p->esquerda;
				else
				{	if (a->esquerda == p) a->esquerda = (p->esquerda == NULL)?p->direita:p->esquerda;
					else	a->direita = (p->esquerda == NULL)?p->direita:p->esquerda;
				}
				delete(p);
			}
			else
			{	//usleep(10500);
				if (p->centro != NULL) 
				{	if(p->centro->informacao == v)	
					{	for (a = NULL, repetido = p; (repetido->centro != NULL && repetido->centro->informacao == v); a = repetido, repetido = repetido->centro);
						//if (repetido->direita != NULL) a->direita = repetido->direita;
						//if (repetido->esquerda != NULL) a->esquerda = r->esquerda;
						delete(repetido);
						a->centro = NULL;
					}
				}
				else 
				{	for (m = p->direita; (m->esquerda != NULL); m = m->esquerda);
					exclui(r,v = m->informacao);
					p->informacao = v;	
				}
			}
			break;

		}
		
		/*
		if (p->informacao == v)
		{	if ((p->esquerda == NULL) || (p->direita == NULL))
			{	if (a == NULL)	r = (p->esquerda == NULL)?p->direita:p->esquerda;
				else
					if (a->esquerda == p)  a->esquerda = (p->esquerda == NULL)?p->direita:p->esquerda;
					else	a->direita = (p->esquerda == NULL)?p->direita:p->esquerda;
				delete(p);
			}
			else
			{	for (m = p->direita; (m->esquerda != NULL); m = m->esquerda);

				if (m->informacao == p->informacao)
				{	for (m = p->esquerda; (m->direita != NULL); m = m->direita);
					v = m->informacao;
					exclui(r,m->informacao);
					p->informacao = v;
				}
				else
				{	v = m->informacao;
					exclui(r,m->informacao);
					p->informacao = v;	
				}
			}
			break;
		}
		*/
		
	}
}

void peso(struct no *r)
{	if (r != NULL)
	{	peso(r->esquerda);
		peso(r->centro);
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



/*
4 100 4 50 4 150 4 100
4 100 4 50 4 150 4 25 4 75 4 125 4 175 4 20 4 30 4 70 4 80 4 120 4 130 4 170 4 180
*/

int largura( struct no *r)
{
    if( r != NULL )
    {
        return 3 + ( largura(r->esquerda) ) + ( largura(r->direita) );
    }
    return 0;
}


void imprimeNivel(struct no *r, int nivel, int realNivel, int alt)
{	nivel--;
	int final;
	//printf("ALTURA = %d\n", alt );
	if (!nivel)
	{	int a = 
		final = ((pow(2, alt-realNivel+1)*6 - 6)/2);
		//printf("REAL NIVEL = %d\n", realNivel );
		if(realNivel == 1) for (int i = 0; i <= final; i++) printf("i"); //é o primeiro
		else for (int i = 0; i < final; i++) printf("y");
		
		if (r==NULL) /*printf("xxx")*/;
		else printf("%03d", r->informacao);
		
		for (int i = 0; i < final; i++) printf("v");
		
		if(realNivel == alt+1) printf("   ");
		///*else */printf("ooo");
		
	}
	else
	{	if (r!=NULL)
	    {   imprimeNivel(r->esquerda, nivel, realNivel, alt);
	    	if (r->centro != NULL) imprimeNivel(r->centro, nivel, realNivel, alt/2);
	    	//else printf("  ");
            imprimeNivel(r->direita, nivel, realNivel, alt);
        }
	}
}

void imprime(struct no *r)
{	int i;
	int alt = altura(r);
	for(i = 1; i <= alt+1; i++)
	{	imprimeNivel(r, i, i, altura(r));
		printf("\n");
	}
}





void imprimeNo(int a, int b)
{	int i;
	for(i = 0; i < b; i++) printf("   ");
	printf("%d\n",a);
}

void imprimeArvore(struct no *r, int c)
{	if (r == NULL)
	{	imprimeNo(-1, c);
		return;
	} 
	imprimeArvore(r->direita, c+1);
	if (r->centro != NULL) imprimeArvore(r->centro, c+1);
	imprimeNo(r->informacao, c);
	//printf("%d\n",r->informacao);
	imprimeArvore(r->esquerda, c+1);
}


void imprime2 (struct  no *r, int nivel) 
{	struct no *p;
	int rep = 0;
	int i = 0;
	int repetido = 0/*conta(r, r->informacao)*/;
	if (r == NULL) return;


	if (r->centro != NULL)
	{	//printf("TEM REPETIDO\n");
		for (p = r; p != NULL; repetido++, p = p->centro);
			//printf("REPETIÇOES = %d\n", repetido );
	}
	
	//printf("NIVEL = %d\n", nivel );
	if (repetido == 0)
	{	//printf("Nao tem Repetido!\n");
		for(i = 0; i < nivel; i++)
		{	
			//printf("espaco[%d] = %d\n", i, espaco[i] );
			//printf("Nivel =%d , I = %d\n",nivel, i);
			if(i == (nivel -1)) printf("+---");
			//if(i == (nivel)) printf("+---");
			else if (nivel%2 == 0 ) printf("|   "); 
			else if (nivel%2 != 0) printf("    ");

		}
		printf("%03d \n", r->informacao);
	}
	else
	{	//printf("TEM REPETIDO\n");
		
		for (rep = 0; rep < repetido; rep++)
		{
			for (i = 0; i < nivel+rep; i++)
			{
				if(i == (nivel -1)) printf("+---");
				else if (nivel%2 == 0 ) printf("|   "); 
				else if (nivel%2 != 0) printf("    ");
			}

			printf("%03d \n", r->informacao );
		}
		
	}
	imprime2(r-> esquerda, altura(r->esquerda));
	imprime2(r->centro, altura(r->centro));
	imprime2(r->direita, altura(r->direita));


}

void mostra(struct no *r, char lado)
{	
	if(r ==NULL) return;
	int i = altura(arv) - altura(r); 
	//printf("i =%d", i);
	
	
	for(;(i--);) printf("    ");
	printf("+--");
	printf("%03d (%c)\n", r->informacao, lado);

	
	mostra(r->esquerda, 'E');
	mostra(r->centro, 'C');
	mostra(r->direita, 'D');
}






int main()
{	int o,r,i, v;
	
/*
4 100 4 50 4 150 4 25 4 75 4 125 4 175
*/
	do
	{	printf("\n1)Inicializa  2)Procurar  3)Rebalanceia  4)Inserir  5)Pre  6)Pos  7)IN  8)Exclui   9)Mostra Niveis  10)Mostra Nivel  11)Mostra ate Raiz  12)ContaRepetido 13)ImprimeArvore| 0) fim\n");
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

			case 13: printf("ARVORE IMPRESSA\n");
					 imprime(arv);
					 break;

			case 14: printf("ARVORE IMPRESSA\n");
					 imprimeArvore(arv, 0);
					 break;
			case 15: printf("ARVORE 2\n");
					 imprime2(arv, altura(arv) );
					 break;
			case 16: printf("Arvore 3\n");
					 mostra(arv, 'R');
					 break;
		}
	}
	while (o);
	inicializa(arv);
	return(0);
}


