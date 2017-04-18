#include<stdio.h>

int Remainder (int dividend,int divisor)
{
	while (dividend >= divisor)
	{
		dividend -= divisor;
	}
	
	return dividend;
}

int Primalidade (int a)
{	
	/*Se a for 1 ele não é primo.*/
	if (a==1)
	{
		return 0;
	}
	else if (a==2)
	{
		return 1;
	}
	/*Se a divisão de a por 2 der zero o número é PAR e não é primo.*/
	else if (Remainder(a,2)==0) 
	{
		return 0;
	}
	/*Saia verificando a com todos os outros números. Se a for divisível por i ele não é primo. Vá verificando até que i = a - 1. 
	se i chegar a ser igual a i = a - 1, o número é primo.	
	*/
	else
	{
		int i=3;
		while(Remainder(a,i)!=0 && i<a)
		{
			i+=2;
		}
		/*A condição a seguir verifica porquê o laço acabou.*/
		if(i==a)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
}

int main ()
{
	int a,v;
	scanf("%d",&a);
	v = Primalidade(a);
	if (v==0)
	{
		printf("O numero %d nao e' primo.\n",a);
	}
	else
	{
		printf("O numero %d e' primo.\n",a);
	}
	return 0;
}
