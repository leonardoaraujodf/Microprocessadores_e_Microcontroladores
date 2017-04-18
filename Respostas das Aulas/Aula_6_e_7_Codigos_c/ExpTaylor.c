#include<stdio.h>

unsigned long long Divisao(unsigned long long dividendo,unsigned long long divisor)
{
	if(dividendo >= divisor)
	{
		dividendo -= divisor;
		return (1 + Divisao(dividendo,divisor));
	}
	else
		return 0;
}

unsigned long long MULT_unsigned(unsigned long long a, unsigned long long b)
{
if(b==0) return 0;
else
return a+MULT_unsigned(a, (b-1));
}

unsigned long long Fatorial (long long n)
{
	if(n==0 || n==1)
	{
		return 1;
	}
	else
	{
		return (MULT_unsigned(n,Fatorial(n-1)));
	}
}

unsigned long long Potencia(unsigned long long x, unsigned long long N)
{
	if(N==0) return 1;
	else return MULT_unsigned(x,Potencia(x, (N-1)));
}


/*  Série de Taylor da EXP(X) = Somatório([x^n]/n!)    */

unsigned long long ExpTaylor_int(unsigned long long x)
{
	long long n;
	long long exp_x=0;
	for(n=0;n<=9;n++)
	{
		exp_x += Divisao((Potencia(x,n)),(Fatorial(n))); /*x^n/n!*/
	}
	return exp_x;
}

int main()
{
	unsigned long long x,resultado;
	scanf("%lld",&x);
	resultado = ExpTaylor_int(x);
	printf("EXP(%lld) = %lld.\n",x,resultado);
	return 0;
}
