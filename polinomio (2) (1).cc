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







void mostra(Poli p){
  struct Termo *t;
   
  t = p->prox;
  while(t != p ){
    printf("%0.2f*x^%0.2f",t->coef,t->expo);
    t = t->prox;
    if(t != p )
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

void inicializa(struct Termo *&l)
{	struct Termo *t;
	l= l->prox;
	//printf("INICIALIZANDO\n");
	while(l->expo != -1)
	{	t = l;
		l = l->prox;
		//printf("T = %f\n", t->coef);
		delete(t);
	}
	//*&l = NULL;
	//l = InicializaPolinomio();
	l= new (struct Termo);
	
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
{	struct Termo *p1_a, *p2_a, *novo, *novo2, *pol;
	float aux;
	Poli novo_, novo_2;
	novo_ = InicializaPolinomio();
	novo_2 = InicializaPolinomio();
	novo = novo_;
	novo2 = novo_2;

	p1_a = p1->prox;
	p2_a = p2->prox;

/*
2*x^2+2*x^2+2*x^2 2*x^3+2*x^3+2*x^6 *
*/
	for(; p1_a->expo != -1; p1_a = p1_a->prox)
	{	for(; p2_a->expo != -1; p2_a = p2_a->prox)
		{	InsereTermo(novo, p1_a->coef*p2_a->coef, p1_a->expo + p2_a->expo);
		}
		p2_a = p2->prox;

	}
	printf("A LISTA COMO ELA É\n");
	mostra(novo_);
	printf("\n");
	//novo = novo->prox;  <<<<<

	/*
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
	}*/
		/*
		printf("novo->coef = %f  ||  novo->expo = %f\n", novo->coef, novo->expo );
		printf("novo->prox->coef = %f  ||  novo->prox->expo = %f\n", novo->prox->coef, novo->prox->expo );
		printf("novo->prox->prox->coef = %f  ||  novo->prox->prox->expo = %f\n", novo->prox->prox->coef, novo->prox->prox->expo );
		printf("novo->prox->prox->prox->coef = %f  ||  novo->prox->prox->prox->expo = %f\n", novo->prox->prox->prox->coef, novo->prox->prox->prox->expo );
		*/
		float soma = 0;
	for (pol = novo->prox; pol->expo != -1; pol = pol->prox)
	{	//soma = pol->coef;
		//printf("SOMA = %f \n", soma);
		//printf("ZZ pol->coef = %f |  pol->expo %f\n", pol->coef, pol->expo);
		while (pol->prox->expo == pol->expo && pol->expo != -1)
		{ 	
			//printf(" pol->expo = %f  ||  pol->prox->expo = %f\n",pol->expo, pol->prox->expo);
				//soma += pol->coef + pol->prox->coef;
			soma += pol->coef;
				//printf("Soma = %f\n", soma);
				//printf("Expo = %f\n", pol->expo); 
			pol = pol->prox;
		}
		if (soma != 0)
		{	//printf("INSERE SOMA, = %f\n", soma);
			InsereTermo(novo2, soma+pol->coef, pol->expo);
			//novo = novo->prox;
			soma=0;

		} else{
		InsereTermo(novo2, pol->coef, pol->expo);
			//novo = novo->prox;
			//printf("NAO EH IGUAL\n");
		}
		//printf("VAI PRO PROXIMO, soma = %f\n", soma);
		//soma = 0;
		
	}
	/*
	-0.5*x^5+2.5*x^3-2*x^2 0.5*x^5+3*x^2+4*x^0 *
	*/
	return(novo_2);
}


Poli divisao(char op, Poli p1, Poli p2)
{	
	struct Termo *p1_b, *p2_b, *p3, *p4, *p5, *p6, *novo3, *novo4, *novo5, *novo6, *pol_;
	float aux;
	Poli novo3_, novo4_, novo5_, novo6_;
	novo3_ = InicializaPolinomio();
	novo4_ = InicializaPolinomio();
	novo5_ = InicializaPolinomio();
	novo6_ = InicializaPolinomio();
	novo3 = novo3_;
	novo4 = novo4_;
	novo5 = novo5_;
	novo6 = novo6_;

	p1_b = p1->prox;
	p2_b = p2->prox;
/*
	printf("p1_b->coef = %f  ||  p1_b->expo = %f \n", p1_b->coef, p1_b->expo );
	//printf("p1_b->prox->coef = %f  ||  p1_b->prox->expo = %f \n", p1_b->prox->coef, p1_b->prox->expo );
	//printf("p1_b->prox->prox->coef = %f  ||  p1_b->prox->prox->expo = %f \n", p1_b->prox->prox->coef, p1_b->prox->prox->expo );

	printf("p2_b->coef = %f  ||  p2_b->expo = %f \n", p2_b->coef, p2_b->expo );
	//printf("p2_b->prox->coef = %f  ||  p2_b->prox->expo = %f \n", p2_b->prox->coef, p2_b->prox->expo );
	//printf("p2_b->prox->prox->coef = %f  ||  p2_b->prox->prox->expo = %f \n", p2_b->prox->prox->coef, p2_b->prox->prox->expo );
*/
	/*
1*x^2+13*x^1+2*x^0
2*x^1-1*x^0
x^2 / 2x = 0.5x

EX2:
-4*x^3+13*x^2+16*x^1-20*x^0 4*x^2+3*x^1-4*x^0 /

4*x^3 + 3*x^2 - 4*x^1 
-4*x^3+13*x^2+16*x^1-20*x^0
4*x^2+3*x^1-4*x^0

1*x^2-13*x^1+2*x^0 2*x^1-1*x^0


*/	p6 = p1;
int cont;
	float coef, expo, coefAnt, ExpoAnt;
	for (; p1_b->expo != -1; p1_b = p1_b->prox)
	{	//printf("p1_b->coef = %f || p1_b->expo = %f\n",p1_b->coef, p1_b->expo);
		coef = p1_b->coef / p2_b->coef;
			expo = p1_b->expo-p2_b->expo;
			InsereTermo(novo5, coef, expo);
			coefAnt = coef;
			ExpoAnt = expo;
			//printf("aaaaaCOEF = %f  ||  EXPO = %f\n", coef, expo );
			//printf("MOSTRA NOVO 5 = \n");
			mostra(novo5_);
			//printf("\n");
			//printf("AAACOEF = %f  ||  EXPO = %f\n", coef, expo );
		for (; p2_b->expo != -1; p2_b = p2_b->prox)
		{	//printf("p2_b->expo = %f\n", p2_b->expo);
			//printf("p1_b->coef = %f || p1_b->expo = %f\n",p1_b->coef, p1_b->expo);
			//printf("p2_b->coef = %f || p2_b->expo = %f\n",p2_b->coef, p2_b->expo);
			InsereTermo(novo3, p2_b->coef/p2_b->coef, p1_b->expo-p2_b->expo );
			//coef = p1_b->coef / p2_b->coef;
			//expo = p1_b->expo-p2_b->expo;

			//inicializa(novo4);

			//printf("BBBBCOEF = %f  ||  EXPO = %f\n", coef, expo );
			for (p3 = p2->prox; p3->expo != -1; p3 = p3->prox)
			{	//printf("p3->coef = %f | p3->expo = %f\n", p3->coef, p3->expo);
				InsereTermo(novo4, p3->coef*coef, p3->expo+expo);
				//printf("COEF = %f  ||  EXPO = %f\n", coef, expo );
				//printf("p3->coef*coef = %f, p3->expo+expo = %f\n", p3->coef*coef, p3->expo+expo);
			}
			//printf("CCCCCCOEF = %f  ||  EXPO = %f\n", coef, expo );
			InsereTermo(novo4, p3->coef*coef, p3->expo+expo);
			if(coef != coefAnt && ExpoAnt != expo)
			{
				InsereTermo(novo5, coef, expo);
			}
			
			p5 = subtracao(p6, novo4_);
			/*
			printf("NOVO POLINOMIO =\n");
			mostra(p5);
			
			printf("\n");

			printf("NOVO SUBTRACAO =\n");
			mostra(p6);
			printf(" / \n");
			mostra(novo4_);
			*/


			p6 = p5;

			inicializa(novo4);


			//printf("P5 \n");
			//mostra(p5);
			/*
			float divi, divo;
			
			for (p3 = p3->prox, p5 = p5->prox; p5->expo != -1; p5= p5->prox)
			{	cont++;
				//printf("p5->coef = %f   | p5->expo = %f \n",p5->coef, p5->expo );
				//printf("p3->coef = %f | p3->expo = %f\n", p3->coef, p3->expo);
				//InsereTermo(novo6, p5->coef, p5->expo );
				divi = p5->coef/p3->coef;
				divo=p5->expo / p2->expo;
				printf("===============================================\n");
				
				//if(divo <= 0 || divi <= 0  )
				if(p5->expo < p2->expo)
				{	InsereTermo(novo6, p5->coef, p5->expo);
						//printf("RETORNANDOOOOO\n");
						if (op == '/') return novo5_;
						//else return novo6_;
				} 
				
				//printf("DIVISAO = coef = %f  ||  EXPO = %f\n", divi, divo);
				p3 = p3->prox;
			} cont = 0;
			*/
			//if (cont = -1)
			//InsereTermo(novo6, p5->prox->coef, p5->prox->expo);
			/*
			if (p5->prox->expo < 0)
			{	printf("jajajajajajajajajajaj");
				return 0;
			}
			*/
			
			p1_b = p5->prox;
			p3 = p2->prox;
			coef = 0; expo = 0;
			printf("\n");

			//return novo4_;
			//aux = p1_b->coef / p2_b->coef;
			coef = p1_b->coef / p2_b->coef;
			expo = p1_b->expo-p2_b->expo;
			//InsereTermo(novo5, coef, expo);
			//printf("IN p1_b->coef/p2_b->coef = %f  ||  p1_b->expo-p2_b->expo = %f\n",  p1_b->coef/p2_b->coef, p1_b->expo-p2_b->expo );
			//InsereTermo(novo3, aux,p1_b->expo - p2_b->expo);
			//inicializa(novo4);
		}
		//printf("TETAAAAAAAAAAAA\n");
		
	}
	//printf("P3 = \n");
	//mostra(novo3_);
	if (op == '%') return p5;
	else return novo5_;
	
}




Poli escolha(char c, Poli p1, Poli p2){
	if (c == '+') return soma(p1, p2);
	else if (c == '-') return subtracao(p1, p2);
	else if (c == '*') return multiplicacao(p1, p2);
	else return divisao(c, p1,p2);
	//{	//printf("\n Este ser humano foi incapaz de realizar esse calculo!\n" );
	
	//}
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
			//result = divisao(op, p1, p2);;
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

