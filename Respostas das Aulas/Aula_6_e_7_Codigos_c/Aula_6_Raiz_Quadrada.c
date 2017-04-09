#include<stdio.h>

int Divisao(int dividendo,int divisor)
{
	if(dividendo >= divisor)
	{
		dividendo -= divisor;
		return (1 + Divisao(dividendo,divisor));
	}
	else
		return 0;
}

int Raiz_Quadrada(float s)
{
	float x=0;
	do 
	{
		if(x==0)
		{
			x=Divisao(s,2);
			printf("%f\n",x);
			x = Divisao((x + Divisao(s,x)),2);
			printf("%f\n",x);
		}
		else
		{
			x = Divisao((x + Divisao(s,x)),2);
			printf("%f\n",x);
		}
	}
	while((x - Divisao((x + Divisao(s,x)),2)) >= 1);
	
	return x;
}

int main ()
{
	float numero;
	int raiz_numero;
	scanf("%f",&numero);
	raiz_numero = Raiz_Quadrada(numero);
	printf("A raiz de %.0f e' %d, e sua divisao por 5 e' %d.\n",numero,raiz_numero,Divisao(numero,5));
	return 0;
}
