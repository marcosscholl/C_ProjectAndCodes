#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct pilhaValor{
    int topo;
    float valor[MAX];
} pilhaValor;

struct pilhaOperacao{
    int topo;
    char operacao[MAX];
} pilhaOperacao;



void inicializaOperacao(struct pilhaOperacao &p)
{   p.topo = -1;
}


//Empurra
void pushOperacao(struct pilhaOperacao &p, int v)
{   if (p.topo < MAX-1) p.operacao[++p.topo] = v;
}

//retira
int popOperacao(struct pilhaOperacao &p)
{   if (p.topo > -1) return(p.operacao[p.topo--]);
    return(-1);
}


void inicializaValor(struct pilhaValor &p)
{   p.topo = -1;
}


void pushValor(struct pilhaValor &p, float v)
{   if (p.topo < MAX-1) p.valor[++p.topo] = v;
}

float popValor(struct pilhaValor &p)
{   if (p.topo > -1) return(p.valor[p.topo--]);
    return(-1);
}



void mostraPilhaValor(struct pilhaValor p)
{   int i;
    for (i = 0; (i <= p.topo); i++) printf("%f \n",p.valor[i]);
    printf("\nq = %d\n",p.topo);
}


void mostraPilhaOperacao(struct pilhaOperacao p)
{   int i;
    for (i = 0; (i <= p.topo); i++) printf("%d \n",p.operacao[i]);
    printf("\nq = %d\n",p.topo);
}





float fazConta(float vlr, char op, float vlr2){
    if ('+' == op)
        return vlr + vlr2;
    if ( '-' == op)
        return vlr - vlr2;
    if ( '*' == op)
        return  vlr * vlr2;
    if ('/' == op)
        return vlr / vlr2;
}

void calcula(char str[])
{
    int i;
    float vlr;
    float vlr2;
    char op;

    //para cada caracter
    for ( i= 0; str[i] != '\0'; i++)
    {
        //se for um operador, empilha oprecacao
        if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
        {
            pushOperacao(pilhaOperacao, str[i]);
        }
        else if (str[i] >= '0' && str[i] <= '9') //Verifica se for um número
         {   sscanf(str+i, "%f", &vlr); //le o valor
            pushValor(pilhaValor, vlr);
            while (str[i+1] == '.' || (str[i+1] >= '0' && str[i+1] <= '9')) //Passa pelo float
                i++;

        }
        else if (str[i] == ')') // se for ')', desempilha valor e operacao e aplica o calculo
        { 
            vlr2 = popValor(pilhaValor);
            vlr = popValor(pilhaValor);
            op = popOperacao(pilhaOperacao);
            pushValor(pilhaValor, fazConta (vlr, op, vlr2)); // Empilha Novamente, para um proximo calculo
 
        }
        // '(' sao ignorados
    }
    printf(" O Resultado é %2f\n", popValor(pilhaValor));
}

int main (){
    int o;

    inicializaValor(pilhaValor);
    inicializaOperacao(pilhaOperacao);

    char expressao[] = "(((21.5+10.77)/2)+(4*(2.5+3)))";
  
    do
    {   printf("1) inicializa    2)Calcula  3)MostraPilha_Valor  4)MostraPilha_Operacoes   0) sair: ");
        scanf("%d",&o);
        switch (o)
        {   case 1: inicializaValor(pilhaValor);
            inicializaOperacao(pilhaOperacao);
            //tamExpress(expressao);
                    break;
            case 2: calcula(expressao);
                    break;
            case 3: 
                mostraPilhaValor(pilhaValor);
                    break;
            case 4: 
                mostraPilhaOperacao(pilhaOperacao);
                    break;

            case 8: //mostra(espressao);
                    break;
        }
    }
    while (o);
    return 0;
}