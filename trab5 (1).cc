#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
    if ('^'== op)
        return pow(vlr, vlr2);
    
}

int valida (char str[]) 
{   int i, j, abre, fecha=0, tam, aux;
    tam = strlen(str);
    
    for (i = 0; i < tam; i++)
    {   if (str[i] == '(') abre++;
        if (str[i] == ')') fecha++;
        
       // if (str[i] != '.' && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '^' && str[i] != '(' && str[i] != ')' || (str[i] >= '0' && str[i] <= '9'))
       if (str[i] != '.' && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '^' && str[i] != '(' && str[i] != ')' )
        {   
            if (str[i] >= 48 && str[i] <= 57 ){}
                else 
                {
                    printf("ERRO = %c\n", str[i]);
                    printf("%s \n", str);
                    for (j = 0; j< i; j++) printf(" ");
                    printf("/\\Expressao Invalida! \n");
                    return 0;
                }
        }
        
    }
    /*
    printf("TAMANHO = %d\n", tam);
    printf("ABRE = %d\n", abre);
    printf("FECHA = %d\n", fecha);
    */

    if (str[0] != '(' || (abre-fecha) ) 
    {
        printf("%c\n", str[0] );
        printf("/\\Erro, Expresão Mal Parentizada;\n");
        return 0;
    }
    if(str[tam-1]  != ')')
    {   printf("%c\n", str[tam-1] );
        printf("/\\Erro, Expresão Mal Parentizada;\n");
        return 0;
    }
    return 1;

}

void calcula(char str[])
{
    int i;
    float vlr;
    float vlr2;
    char op;

    if (valida(str)) 
    {
        // não estou considerando a seguinte expressão como valida: (3).
            //Motivo, pelo que me lembro da explicacao da calcinha, para cada ')' temos de desempilhar,
            // e se desempilharmos, temos que aplicar o calculo. Entao o correto seria: (0+3). Roger?

        //para cada caracter
        for ( i= 0; str[i] != '\0'; i++)
        {

            
            //se for um operador, empilha oprecacao
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '^')
            {
                //Teste se o proximo de operacao é um '-' e se o proximo dele é um valor, '(2--2)'
                    // Se for, ele vai empilhar float, apartir da operacao, para testar (2-(-2)), - com - é igual a +
                if (str[i+1] == '-' && (str[i+2] >= '0' && str[i+2] <= '9'))
                {       pushOperacao(pilhaOperacao, str[i]);
                    //printf("*OPERACAO = %c\n", str[i] );

                        sscanf(str+i+1, "%f", &vlr); //le o valor
                        pushValor(pilhaValor, vlr);
                        while (str[i+1] == '-' || (str[i+1] >= '0' && str[i+1] <= '9')) //Passa pelo Operador
                            i++;
                    

                } else if (str[i-1] != '('){
                     pushOperacao(pilhaOperacao, str[i]);
                }
                    
            
                
            } 
            else if (str[i] >= '0' && str[i] <= '9') //Verifica se for um número
             {   
                    //Testa se o menos é um operador ou é do valor, para assim poder calcular corretamente ex:(-2+5)
                    if((str[i] >= 48 && str[i] <= 57) && str[i-1] == '-' && str[i-2] == '(' )
                    {   //(-2+10)
                        sscanf(str+i-1, "%f", &vlr); //le o valor
                        pushValor(pilhaValor, vlr);
                        while (str[i-1] == '-' || (str[i] >= '0' && str[i] <= '9')) 
                            i++;
                        pushOperacao(pilhaOperacao, str[i]);

                    } else {

                    sscanf(str+i, "%f", &vlr); //le o valor
                    pushValor(pilhaValor, vlr);
                    while (str[i+1] == '.' || (str[i+1] >= '0' && str[i+1] <= '9')) //Passa pelo float
                        i++;
                }

            }
            else if (str[i] == ')') // se for ')', desempilha valor e operacao e aplica o calculo
            { 
                vlr2 = popValor(pilhaValor);
                vlr = popValor(pilhaValor);
                op = popOperacao(pilhaOperacao);

                if (op == '^' && vlr2 < 0)
                { printf("Impossivel calcular Expoente Negativo\n"); 
                    return;
                }
                pushValor(pilhaValor, fazConta (vlr, op, vlr2)); // Empilha Novamente, para um proximo calculo
     
            }
            // '(' sao ignorados
        }
        printf(" O Resultado é %2f\n", popValor(pilhaValor));
    }
}

int main (){
    int o;

    inicializaValor(pilhaValor);
    inicializaOperacao(pilhaOperacao);

    //char expressao[] = "(((21.5+10.77)/2)+(4*(2.5+3)))";
    //char expressao[] = "((((1+2)+3) + (4*2))*2)";
    //char expressao[] = "((((1+((2+3)-(4-2)))+(,1+2))*2)/((2*3)+(4/4)))"; //invalida
    //char expressao[] = "((((1+((2+3)-(4-2)))+(1+2))*2)/((2*3)+(4/4)))"; //  Ok vlr=2

    //char expressao[] = "(2^4)";
      char expressao[] = "(-5+10)";
    //char expressao[] = "((((2.3+4)*3)+1)-2)";



  
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