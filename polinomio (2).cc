#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Termo{
    float coef;
    float expo;
    struct Termo * prox;
};

typedef struct Termo* Poli;



void inicializa(struct Termo *&l)
{	struct Termo *t;

	while(l->prox != l)
	{	t = l;
		l = l->prox;
		delete(t);
	}
	l = NULL;
}




void mostra(Poli p){
  struct Termo *t;
   
  t = p->prox;
  while(t != p){
    printf("%0.2f*x^%0.2f",t->coef,t->expo);
    t = t->prox;
    if(t != p)
    { if(t->coef >= 0.0) printf(" + ");
      else printf(" ");
    }
  }
  printf("\n");
}


Poli InicializaPolinomio(){
  struct Termo *p;
  p = new (struct Termo);
  p->coef = 0.0;
  p->expo = -1;
  p->prox = p;
  return p;
}


void InsereTermo(Poli p, float coef, float expo)
{	int aux = 1;
	
	struct Termo *t, *at,*n;

	n = new (struct Termo);
	n->coef = coef;
	n->expo = expo;
	
	//insere entre at e t o novo
	at = p;
	t = p->prox;
  
	//Ordena Maior -> Menor
	while(expo < t->expo )
  	{   at = t;
  		t = t->prox;

   		if (t == p)
	    {	aux = 0;
	    }
  	}
	n->prox = t; // t menos que n;
	at->prox = n; //Maior que n

	//Ordena Maior p/ menor
	/*
	  printf("\n");
	  printf("At->coef = %f  |  At->expo = %f  \n",at->coef, at->expo );
	  printf(">> N->coef = %f  |  N->expo = %f  \n",n->coef, n->expo );
	  printf("t->coef = %f  |  t->expo = %f  \n",t->coef, t->expo );
	*/
	if(aux) return;

}

Poli geraPolinomio(char str[])
{	
	int i = 0, n, tam;
	
	char c;
	float coef = 0.0, expo = 0.0, sinal = 1.0;
	Poli p;
	p = InicializaPolinomio();

	while (str[i])
	{	sscanf(str+i, " %f * x ^ %f %n",&coef, &expo, &n);
		i += n;
		InsereTermo(p, coef, expo);

		sscanf(str+i,"%c %n",&c,&n);
		
		if (c == '-')
		{	//i += n;
		} 


	}
	return p;
}


Poli soma(Poli p1, Poli p2)
{
	struct Termo *p1_a, *p2_a, *novo;
	float aux;
	Poli novo_;
	novo_ = InicializaPolinomio();
	novo = novo_;

	p1_a = p1->prox;
	p2_a = p2->prox;

	while (p1_a->expo != -1 || p2_a->expo != -1)
	{	if (p1_a->expo > p2_a->expo)
		{	InsereTermo(novo, p1_a->coef, p1_a->expo);
			novo = novo->prox;
			p1_a =  p1_a->prox;
		}
		else if (p1_a->expo < p2_a->expo)
		{	InsereTermo(novo, p2_a->coef, p2_a->expo);
			novo = novo->prox;
			p2_a = p2_a->prox;
		}
		else
		{ /* p1_a->expo == p2_a->expo */
	      	aux = p1_a->coef + p2_a->coef;
	        InsereTermo(novo, aux, p2_a->expo);
	        novo = novo->prox;
	      	p1_a = p1_a->prox;
	      	p2_a = p2_a->prox;
	    }
	}
	return novo_;

}


Poli subtracao(Poli p1, Poli p2)
{	struct Termo *p1_a, *p2_a, *novo;
	float aux;
	Poli novo_;
	novo_ = InicializaPolinomio();
	novo = novo_;

	p1_a = p1->prox;
	p2_a = p2->prox;

	while (p1_a->expo != -1 || p2_a->expo != -1)
	{	p2_a->coef = -p2_a->coef;
		if(p1_a->expo > p2_a->expo)
		{	InsereTermo(novo, p1_a->coef, p1_a->expo);
			p1_a = p1_a->prox;
			novo = novo->prox;
			
		}
		else if (p1_a->expo < p2_a->expo)
		{	InsereTermo(novo, p2_a->coef, p2_a->expo);
			novo = novo->prox;
			p2_a = p2_a->prox;
		}
		else 
		{	 aux = p1_a->coef + p2_a->coef;
			
			if (aux > 0 || aux < 0)
			{	InsereTermo(novo, aux, p1_a->expo);
				novo = novo->prox;
			}
				p1_a = p1_a->prox;
				p2_a = p2_a->prox;
		}


	}
	
	return (novo_);
/*
P(x) – Q(x) = (10x6 + 7x5 – 9x4 – 6x3 + 13x2 – 4x + 11) – (– 3x6 + 4x5 – 3x4 +2x3 + 12x2 + 3x + 15)
P(x) – Q(x) = 10x6 + 7x5 – 9x4 – 6x3 + 13x2 – 4x + 11 + 3x6 – 4x5 + 3x4 – 2x3 – 12x2 – 3x – 15
P(x) – Q(x) = 13x6 + 3x5 – 6x4 – 8x3 + x2 – 7x – 4
*/
/*
10*x^6+7*x^5-9*x^4-6*x^3+13*x^2-4*x^1+11*x^0 -3*x^6+4*x^5-3.0*x^4+2*x^3+12*x^2+3*x^1+15*x^0 -
*/
}

/*
-2*x^2-0.5*x^5+2.5*x^3 3*x^2+0.5*x^5+4*x^0 * 
0.25*x^10.00 + 1.25*x^8.00 + 0.50*x^7.00 + 9.50*x^5.00 -6.00*x^4.00 + 10.00*x^3.00 -8.00*x^2.00
*/
Poli multiplicacao(Poli p1, Poli p2)
{	struct Termo *p1_a, *p2_a, *novo, *novo2;
	float aux;
	Poli novo_, novo_2;
	novo_ = InicializaPolinomio();
	novo_2 = InicializaPolinomio();
	novo = novo_;
	novo2 = novo_2;

	p1_a = p1->prox;
	p2_a = p2->prox;


	for(; p1_a->expo != -1; p1_a = p1_a->prox)
	{	for(; p2_a->expo != -1; p2_a = p2_a->prox)
		{	InsereTermo(novo, p1_a->coef*p2_a->coef, p1_a->expo + p2_a->expo);
		}
		p2_a = p2->prox;

	}
	//mostra(novo_);
	novo = novo->prox; 
	
	for(; novo->expo != -1; )
	{	if(novo->expo == novo->prox->expo)
		{	if(novo->prox->expo == novo->prox->prox->expo)
			{	InsereTermo(novo2, novo->coef + novo->prox->coef + novo->prox->prox->expo, novo->expo);
				novo = novo->prox->prox;
			} 
			else
			{	InsereTermo(novo2, novo->coef + novo->prox->coef, novo->expo);
				novo = novo->prox;
			}
		}
		else
		{	InsereTermo(novo2, novo->coef, novo->expo);
		}
		novo = novo->prox;	
	}
	
	return(novo_2);
}

Poli escolha(char c, Poli p1, Poli p2){
	if (c == '+') return soma(p1, p2);
	else if (c == '-') return subtracao(p1, p2);
	else if (c == '*') return multiplicacao(p1, p2);
	else printf("\n Este ser humano foi incapaz de realizar esse calculo!\n" );
}

int main (){
    int o;
    char str1[MAX];
    char str2[MAX];
    char op;
    Poli p1, p2, result;
    p1 = InicializaPolinomio();
    p2 = InicializaPolinomio();
    result = InicializaPolinomio();


     do
    {   printf("1)InsereExpressão    2)Calcula   3)Mostra 5) inicializa  0) sair: ");
        scanf("%d",&o);
        switch (o)
        {   case 1: 
            printf("Insere Expressão\n");
            printf("Primeiro Polinomio\n");
            scanf("%s",str1 );
            p1 = geraPolinomio(str1);

            printf("Segundo Polinomio\n");
            scanf("%s",str2 );
            p2 = geraPolinomio(str2);


            printf("Operação\n");
			scanf("\n%c", &op );
			printf("%c\n", op );

			printf("MOSTRA OS POLINOMIOS\n");
			mostra(p1);
			mostra(p2);
			printf("\n");
			//result = soma(p1, p2);
			//result = subtracao(p1, p2);
			//result = multiplicacao(p1, p2);
			printf("Resultado:\n");
			//mostra(result);
			mostra(escolha(op, p1, p2));
			



			
			
			
                    break;

            case 2: //calcula(expressao);
                    break;
            case 3: 
            mostra(result);
            //mostra(pol2);
            		break;
        }

    }	
    while (o);
    //inicializa(p1);
    //inicializa(p2);
    return 0;
}

