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
	
	for (; n >= 1000; n-=1000) printf("M");
	for (; n >= 900; n-=900) printf("CM");
	for (; n >= 500; n-=500) printf("D");
	for (; n >= 400; n-=400) printf("CD");
	for (; n >= 100; n-=100) printf("C");
	for (; n >= 90; n-=90) printf("XC");
	for (; n >= 50; n-=50) printf("L");
	for (; n >= 40; n-=40) printf("XL");
	for (; n >= 10; n-=10) printf("X");
	for (; n >= 9; n-=9) printf("IX");
	for (; n >= 5; n-=5) printf("V");
	for (; n >= 4; n-=4) printf("IV");
	for (; n >= 1; n-=1) printf("I");
	printf("\n");
	return(0);
}