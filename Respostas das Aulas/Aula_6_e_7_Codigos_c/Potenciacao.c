#include <stdio.h>

int MULT_unsigned(unsigned int a, unsigned int b)
{
if(b==0) return 0;
else
return a+MULT_unsigned(a, (b-1));
}

int Potencia(int x, int N)
{
	if(N==0) return 1;
	else return MULT_unsigned(x,Potencia(x, (N-1)));
}

int main ()
{
	int a,b,c;
	scanf("%d %d",&a,&b);
	c = Potencia(a,b);
	printf("O resultado de %d elevado a %d e' %d.\n",a,b,c);
	return 0;
}
