#include<stdio.h>

#include<stdio.h>

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

int main()
{
	unsigned long long a,b;
	scanf("%lld",&a);
	b = Fatorial(a);
	printf("O fatorial de %lld e' %lld.\n",a,b);
	return 0;
}
