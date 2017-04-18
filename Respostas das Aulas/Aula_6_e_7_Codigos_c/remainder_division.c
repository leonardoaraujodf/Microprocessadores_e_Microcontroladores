#include <stdio.h>

int Remainder (int dividend,int divisor)
{
	while (dividend >= divisor)
	{
		dividend -= divisor;
	}
	
	return dividend;
}

int main ()
{
	int a,b,c;
	scanf("%d %d",&a,&b);
	c = Remainder(a,b);
	printf("The division between %d and %d has %d as remainder.\n",a,b,c);
	return 0;
}
