#include <stdio.h>
#include <stdlib.h>

#define INFINITO 9999999
#define VISITADO 1
#define NAOVISITADO 0
#define MAX 57


struct aresta
{	int destino;
	int distancia;
	int interrupcoes;
    int sinaleiras;
    int preferencial;
    int material;
    int buracos;
    int reducao;
	struct aresta *proximo;
};

struct vertice
{	int origem;
	char visitado;
    int distanciaAteMim;
	struct aresta *arestas;
	struct vertice *proximo;
} *g = NULL;



struct vertice *procuravertice(struct vertice *g, int o)
{	struct vertice *v;

	for (v = g; (v != NULL); v = v->proximo) if (v->origem == o) return(v);
	return(NULL);
}

struct aresta *procuraaresta(struct vertice *g, int o, int d)
{	struct vertice *v;
	struct aresta *a;

	if ((v = procuravertice(g,o)) == NULL) return(NULL);
	for (a = v->arestas; (a != NULL); a = a->proximo) if (a->destino == d) return(a);
	return(NULL);
}

void incluivertice(struct vertice *&g, int origem)
{	struct vertice *n;

	if (procuravertice(g,origem) != NULL) return;
	n = new(struct vertice);
	n->origem = origem;
	n->arestas = NULL;
	n->arestas = NULL;
	n->proximo = g;
	g = n;
}

//void incluiaresta(struct vertice *&g, int origem, int destino, float c)
void incluiaresta(struct vertice *&g, int origem, int destino, int distancia, int interrupcoes, int sinaleiras, int preferencial, int material, int buracos, int reducao)
{	struct aresta *n;
	struct vertice *v;

	incluivertice(g,origem);
	incluivertice(g,origem);
	if (procuraaresta(g,origem,destino) != NULL) return;
	n = new(struct aresta);
	n->destino = destino;
	n->distancia = distancia;
	n->interrupcoes = interrupcoes;
    n->sinaleiras = sinaleiras;
    n->preferencial = preferencial;
    n->material = material;
    n->buracos = buracos;
    n->reducao = reducao;
	n->proximo = (v = procuravertice(g,origem))->arestas;
	v->arestas = n;
}


void inicializaaresta(struct aresta *&a)
{	struct aresta *t;

	while (a != NULL)
	{	t = a;
		a = a->proximo;
		delete(t);
	}
}

void inicializavertice(struct vertice *&g)
{	struct vertice *t;

	while (g != NULL)
	{	t = g;
		g = g->proximo;
		inicializaaresta(t->arestas);
		delete(t);
	}
}


void mostra(struct vertice *g)
{	struct vertice *v;
	struct aresta *a;

	for (v = g; (v != NULL); v = v->proximo)
	{	printf("%d: ",v->origem);
		for (a = v->arestas; (a != NULL); a = a->proximo) printf("%d,%d ",a->destino,a->distancia);
		printf("\n");
	}
}

FILE * montaGrafo(FILE *arquivo)
{	int origem, destino;
	int distancia, interrupcoes, sinaleiras, preferencial, material, buracos, reducao;

	while(fscanf(arquivo,"%d:%d(%d,%d,%d,%d,%d,%d,%d)", &origem, &destino, &distancia, &interrupcoes, &sinaleiras, &preferencial, &material, &buracos, &reducao) != EOF)
		incluiaresta(g, origem, destino, distancia, interrupcoes, sinaleiras, preferencial, material, buracos, reducao);
	return arquivo;
	//fclose(arquivo);
}


void dijkstraDistancia(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;

	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)	distancias[vertice] =  a->distancia;
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <=MAX; i++)
        {	if (!pertence[i])
         	{	
            	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	
               		if (distancias[i] != 0 && (distancias[v] + a->distancia < distancias[i])) 
               		{
                    	distancias[i] = distancias[v] + a->distancia;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);
   
	// Mostra o Resultado da busca 
    printf("\nDistância De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }
   
}



int calculaMaterial(struct aresta *a)
{	int material = 0;
	if (a->material) 
	{	if (a->material == 1) material = (int)a->distancia/9;
		else if (a->material == 2) material = (int)a->distancia/7;
		else material = (int)a->distancia/5;
		return material;
	}
	else return 0;
}

int calculaBuraco(struct aresta *a)
{	int buraco = 0;
	if (a->buracos)
	{	if (a->buracos == 1) buraco = (int)a->distancia/10;
		else if (a->buracos == 2) buraco = (int)a->distancia/9;
		else if (a->buracos == 3) buraco = (int)a->distancia/7;
		else if (a->buracos == 4) buraco = (int)a->distancia/5;
		else buraco = (int)a->distancia/3;
		return buraco;
	}
	else return 0;
}

void dijkstraTempo(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;

	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;	  


	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        //if ((a=procuraaresta(g, origem, vertice)) != NULL)	distancias[vertice] =  a->interrupcoes + (a->sinaleiras*2) + a->preferencial;
    	if ((a=procuraaresta(g, origem, vertice)) != NULL)
    	{	if (a->sinaleiras) sinaleira = a->distancia/4 ;
			if (a->interrupcoes) interupcao = a->distancia/6 ;
			if (a->preferencial) preferencial = a->distancia/8;
    		distancias[vertice] =  interupcao + sinaleira + preferencial;

    		a->distancia = distancias[vertice];
    	}	
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{
					if (a->sinaleiras) sinaleira = a->distancia/4 ;
					if (a->interrupcoes) interupcao = a->distancia/6 ;
					if (a->preferencial) preferencial = a->distancia/8;

               		if (distancias[i] != 0 && ((distancias[v] +  interupcao + sinaleira + preferencial) < distancias[i])) 
               		{
                    	distancias[i] = distancias[v] + interupcao + sinaleira + preferencial;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);

   
	// Mostra o Resultado da busca 
    printf("\nTempo De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }
    inicializaaresta(a);
   
}

//
void dijkstraDesgaste(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;

	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;

	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)
        {	material = calculaMaterial(a);
        	buraco = calculaBuraco(a);
        	if (a->reducao) reducao = (int)a->distancia/7;

        	distancias[vertice] =  material + buraco + reducao;
        	a->distancia = distancias[vertice];
        }
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	material = calculaMaterial(a);
		        	buraco = calculaBuraco(a);
		        	if (a->reducao) reducao = (int)a->distancia/7;

               		if (distancias[i] != 0 && ((distancias[v] +  material + buraco + reducao) < distancias[i])) 
               		{
                    	//distancias[i] = distancias[v] + a->material + a->buracos + a->reducao;
                    	distancias[i] = distancias[v] + material + buraco + reducao;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);
   
	// Mostra o Resultado da busca 
    printf("\nConservação De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }
    inicializaaresta(a);
   
}




void dijkstraDistancia_Tempo(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;
	
	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;


	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)
        {	if (a->sinaleiras) sinaleira = a->distancia/4 ;
			if (a->interrupcoes) interupcao = a->distancia/6 ;
			if (a->preferencial) preferencial = a->distancia/8;
        	distancias[vertice] =  a->distancia + sinaleira + interupcao + preferencial;
        	a->distancia = distancias[vertice];
        }
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	if (a->sinaleiras) sinaleira = a->distancia/4 ;
					if (a->interrupcoes) interupcao = a->distancia/6 ;
					if (a->preferencial) preferencial = a->distancia/8;

               		if (distancias[i] != 0 && ((distancias[v] +  a->distancia + interupcao +preferencial + sinaleira) < distancias[i])) 
               		{	//printf("%s\n", );
                    	distancias[i] = distancias[v] +  a->distancia +  interupcao +preferencial + sinaleira;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);

   
	// Mostra o Resultado da busca 
    printf("\nDistancia + Tempo De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }

    inicializaaresta(a);
   
}



void dijkstraDistancia_Desgaste(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;


	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;


	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)	
        {	material = calculaMaterial(a);
        	buraco = calculaBuraco(a);
        	if (a->reducao) reducao = (int)a->distancia/7;
        	distancias[vertice] =  a->distancia + material + buraco + reducao;
        	a->distancia = distancias[vertice];
        }
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	material = calculaMaterial(a);
		        	buraco = calculaBuraco(a);
		        	if (a->reducao) reducao = (int)a->distancia/7;

               		if (distancias[i] != 0 && ((distancias[v] + a->distancia + material + buraco + reducao) < distancias[i])) 
               		{	distancias[i] = distancias[v] +  a->distancia + material + buraco + reducao;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);

   
	// Mostra o Resultado da busca 
    printf("\nDistancia + Desgaste De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }
    inicializaaresta(a);
   
}


void dijkstraTempo_Desgaste(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;

	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;


	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)	
        {	if (a->sinaleiras) sinaleira = a->distancia/4 ;
			if (a->interrupcoes) interupcao = a->distancia/6 ;
			if (a->preferencial) preferencial = a->distancia/8;

			material = calculaMaterial(a);
        	buraco = calculaBuraco(a);
        	if (a->reducao) reducao = (int)a->distancia/7;

        	distancias[vertice] =  sinaleira + interupcao + preferencial + material + buraco + reducao;
        	a->distancia = distancias[vertice];
    	}
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	if (a->sinaleiras) sinaleira = a->distancia/4 ;
					if (a->interrupcoes) interupcao = a->distancia/6 ;
					if (a->preferencial) preferencial = a->distancia/8;

					material = calculaMaterial(a);
		        	buraco = calculaBuraco(a);
		        	if (a->reducao) reducao = (int)a->distancia/7;

               		if (distancias[i] != 0 && ((distancias[v] + sinaleira + interupcao + preferencial + material + buraco + reducao) < distancias[i])) 
               		{	//printf("%s\n", );
                    	distancias[i] = distancias[v] +  sinaleira + interupcao + preferencial + material + buraco + reducao;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);

   
	// Mostra o Resultado da busca 
    printf("\nTempo + Desgaste De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);
    }
    inicializaaresta(a);
   
}

void dijkstraDistancia_Tempo_Desgaste(struct vertice *g, int origem, int destino)
{
	
	int n=57;  //quantidade de vertices	
	//int s=2; // vertice inicial
	int *ant = new (int[n]);
	int *tmp = new (int[n]);
	int *pertence = new (int[n]);  //vetor dos visitados
	int *distancias = new (int[n]);  //vetor de distancias
	int k; //enquanto vp != v
	int menor; //menor valor em d
	int u, v; //vertice com v[u] == 0 com menor valor e d
	int i, aux = 0;
	struct aresta *a;
	struct vertice *ver;
	int vertice;
	int cont;


	int interupcao, sinaleira, preferencial, material, buraco, reducao;
	interupcao = sinaleira = preferencial = material = buraco = reducao = 0;

	for (vertice = 1; vertice <=n; vertice++) {
        pertence[vertice] = NAOVISITADO;
        if ((a=procuraaresta(g, origem, vertice)) != NULL)
        {	if (a->sinaleiras) sinaleira = a->distancia/4 ;
			if (a->interrupcoes) interupcao = a->distancia/6 ;
			if (a->preferencial) preferencial = a->distancia/8;

			material = calculaMaterial(a);
        	buraco = calculaBuraco(a);
        	if (a->reducao) reducao = (int)a->distancia/7;
        	distancias[vertice] =  a->distancia + sinaleira + interupcao + preferencial + material + buraco + reducao;
    	}
    	else distancias[vertice] = INFINITO;
    }

    pertence[origem] = 1;
    distancias[origem] = 0;

    do {
 
        menor = INFINITO;
        for (i=1; i <= MAX; i++)
        {
        	if (!pertence[i])
         	{	if (distancias[i] >= 0 && distancias[i] < menor) 
            	{	if (i != 10) 
               		{	ver = procuravertice(g, i);
	               		for( a = ver->arestas; (a !=NULL); a = a->proximo)
							if ( a->distancia < menor) 	menor = a->distancia;
						//printf("I = %d  | a->distancias = %d \n", i, menor);
						v = i;
					}
            	}
        	}
      	}
 
      	if (menor != INFINITO && v != destino) 
      	{
         	pertence[v] = 1;
         	for (i = 0; i <= MAX; i++)
         	{
            	if((!pertence[i]) && ((a=procuraaresta(g,v,i))!=NULL))
				{	if (a->sinaleiras) sinaleira = a->distancia/4 ;
					if (a->interrupcoes) interupcao = a->distancia/6 ;
					if (a->preferencial) preferencial = a->distancia/8;

					material = calculaMaterial(a);
		        	buraco = calculaBuraco(a);
		        	if (a->reducao) reducao = (int)a->distancia/7;

               		if (distancias[i] != 0 && ((distancias[v] + a->distancia + sinaleira + interupcao + preferencial + material + buraco + reducao) < distancias[i])) 
               		{	//printf("%s\n", );
                    	distancias[i] = distancias[v] + a->distancia + sinaleira + interupcao + preferencial + material + buraco + reducao;
                  		ant[i] =v;
                	}
            	}
        	}
              
      	}
    } while (v != destino && menor != INFINITO);

   
	// Mostra o Resultado da busca 
    printf("\nDistancia + Tempo + Desgaste De %d para %d: \n", origem, destino);
    cont = 0;

    if (menor == INFINITO) 
    {
    	printf("Nao Existe\n");
    	printf("\tCusto: \t- \n");
    }
    else 
    {
    	i = destino;
      	//i = ant[i];
      	while (i != 0) {
        	//printf("<-%d",i+1);
         	tmp[cont] = i;
         	cont++;
         	i = ant[i];
      	}
       
      	for (i = cont; i > 0 ; i--) {
        	printf("%d -> ", tmp[i]);
      	}
      	printf("%d", destino);
       
      	printf("\n\tCusto:  %d\n", distancias[destino]);


	inicializaaresta(a);
    }
   
}

int main()
{	int o, d;
	float c;
	FILE *arquivo;

	printf("111\n");

	arquivo = montaGrafo(fopen("grafo.txt", "r"));
	printf("VAI FAZER\n");
	
	dijkstraDistancia(g, 1, 57);
	dijkstraTempo(g, 1, 57);
	dijkstraDesgaste(g, 1, 57);
	dijkstraDistancia_Tempo(g, 1, 57);
	dijkstraDistancia_Desgaste(g, 1, 57);
	dijkstraTempo_Desgaste(g, 1, 57);
	dijkstraDistancia_Tempo_Desgaste(g, 1, 57);

	//mostra(g);
	fclose(arquivo);
	inicializavertice(g);

	return(0);
}




















