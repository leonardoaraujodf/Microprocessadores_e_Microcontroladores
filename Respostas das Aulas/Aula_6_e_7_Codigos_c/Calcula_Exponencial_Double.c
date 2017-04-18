#include <stdio.h>

double Fatorial (long long n)
{
	if(n==0 || n==1)
	{
		return 1;
	}
	else
	{
		return (n*Fatorial(n-1));
	}
}

double Pot(double x, int n)
{
	if(n>0)
	{
		return (x*Pot(x,(n-1)));
	}
	else
		return 1;
}

double ExpTaylor(double x)
{
	int i;
	double Exp;
	for(i=0;i<=20;i++)
	{
		Exp += Pot(x,i)/Fatorial(i);
	}
	return Exp;
}

void main ()
{
	double x,resultado;
	scanf("%lf",&x);
	resultado = ExpTaylor(x);
	printf("EXP(%.2lf) = %.4lf",x,resultado);
}
