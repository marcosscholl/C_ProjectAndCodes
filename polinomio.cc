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

/*
struct Pol2{
    float coef;
    //char var;
    float expo;
    struct Pol2 * prox;
} *Pol2 = NULL;
*/

/*
void inicializa(struct Pol *&l)
{	struct Pol *t;

	while(l != NULL)
	{
		t = l;
		l = l->prox;
		delete(t);
	}
}
*/

/*
void mostra( Poli *l)
{	struct Termo i;

	for (i = l; (i != NULL); i = i->prox) printf("%f   %f ",i->coef,  i->expo);
	printf("\n");
	
}
*/

void mostra(Poli p){
  struct Termo *t;
   
  t = p->prox;
  while(t != NULL){
    printf("%0.2f*x^%0.2f",t->coef,t->expo);
    t = t->prox;
    if(t != NULL){
      if(t->coef >= 0.0)
        printf(" + ");
      else
        printf(" ");
    }
  }
  printf("\n");
}

/*
struct Termo *AlocaTermo(){
  struct Termo *p;
  p = (struct Termo*)malloc(sizeof(struct Termo));
  if(p == NULL)
    exit(1);
  return p;
}
*/

Poli InicializaPolinomio(){
  struct Termo *p;
  //p = AlocaTermo();
  p = new (struct Termo);
  p->coef = 0.0;
  p->expo = -1;
  p->prox = NULL;
  return p;
}


void InsereTermo(Poli p, float coef, float expo)
{
  struct Termo *t, *at, *q;
  /* Aloca memória para o novo termo: */
  //q = AlocaTermo();
  //q = new (struct Termo);
  q = InicializaPolinomio();

  q->coef = coef;
  q->expo = expo;
  // Busca a posição correta para inserir o novo termo,
   //  O novo termo será inserido entre os termos apontados 
   //  por at e t.
  
  at = p;
  t = p->prox;
  /*
  while(expo < t->expo){
    at = t;
    t = t->prox;
  }
  */
  
  q->prox = t;
  at->prox = q;
  
printf("Polinomio: \n");
  mostra(p);
}

Poli geraPolinomio(char str[])
{	
	int i = 0, n, tam;
	
	char c;
	float coef = 0.0, expo = 0.0, sinal = 1.0;
	//struct Pol *p;
	Poli p;
	//p =  AlocaTermo();
	p = InicializaPolinomio();

	tam = strlen(str);
	printf("Tamanho do Polinomio = %d\n", tam );


	while (str[i] != '\0')
	{
		sscanf(str+i, " %f * x ^ %f %n",&coef, &expo, &n);
		i += n;
		InsereTermo(p, sinal*coef, sinal*expo);

		sscanf(str+i,"%c %n",&c,&n);
		
		if (c == '-')
		{	sinal = -1.0;
			i += n;
		} 

		//printf("coef = %f\n", coef);
		//printf("Expo %f\n", expo);

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

	//p1_a = p1->prox;
	p1_a = p1;
	printf("%p\n", p1->prox );

	//p2_a = p2->prox;
	p2_a = p2;
	printf("%p\n", p2->prox );
	
	printf("TETAAAA\n");
	while (p1_a->prox != NULL || p2_a->prox != NULL)
	{		printf("TETAAAA 22222222\n");

		if (p1_a->expo > p2_a->expo)
		{	printf("TETAAAA 33333333\n");
			InsereTermo(novo, p1_a->coef, p1_a->expo);
			novo = novo->prox;
			p1_a =  p1_a->prox;
			
		}
		else if (p1_a->expo < p2_a->expo)
		{	printf("TETAAAA 444444444\n");
			InsereTermo(novo, p2_a->coef, p2_a->expo);
			novo = novo->prox;
			p2_a = p2_a->prox;
		}
		else
		{	printf("TETAAAA 55555555\n");
			
			aux = p1_a->coef + p2_a->coef;
			InsereTermo(novo, aux, p1_a->expo);
			novo = novo->prox;
			p1_a = p1_a->prox;
			p2_a = p2_a->prox;
		}
		mostra(novo);
		/*
		p1_a = p1_a->prox;
		p2_a = p2_a->prox;
		*/
	}
	mostra(novo_);
	return novo_;

}
/*
2*x^2+5*x^3+1*x^0
2*x^2+5*x^3+1*x^0
*/

int main (){
    int o;
    char str1[MAX];
    char str2[MAX];
    //char * Pol2;
    char op;
    Poli p1, p2, result;
    p1 = InicializaPolinomio();
    p2 = InicializaPolinomio();
    result = InicializaPolinomio();

   // inicializa(Pol);
    // inicializa(pol2);


     do
    {   printf("1)InsereExpressão    2)Calcula   3)Mostra 5) inicializa  0) sair: ");
        scanf("%d",&o);
        switch (o)
        {   case 1: 
            printf("Insere Expressão\n");
            printf("Primeiro Polinomio\n");
            scanf("%s",str1 );
            p1 = geraPolinomio(str1);
            //printf("Polinomio: \n");
  			//mostra(p);

            printf("Segundo Polinomio\n");
            scanf("%s",str2 );
            p2 = geraPolinomio(str2);


            printf("Operação\n");
			scanf("\n%c", &op );
			printf("%c\n", op );

			printf("MOSTRA OS POLINOMIOS\n");
			mostra(p1);
			mostra(p2);
			result = soma(p1, p2);
			mostra(result);
			



			
			
			
                    break;

            case 2: //calcula(expressao);
                    break;
            case 3: 
            //mostra(pol); 
            //mostra(pol2);
            		break;
        }

    }	
    while (o);
    return 0;
}

