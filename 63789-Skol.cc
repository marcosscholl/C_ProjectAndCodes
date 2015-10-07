


void excluirrepetições(struct no *&l, int r)
{
	struct no *noAux = l; 
	int cont;

	while (noAux -> proximo != l)
	{
		if (noAux->informacao == valor)
		{
			cont++;

			if (cont > 1)
			{
				noAux->anterior->proximo = noAux->proximo;
				noAux->proximo->anterior = noAux->anterior;
				//aux= no;
				delete(noAux);
			}

		}
		noAux = noAux->proximo;

	}
	//Se for o Ultimo
	if(cont > 1 && noAux-> informacao == valor && noAux->proximo == l)
	{	//Nao deleta pois esta perto do Inicio da Lista
	}
}



void movermaiorsequencia(struct no *&l) 
{
	struct no *noAux = l, *&noCopy = l, *p, *seguraPosicao;
	int cont, cont2;

	while (noAux -> proximo != l)
	{
		if (noAux->informacao  >  noAux->anterior->informacao)
		{	
			cont++;

			if(cont2 < cont)
			{
				cont2= cont; 
				p=noAux;
			} 

		}
		noAux = noAux->proximo;
	}

	for (i = cont; (i); i--)
	{	//volta até o ponteiro onde começa a ordenacao. 
			//Nao tenho certeza de que assim esta correto, nao cou preder tempo com testes aprofundados;
		p = p->anterior;
	}
	for (i = cont; (i); i--)
	{	//Nao tenho certeza se nocopy vai realmente afetar a lista l, ou se será uma variavel local
		if(noCopy->anterior->proximo == l)
			noCopy = p;
			noCopy->proximo->anterior = noCopy
			p->anterior = noCopy->anterior;
			l=noCopy;
			//noCopy->anterior ->proximo == noCopy;
		}
		noCopy -> proximo = p;
		p-anterior = noCopy;

		noCopy = noCopy -> proximo;	
	}
	noCopy-> proximo = l->proximo;

}
