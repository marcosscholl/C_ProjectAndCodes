/* Programa: polinomios.c (Polinômios) */
/* Autor: Alexandre N. de Medeiros RA115966 */
/* Disciplina: MC202 Turma E */
/* Data: 10/ago/2011 */
/* Revisado: 16/set/2012 */

/* Este módulo implementa operações sobre polinômios em uma variável. */
/* Cada polinômio é representado por uma lista ligada simples, com nó */
/* cabeça. Os nós da lista representam os termos não nulos do polinômio */
/* em ordem crescente dos seus expoentes. O nó cabeça tem expoente '-1'.*/

//#include "polinomios.h"
//#include "balloc.h"
#include <stdio.h>

/*----------------------- Funções auxiliares ----------------------------*/

void InsereTermoAux(Polinomio p, int e, float c)
{
  /* Insere o termo '(e,c)' após o nó apontado por 'p'. */

  Polinomio novo = MALLOC(sizeof(Termo));
  novo->expo = e;
  novo->coef = c;
  novo->prox = p->prox;
  p->prox = novo;

  return;

} /* InsereTermoAux */

/*---------------- Implementação das funções da interface --------------*/

void ImprimePolinomio(Polinomio p)
{
  /* Imprime, em ordem crescente dos expoentes, os termos do */
  /* não nulos do 'p'. No caso do polinômio identicamente nulo, */
  /* imprime as palavras "Polinômio nulo". */

  if (p==NULL) {
    printf("Polinômio inválido\n");
    return;
  }

  if (p->prox==p) {
    printf("Polinômio nulo\n");
    return;
  }

  p = p->prox;
  while (p->expo!=-1) {
    printf("(%2d,%5.1f) ",p->expo,p->coef);
    p = p->prox;
  }
  printf("\n");

} /* ImprimePolinomio */

Polinomio CriaPolinomioNulo()
{
  /* Devolve um novo polinômio identicamente nulo. */

  /* Cria um nó cabeça e retorna seu endereço. */
  Polinomio novo = MALLOC(sizeof(Termo));
  novo->expo = -1;
  novo->prox = novo;

  return novo;

} /* CriaPolinomioNulo */

void LiberaPolinomio(Polinomio p)
{
  /* Libera toda a memória dinâmica ocupada por um polinômio. */

  Polinomio q = p->prox, aux;

  /* Libera nó por nó até voltar ao nó cabeça da lista. */
  while (q != p) {
    aux = q->prox;
    FREE(q);
    q = aux;
  }

  /* Libera o nó cabeça */
  FREE(p);

  return;

} /* LiberaPolinomio */

Boolean PolinomioNulo(Polinomio p)
{
  /* Verifica se o polinômio 'p' é identicamente nulo. */

  /* Se o nó cabeça aponta pra si mesmo o Polinômio é nulo. */
  if (p->prox == p)
    return true;
  else
    return false;

} /* PolinomioNulo */

void InsereTermo(Polinomio p, int e, float c)
{
  /* Insere no polinomio 'p' o termo '(e,c)', de maneira a manter os */
  /* termos ordenados. Supõe que não existe ainda em 'p' um termo com */
  /* expoente 'e', e que 'c' não é zero. */

  Polinomio atual = p, prox = p->prox;

  /* Caso encontrou a posição adequada OU chegou no final do polinomio
* retorna a posição anterior.
*/
  while (prox->expo < e && prox != p) {
    atual = prox;
    prox = prox->prox;
  }

  InsereTermoAux(atual, e, c);

  return;

} /* InsereTermo */

Polinomio SomaPolinomios(Polinomio a, Polinomio b)
{
  /* Devolve a soma dos polinômios 'a' e 'b'. Não altera os polinômios */
  /* dados. Termos nulos não são inseridos no resultados. */

  Polinomio res, atualA = a->prox, atualB = b->prox, aux;

  res = CriaPolinomioNulo();
  aux = res;

  /* Como ambos polinômios estão ordenados, faz uma intercalação
* e caso encontra um termo de mesmo expoente em ambos, soma-os
*/
  while (atualA != a && atualB != b) {
    /* Termos de mesmo expoente em ambos polinômios. */
    if (atualA->expo == atualB->expo) {
      if (atualA->coef + atualB->coef != 0) {
        InsereTermoAux(aux, atualA->expo, atualA->coef + atualB->coef);
        aux = aux->prox;
      }

      atualA = atualA->prox;
      atualB = atualB->prox;

    } else if (atualA->expo < atualB->expo) {
      /* Termo de expoente exclusivo do polinômio 'a'. */
      InsereTermoAux(aux, atualA->expo, atualA->coef);
      aux = aux->prox;

      atualA = atualA->prox;
    } else if (atualA->expo > atualB->expo) {
      /* Termo de expoente exclusivo do polinômio 'b'. */
      InsereTermoAux(aux, atualB->expo, atualB->coef);
      aux = aux->prox;

      atualB = atualB->prox;
    }

  }

  /* Insere, no novo polinômio, os termos restantes do polinômio de maior grau. */
  if (atualA == a) {
    while (atualB != b) {
      InsereTermoAux(aux, atualB->expo, atualB->coef);
      aux = aux->prox;

      atualB = atualB->prox;
    }
  } else {
    while (atualA != a) {
      InsereTermoAux(aux, atualA->expo, atualA->coef);
      aux = aux->prox;

      atualA = atualA->prox;
    }
  }

  return res;

} /* SomaPolinomios */

Polinomio MultTermo(Polinomio p, int e, float c)
{
  /* Devolve o polinômio 'p' multiplicado pelo termo '(e,c)'. Supõe */
  /* que 'c' não é nulo. Não altera os polinômio dado. */

  Polinomio
  res, // Resultado da Multiplicação
  atual = p->prox, // Nó atual do polinomio p
  aux;

  res = CriaPolinomioNulo();
  aux = res;
  /* Multiplica todos termos do polinômio 'p' por um termo. */
  while (atual != p) {
    InsereTermoAux(aux, atual->expo + e, atual->coef * c);
    aux = aux->prox;
    atual = atual->prox;
  }

  return res;

} /* MultTermo */

Polinomio MultPolinomios(Polinomio a, Polinomio b)
{
  /* Devolve o produto dos polinômios 'a' e 'b'. Não altera os polinômios */
  /* dados. */

  Polinomio
  aux1, // Resultado parcial da multiplicação por um termo
  aux2, // Resultado parcial do resultado atual com 'aux1'
  atualB = b->prox, // Termo atual do Polinômio 'b'
  res; // Resultado final


  res = CriaPolinomioNulo();

  /* Multiplica o polinomio 'a' pelos termos de 'b', usando um termo de
* 'b' por vez, somando o resultado de cada multiplicação.
*/
  while (atualB != b) {
    /* Multiplica 'atualB' termo pelo polinômio 'a'. */
    aux1 = MultTermo(a, atualB->expo, atualB->coef);
    atualB = atualB->prox;

    /* Soma o resultado da multiplicação com a soma parcial. */
    aux2 = SomaPolinomios(res, aux1);

    /* Libera os Polinômios que não serão mais utilizados. */
    LiberaPolinomio(aux1);
    LiberaPolinomio(res);

    res = aux2;
  }

  return res;

} /* MultPolinomios */
