/*O presente programa o usuário digita uma data qualquer e mostra o dia da semana correspondente.
Autor: Reginaldo de Matias - Ciência da Computação - UDESC*/

#include <stdio.h>
#include <stdlib.h>
 
void calculo_dia_da_semana(int dia,int mes,int ano);
 
int main()
{
    int d,m,a,teste;
    do{
        teste = 0;
      printf("Calculo do dia da semana\n");
      printf("dia: ");
      scanf("%i",&d);
      printf("mes: ");
      scanf("%i",&m);
      printf("ano: ");
      scanf("%i",&a);
      if((d < 1 || d > 31) || (m < 1 || m > 12) || (a < 1583))
         teste = 1;
         if((m == 2) && (d + m) > 31) /*fevereiro tem no máximo 29 dias*/
         {
             if((m == 2) && (d == 29)) /*verifica se não é ano bissexto*/
             {
                 if(!(a% 4 == 0) && (a % 100 != 0) || (a % 400 == 0))
                 teste = 1;
             }
         }    
        if(teste)
        {
            printf("\n!!!ERRO!!! A data (%i/%i/%i) nao existe!!!\n",d,m,a);
        }
      }while(teste);
      //depois do teste de erro    
            calculo_dia_da_semana(d,m,a);
system("Pause");
}
void calculo_dia_da_semana(int dia,int mes,int ano)
{
    switch (mes)
    {
        case 1: break;
        case 2: dia += 31; break;
        case 3: dia += 59; break;
        case 4: dia += 90; break;
        case 5: dia += 120; break;
        case 6: dia += 151; break;
        case 7: dia += 181; break;
        case 8: dia += 212; break;
        case 9: dia += 243; break;
        case 10: dia += 273; break;
        case 11: dia += 304; break;
        case 12: dia += 334; break;
    }
           /* Se o ano é um ano-bisexto E
           Se o mes de fevereiro ja passou entao acrescente um dia ao deslocamento*/
           if ( ((ano%4)==0) && ( ((ano%100)!=0) || ((ano%400)==0) ) && (mes > 2))
               dia += 1;
               dia += -1 + (ano-1)*365 + (ano-1)/4 -(ano-1)/100 +(ano-1)/400 ;            
                 
             switch (dia % 7)
             {
                case 0: printf("Segunda-feira\n"); break;
                case 1: printf("Terca-feira\n"); break;
                case 2: printf("Quarta-feira\n"); break;
                case 3: printf("Quinta-feira\n"); break;    
                case 4: printf("Sexta-feira\n"); break;
                case 5: printf("Sabado.\n"); break;
                case 6: printf("Domingo.\n"); break;
             }
}   