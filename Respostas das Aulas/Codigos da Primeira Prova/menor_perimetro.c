#include<stdio.h>

int MULT_unsigned(unsigned int a, unsigned int b)
{
if(b==0) return 0;
else
return a+MULT_unsigned(a, (b-1));
}

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

int minimo_perimetro(int A)
{
	A = Raiz_Quadrada(A);
	A = MULT_unsigned(A,4);
	return A;
}

void main ()
{
	int area,menor_perimetro;
	scanf("%d",&area);
	menor_perimetro = minimo_perimetro(area);
	printf("O menor perimetro e' %d.\n",menor_perimetro);
}
