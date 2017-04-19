#include<stdio.h>

int DIV_signed(int a, int b)
{
	if(a<0 && b<0)
	{
		a = -a;
		b = -b;
		return Unsigned_Div(a,b);
	}
	else if (a<0 && b>0)
	{
		a = -a;
		return -(Unsigned_Div(a,b));
	}
	else if (a>0 && b<0)
	{
		b = -b;
		return -(Unsigned_Div(a,b));
	}
	else
	{
		return Unsigned_Div(a,b);
	}

}

int Unsigned_Div(int dividendo,int divisor)
{
	if(dividendo >= divisor)
	{
		dividendo -= divisor;
		return (1 + Unsigned_Div(dividendo,divisor));
	}
	else
		return 0;
}

void main()
{
	int a,b,c;
	scanf("%d %d",&a,&b);
	c = DIV_signed(a,b);
	printf("A divisao de %d por %d e' %d.\n",a,b,c);
}
