#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>


#define TAM 5


/*
Este algoritmo é uma versão randomizado de algoritmo de Prim .

 1.Comece com uma grade completa de paredes.
 2.Escolha uma célula, marcá-la como parte do labirinto. Adicionar as paredes da célula para a lista de parede.
 3.Enqunto existam paredes na lista:
    1.Escolha uma parede aleatório da lista. Se a célula do lado oposto não se encontra no labirinto ainda:
       1.Faça a parede de uma passagem e marcar a celula no lado oposto, como parte do labirinto.
       2.Adicionar as paredes vizinhas da célula para a lista de parede.
 
    2.Se a célula no lado oposto já estava no labirinto, remover a parede a partir da lista.

Como o algoritmo de profundidade, que geralmente vai ser relativamente fácil de encontrar o caminho para a célula inicial, 
mas difícil de encontrar o caminho de qualquer outro lugar.
Note-se que simplesmente executando Prim de clássicos em um grafo com pesos aleatórios iria criar labirintos estilisticamente 
idênticas às de Kruskal, porque ambos são algoritmos que medem o mínimo de árvores. Em vez disso, este algoritmo apresenta 
variação estilística porque as bordas mais perto do ponto de partida ter um menor peso eficaz.
*/

typedef struct paredes 
{ int parede;
} paredes;

typedef struct ListaParedes
{ 	int id;
	int parede;
} ListaParedes;

typedef struct celula 
{	int pertence;
	int id;
	
	struct paredes* paredes[6];
} Celula;


Celula* labirinto[TAM][TAM];

/*
ListaParedes* listaParedes [TAM*TAM*10];


typedef struct ListaParedes
{ 	int id;
	int parede;
} ListaParedes;
*/



struct listaParedes
{	int id;
	struct listaParedes* proximo;
	struct listaParedes* abaixo;

} *listaParedes = NULL;


struct lse
{	int id;
	int parede;
	struct lse * proximo;

} *lista = NULL;

/*
struct l
{   int id;
    struct l *proximo;
    struct l *baixo;
} 
*/

void inicializaLista(struct lse *&l)
{	struct lse *t;

	while(l != NULL)
	{
		t = l;
		l = l->proximo;
		delete(t);
	}
}


void mostra(struct lse *l)
{	struct lse *i;

	for (i = l; (i != NULL); i = i->proximo) printf("Parede Id = %d  | Parede = %d  \n",i->id, i->parede);
	printf("\n");
	
}

void incluifim(struct lse *&l, int id, int parede)
{	
	if (parede >0)
	{
		struct lse *n, *p;
		n = new (struct lse);
		n->id = id;
		n -> parede = parede;
		n -> proximo = NULL;
		if (l == NULL) l = n;  
		else
		{	
			for (p = l; (p-> proximo != NULL); p = p->proximo );
				p -> proximo = n;
		}
	}
	
}

void exclui(struct lse *&l, int id, int parede)
{	struct lse *p, *a;

	for (a = NULL, p = l; (p != NULL); a = p, p = p->proximo)
		if (p->id == id && p->parede == parede)
		{	if (a == NULL) l = p->proximo;
			else a->proximo = p->proximo;
			delete(p);
			break;
		}
}




int qtd_add = 0;
int linhaParede = 0;

void inicializa(int linha, int coluna, int id)
{	
	labirinto[linha][coluna] = (Celula*) malloc(sizeof(Celula));
	labirinto[linha][coluna]->id= id;
	

	//Alocando as Paredes
	for (int i = 0; i <= 5; i++)
	{
		labirinto[linha][coluna]->paredes[i] = (paredes*) malloc(sizeof(paredes));
	}

	labirinto[linha][coluna]->paredes[0] = (paredes*) malloc(sizeof(paredes));
	//printf("labirinto[linha][coluna]->paredes[0]->parede = %p\n", labirinto[linha][coluna]->paredes[0]);

	labirinto[linha][coluna]->paredes[0]->parede = 100;
	labirinto[linha][coluna]->paredes[1]->parede = 200;
	labirinto[linha][coluna]->paredes[2]->parede = 300;
	labirinto[linha][coluna]->paredes[3]->parede = 400;
	labirinto[linha][coluna]->paredes[4]->parede = 500;
	labirinto[linha][coluna]->paredes[5]->parede = 600;

	//Paredes EXTERNAS
	if (linha == 0)
	{
		labirinto[linha][coluna]->paredes[0]->parede = 0;
		labirinto[linha][coluna]->paredes[1]->parede = 0;
		labirinto[linha][coluna]->paredes[5]->parede = 0;
	} 
	else if (linha == TAM-1)
	{
		labirinto[linha][coluna]->paredes[2]->parede = 0;
		labirinto[linha][coluna]->paredes[3]->parede = 0;
		labirinto[linha][coluna]->paredes[4]->parede = 0;
	}

	if (coluna == 0)
	{
		labirinto[linha][coluna]->paredes[4]->parede = 0;
		labirinto[linha][coluna]->paredes[5]->parede = 0;
	} 
	else if (coluna == TAM-1)
	{	labirinto[linha][coluna]->paredes[1]->parede = 0;
		labirinto[linha][coluna]->paredes[2]->parede = 0;
		//labirinto[linha][coluna]->paredes[3]->parede = 0;
	}

	if (linha == 0 && coluna == TAM-1)
	{
		labirinto[linha][coluna]->paredes[3]->parede = 400;
	}
	if (linha > 0 && linha < TAM-1 && coluna == TAM-1)
	{
		labirinto[linha][coluna]->paredes[1]->parede = 0;
	}

	if (linha == TAM-1 && coluna == TAM-1)
	{
		labirinto[linha][coluna]->paredes[1]->parede = 0;
	}

	if (linha > 0 && linha < TAM-1 && coluna == 0)
	{	labirinto[linha][coluna]->paredes[0]->parede = 100;
		labirinto[linha][coluna]->paredes[1]->parede = 200;
		labirinto[linha][coluna]->paredes[2]->parede = 300;
		labirinto[linha][coluna]->paredes[3]->parede = 400;
		labirinto[linha][coluna]->paredes[4]->parede = 0;
		labirinto[linha][coluna]->paredes[5]->parede = 0;
	}

	
	labirinto[linha][coluna]->pertence = 0;
}


void gera()
{ 	
	
	int linha, coluna, id;
	id = 1;
		//t i = j = 0;
	for (linha = 0; linha < TAM; linha++)
	{
		for (coluna = 0; coluna < TAM; coluna++)
		{	
			inicializa(linha, coluna, id++);
		}
	}
	printf("PAREDES GERADAS\n");
	//printf("TAMANHO = %d\n", TAM*TAM*10);
	inicializaLista(lista);
	
}



int celulaRand()
{	
    int i;
    //printf("intervalo da rand: [0,%d]\n", 25);
    srand( (unsigned)time(NULL) );

    for(i=1 ; i <= TAM*TAM ; i++)
        return (1 + ( rand() % TAM*TAM ));
}

int paredeRand(int randMaximo)
{	
    int i;
    //printf("intervalo da rand: [0,%d]\n", 25);
    srand( (unsigned)time(NULL) );

    for(i=1 ; i <= 25 ; i++)
        return (1 + ( rand() % randMaximo ));
}


void desalocaMatriz()
{	int i, j;
	for(i = 0; i < TAM; i++)
		for (j = 0; j < TAM; j++)
			for (int k = 0; i <= 5; k++)
				//free(labirinto[i][j]->paredes[k]);
			free(labirinto[i][j]);
	//free(labirinto);
}



void resolveLabirinto(int i, int j, int k, int parede)
{	//printf("RESOLVE LABIRINTO\n");
	int paredeEscolhida, paredeDiagonal;
	paredeEscolhida = parede;

	int diagonalLinha =0, diagonalColuna = 0, rotacaoParede = 0, refParedesRemove =0;

	if (paredeEscolhida == 600)
	{ 	paredeDiagonal = 300;
		diagonalLinha = -1;
		diagonalColuna = -1;
		rotacaoParede = -3;
		refParedesRemove = 600-300;

	}
	 else if (paredeEscolhida == 500) 
	{	paredeDiagonal = 200;
		diagonalLinha = +1;
		diagonalColuna = -1;
		rotacaoParede = -3;
		refParedesRemove = 500-300;
	}
	else if (paredeEscolhida == 400)
	{	paredeDiagonal = 100;
		diagonalLinha = +1;
		diagonalColuna = 0;
		rotacaoParede = -3;
		refParedesRemove = 400-300;
	}	
	else if (paredeEscolhida == 300)
	{	paredeDiagonal = 600;
		diagonalLinha = +1;
		diagonalColuna = +1;
		rotacaoParede = +3;
		refParedesRemove = 300+300;
	}
	else if (paredeEscolhida == 200)
	{	paredeDiagonal = 500;
		diagonalLinha = -1;
		diagonalColuna = +1;
		rotacaoParede = +3;
		refParedesRemove = 200+300;

	}
	else if (paredeEscolhida == 100)
	{	paredeDiagonal = 400;
		diagonalLinha = -1;
		diagonalColuna = 0;
		rotacaoParede = +3;
		refParedesRemove = 100+300;
	}

	struct lse *listaParedes;
	listaParedes = lista;

	



	if (i-1 >= 0 || j-1 >= 0 || i+1 == TAM || j+1 == TAM)
	{
		if (labirinto[i][j]->paredes[k]->parede == paredeEscolhida)
		{	 //printf("PAREDE ESCOLHIDA = %d\n", paredeEscolhida );
			//verifica o oposto e adiciona o oposto
			//printf("I = %d  ||  J = %d\n", i, j);
			//printf("I-1 = %d  ||  J-1 = %d\n", i-1, j-1);

			if (labirinto[i+diagonalLinha][j+diagonalColuna]->pertence == 0)
			{ 	//printf("11\n");
				labirinto[i+diagonalLinha][j+diagonalColuna]->pertence = 1;
				for (int t = 0; t <= 5; t++)
				{		

					incluifim(lista, labirinto[i+diagonalLinha][j+diagonalColuna]->id, labirinto[i+diagonalLinha][j+diagonalColuna]->paredes[t]->parede );
					linhaParede++;
				}
				//printf("33\n");



				//Aponta as paredes para fazer passagem
				if (labirinto[i+diagonalLinha][j+diagonalColuna]->paredes[k+rotacaoParede]->parede == paredeDiagonal)
				{	//printf("44\n");
					labirinto[i][j]->paredes[k]->parede = labirinto[i+diagonalLinha][j+diagonalColuna]->id;
			        labirinto[i+diagonalLinha][j+diagonalColuna]->paredes[k+rotacaoParede]->parede = labirinto[i][j]->id;
				}
					//Ageita a lista de Paredes, removendo quem fez passagem
				//for (int x = 0; x < linhaParede; x++)
				for (listaParedes; (listaParedes != NULL); listaParedes = listaParedes->proximo )
				{//printf("55\n");
					if (listaParedes-> id == labirinto[i][j]->id)
					{	//printf("66\n");
						if (listaParedes->parede == paredeEscolhida )
						{	//listaParedes[x]->id = 0;
							//listaParedes->parede = 0;
							//printf("77\n");
							exclui(lista,listaParedes->id, listaParedes->parede );
						}
					} 
					else if (listaParedes-> id == labirinto[i+diagonalLinha][j+diagonalColuna]->id)
					{	//printf("88\n");
						if (listaParedes->parede == refParedesRemove )
						{	//listaParedes[x]->id = 0;
							//listaParedes[x]->parede = 0;
							//printf("99\n");
							exclui(lista,listaParedes->id, listaParedes->parede );
						}
					}
				}


			} 
			else
			{
				//printf("JA PERTENCE AO LABIRINTO\n");
				//for (int c = 0; c < linhaParede; c++)
				for (listaParedes; (listaParedes != NULL); listaParedes = listaParedes->proximo )
				{	
					if (listaParedes->id == labirinto[i][j]->id)
					{	//for (int t = 0; t <=5; t++)
						//{
							if(listaParedes->parede == paredeEscolhida)
							{	
								//printf("Remove da Lista\n listaParedes-> id = %d  || Parede = %d\n", listaParedes->id, listaParedes->parede );
								//	listaParedes->id = 0;
								//listaParedes->parede = 0;
								//listaParedes->parede = 0;
								exclui(lista,listaParedes->id, listaParedes->parede );
							}
							
						//}	
					}
					//printf("REMOVE AS DUAS PAREDES DA LISTA DE PAREDES E NÃO FAZ MAIS NADA\n");
					if (listaParedes->id == labirinto[i+diagonalLinha][j+diagonalColuna]->id && listaParedes->parede == refParedesRemove ) 
					{		
						//printf("REMOVE A PAREDE ID =  %d ||  PAREDE =  %d\n", labirinto[i+diagonalLinha][j+diagonalColuna]->id,refParedesRemove );
						//listaParedes->parede = 0;
						exclui(lista,listaParedes->id, listaParedes->parede );
					}
				}
			}
			//printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
			
			
		}
		
	}
	else
	{
		//printf("Não Pode sair dos limites do Labirinto!\n");
	}

}



struct paredes2 
{ 
    int id;
    
    struct paredes2* proximo;
    
} *paredes2 = NULL;

struct listaDelista 
{
    //struct celula* celula;
    int celula;
    
    struct paredes2* passagem;
    
    struct listaDelista* proximo;
} *listaDelista = NULL;




void geraListaDeLista()
{
	//struct grafo *listaGrafo;
	struct paredes2 * p2;
	struct listaDelista* listaLista, *listaAux;

	listaLista = new (struct listaDelista);

	int linha, coluna, aux;
	for (linha = 0; linha < TAM; linha++)
	{	
		for (coluna = 0; coluna < TAM; coluna++)
		{	//printf("labirinto[ %d ] [ %d ] -> ID= %d \n", linha, coluna, labirinto[linha][coluna]->id);	
			printf("\nID %d ->  ", labirinto[linha][coluna]->id);	

			

			listaLista->celula = labirinto[linha][coluna]->id;
			listaLista->proximo = new (struct listaDelista);
			p2 = new (struct paredes2);

			for (int i = 0; i <= 5; i++)
			{	
				if (labirinto[linha][coluna]->paredes[i]->parede > 0 && labirinto[linha][coluna]->paredes[i]->parede < 100)
				{	//printf("labirinto[ %d ] [ %d ] -> paredes[0]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[i]->parede);
					printf(" %d ", labirinto[linha][coluna]->paredes[i]->parede);

					p2-> id = labirinto[linha][coluna]->paredes[i]->parede;
					p2-> proximo = new (struct paredes2);
					
					listaLista->passagem = p2;

					
				}
			}
			listaLista = listaLista->proximo;


		}
	}
	struct listaDelista* i;
	for (i = listaDelista; (i != NULL); i = i->proximo)
	{	 
		printf("Parede Id = %d  | Parede =  \n", i->celula);

	}
		printf("\n");


}


void mostraListaParedes()
{	struct listaParedes* i;
	for (i = listaParedes; (i != NULL); i = i->proximo) printf("Parede Id = %d  | Parede = %d  \n", i->id, i->proximo->id);
		printf("\n");

	/*
	void mostra(struct lse *l)
	{	struct lse *i;

		for (i = l; (i != NULL); i = i->proximo) printf("Parede Id = %d  | Parede = %d  \n",i->id, i->parede);
		printf("\n");
		
	}
	*/
}


int size(struct lse *lista)
{ struct lse *listaParedes;
	int i = 0;
	for(listaParedes = lista; (listaParedes != NULL); listaParedes= listaParedes->proximo) i++;

	return i;
}


int cria()
{
	//Gera uma posição randomica e escolhe por que celula começar.
	// vamos começar com a posição 12. Linha 2 | Coluna 1
	int linha, coluna, linhaStart, colunaStart, id;
	int colunaParede, celulaStart, iteracoes = 0;
	
	struct lse *listaParedes;
	listaParedes = lista;


	

		int executa = 1;
			while(executa)
			{

		//t i = j = 0;
				
					//printf("LINHA = %d  |||  COLUNA = %d \n", linha, coluna );
		
				
				//printf("qqqqqqqqqqqqqqqqqqqqq\n");
				if (iteracoes == 0)
				{

					celulaStart = celulaRand();
					printf("CELULA RANDOMICA = %d\n", celulaStart );
					//printf("111\n");
					for (linhaStart = 0; linhaStart < TAM; linhaStart++)
					{	printf("  \n");
						for (colunaStart = 0; colunaStart < TAM; colunaStart++)
						{	//printf(" 22222222222 \n");
							if (labirinto[linhaStart][colunaStart] -> id == celulaStart)
							{	linha = linhaStart;
								coluna = colunaStart;
							}
						}
					}
					linhaStart = 0; 
					colunaStart = 0;

					if (labirinto[linha][coluna]->pertence == 0) //Celula não esta nas paredes.
					{	labirinto[linha][coluna]->pertence=1; 
						//linhaParede/* = qtd_add++*/;
						//printf("linhaParede = %d\n", linhaParede );
						
						int i,j;
						for (i = 0; i <= 5; i++)
						{	// Poem as paredes na lista de paredes.
							//printf("uuuuuuuuuuuuuuuuuuuuu\n");

							//Só executa na primeira vez
							//NÃO POSSO COLOCAR A CELULA AINDA NA LISTA
							
							if (labirinto[linha][coluna]->paredes[i]->parede >= 100)
							{	
								//listaParedes[linhaParede] = (ListaParedes*) malloc(sizeof(ListaParedes));
						        //listaParedes[linhaParede]->id = labirinto[linha][coluna]->id;
						        printf("PAREDE = %d\n", labirinto[linha][coluna]->paredes[i]->parede);
								//listaParedes[linhaParede++]-> parede = labirinto[linha][coluna]->paredes[i]->parede;
								

								incluifim(lista, labirinto[linha][coluna]->id, labirinto[linha][coluna]->paredes[i]->parede);

							}
							

						}

					iteracoes++;
					}
				}

				// Tenho que Sortear agora uma parede
				int paredeSorteada = -1;
				int paredeSorteada_id=0;
				int paredeSorteada_parede =0;
				//printf("LINHA PAREDE = %d\n", size(lista));
				/*for (int w=0;  w < size(lista); w++)
				{
					//paredeSorteada = listaParedes[paredeRand(linhaParede)]->id;
					paredeSorteada = paredeRand(size(lista));
				}
				*/
				int cont = 0;
				printf("PAREDE RANDOMICA = %d\n", paredeRand(size(lista)));
				for (listaParedes = lista; listaParedes != NULL && cont < paredeRand(size(lista)); listaParedes = listaParedes->proximo, cont++)
				{	//printf("ahisdsdsdsdsdhid\n");
					paredeSorteada_id = listaParedes->id;
					paredeSorteada_parede = listaParedes->parede;
				}

				 //paredeSorteada_id = listaParedes[paredeSorteada]->id;
				 //paredeSorteada_parede = listaParedes[paredeSorteada]->parede;

				//printf("PAREDE SORTADA = %d\n", paredeSorteada);
				printf("PAREDE SORTEADA  ID = %d\n", paredeSorteada_id);
				printf("PAREDE SORTEADA PAREDE= %d\n", paredeSorteada_parede);
				//printf("PAREDE SORTADA PAREDE= %d\n", listaParedes[paredeSorteada]->parede);
				
				//Sorteia uma parede dessa lista de paredes e remove.
				//vou remover a parede direita_Cima, fazer função para descobrir quantidade de paredes inseridas.
				int i, j;
				
				//percorre o vetor de paredes.
				//Acha uma parede e remove ela;
				//for (i = 0; i < linhaParede; i++)
				//printf("OIIIIIII\n");
				for (listaParedes = lista; (listaParedes != NULL); listaParedes = listaParedes->proximo )
				{	//printf("000000000000\n");
					//Pego aquela parede da lista de Parede
					if (listaParedes->id == paredeSorteada_id && listaParedes->parede == paredeSorteada_parede)
					{	// descobre em que linha esta parede esta para remover a parede da sua diagonal e criar o labirinto.
						//printf("TETA \n");
						for (int i = 0; i < TAM; i++)
						{
							for (int j = 0; j < TAM; j++)
							{	// se remover a parede direita cima. Tem de chegar no linha -1 e coluna -1
								// e remover a parede esquerda baixo dessa posicao
								//printf("11111111111 \n" );
								if(labirinto[i][j]->id == paredeSorteada_id)
								{	//apontando as paredes e criando passagem
										 //printf("222222222 \n" );
									//Conferindo se esta parede nao esta apontada.
									for (int k = 0; k <=5; k++)
									{	
										
										if (labirinto[i][j]->paredes[k]->parede == paredeSorteada_parede)
										{
											resolveLabirinto( i, j, k, paredeSorteada_parede);
										}
										

										

									}

									

								}
							}
						}
					}
					linha = 0; coluna = 0;
				}

				executa=0;
				
				executa = size(lista);
				printf("\nEXECUTA = %d\n", executa);
				
				

			}//fim do While
			geraListaDeLista();

}




void mostraLabirinto()
{	int linha, coluna;
	for (linha = 0; linha < TAM; linha++)
	{
		for (coluna = 0; coluna < TAM; coluna++)
		{	printf("labirinto[ %d ] [ %d ] -> ID= %d \n", linha, coluna, labirinto[linha][coluna]->id);	
			printf("labirinto[ %d ] [ %d ] -> paredes[0]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[0]->parede);
			printf("labirinto[ %d ] [ %d ] -> paredes[1]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[1]->parede);
			printf("labirinto[ %d ] [ %d ] -> paredes[2]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[2]->parede);
			printf("labirinto[ %d ] [ %d ] -> paredes[3]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[3]->parede);
			printf("labirinto[ %d ] [ %d ] -> paredes[4]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[4]->parede);
			printf("labirinto[ %d ] [ %d ] -> paredes[5]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[5]->parede);

			//printf("labirinto[ %d ] [ %d ] -> paredes[6]->parede = %d \n", linha, coluna, labirinto[linha][coluna]->paredes[6]->parede);

			printf("labirinto[ %d ] [ %d ] -> pertence = %d \n", linha, coluna, labirinto[linha][coluna]->pertence);
			/*
			labirinto[linha][coluna]->direita_cima;
			labirinto[linha][coluna]->direita_baixo ;
			labirinto[linha][coluna]->inferior;
			labirinto[linha][coluna]->esquerda_baixo;
			labirinto[linha][coluna]->esquerda_cima;

			labirinto[linha][coluna]->pertence = 0;
			*/
			printf("\n");
		}
		printf("\n");
	}
}


int main ()
{
    int o;
    char op;


     do
    {   printf("1)Gera   2) Mostra  3)Executa  4)MostraParedes   0) sair: ");
        scanf("%d",&o);
        switch (o)
        {   case 1:

        	gera();
            //scanf("%s",str1 );
			
                    break;

            case 2:
            mostraLabirinto();
                    break;
            case 3: 
            cria();
            		break;

            case 4: 
            mostra(lista);
            		break;

            case 5: 
            printf("Tamanho da Lista de Paredes = %d\n", size(lista) );
            
            		break;

        }	


    }	
    while (o);
    inicializaLista(lista);
    desalocaMatriz();
}