#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Transformar em numeral romano um número inteiro positivo n (int n). 
/*
I, V,  X,  L,  C,   D,   M
1, 5, 10, 50, 100, 500, 1000
*/
//n = 1350 = MCCCL
int main()
{	int n;
	printf("Digite um Numero:\n");
	scanf("%d", &n);
	//n = 1350;
	while (n > 0) {		
		  if ( n >= 1000) { 
		  	n -=1000;   printf("M");
		  } else if ( n >= 500 && n < 1000) {
		  	n -=500; printf("D");
		  } else if (n == 400) {
		  	n-=400;
		  	printf("ID");
		  } else if ( n >= 100  && n < 500) {
		  	n -=100; printf("C");
		  } else if (n == 90) {
		  	n-=90;
		  	printf("IC");
		  } else if ( n >= 50 && n < 100) {
		  	n -=50; printf("L");
		  } else if (n == 40) {
		  	n-=40;
		  	printf("IL");
		  }else if ( n >= 10 && n < 40) {
		  	n -=10; printf("X");
		  } else if (n == 9) {
		  	n-=9;
		  	printf("IX");
		  }else if ( n >= 5 && n < 9) {
		  	n -=5; printf("V");
		  } else if (n == 4) {
		  	n-=4;
		  	printf("IV");
		  }else if ( n >= 1 && n < 4) {
		  	n -=1; printf("I"); 
		  }
	}
	printf("\n");
}
