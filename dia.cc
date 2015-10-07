#include <stdio.h>
#include <stdlib.h>
 
 
int main()
{	int d,m,a, s ;
    int da,ma,aa;
    int fm[12] = {32, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    

    d = 1;
    m = 1;
    a = 1900;

    printf("Data (dd/mm/aaaa): \n" );
    scanf("%d/%d/%d", &da, &ma, &aa);
    printf("1= dom - 2 -= terça");
    
    while ((d != da) || (m != ma) ||  (a != aa))
    if (++d > fm[m-1])
    {    	d = 1;
    	
    	if (++m > 12)
    	{	//CALCULA O AMANHA
    		m=1
    		a++;
    	}
    	if (++s  > 7) s = 1;
    	
    }

   
   if (c < 0)
   {
   		//Quantos dias Ontem
   }

while (s != sa)

    if (!--d)
    {
    	if (--m)
    	{
    		m = 12
    		a--;
    	}
    	d = fm[m-1];
    }
   //Zerando a Semana Se domingo, volta pra sexta
    if (!--s) s = 7;

    printf("%d/%d/%d", d, m, a);
david  guetta no rio