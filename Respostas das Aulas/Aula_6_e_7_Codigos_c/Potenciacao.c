#include <stdio.h>

int MULT_signed(int a, int b)
{
	if(a<0 && b<0)
	{
		a = -a;
		b = -b;
		return MULT_unsigned(a,b);
	}
	else if (a<0 && b>0)
	{
		a = -a;
		return -(MULT_unsigned(a,b));
	}
	else if (a>0 && b<0)
	{
		b = -b;
		return -(MULT_unsigned(a,b));
	}
	else
	{
		return MULT_unsigned(a,b);
	}

}

int MULT_unsigned(unsigned int a, unsigned int b)
{
if(b==0) return 0;
else
return a+MULT_unsigned(a, (b-1));
}

int Potencia(int x, int N)
{
	if(N==0) return 1;
	else return MULT_signed(x,Potencia(x, (N-1)));
}

int main ()
{
	int a,b,c;
	scanf("%d %d",&a,&b);
	c = Potencia(a,b);
	printf("O resultado de %d elevado a %d e' %d.\n",a,b,c);
	return 0;
}
