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
	/*Se a for 1 ele n�o � primo.*/
	if (a==1)
	{
		return 0;
	}
	else if (a==2)
	{
		return 1;
	}
	/*Se a divis�o de a por 2 der zero o n�mero � PAR e n�o � primo.*/
	else if (Remainder(a,2)==0) 
	{
		return 0;
	}
	/*Saia verificando a com todos os outros n�meros. Se a for divis�vel por i ele n�o � primo. V� verificando at� que i = a - 1. 
	se i chegar a ser igual a i = a - 1, o n�mero � primo.	
	*/
	else
	{
		int i=3;
		while(Remainder(a,i)!=0 && i<a)
		{
			i+=2;
		}
		/*A condi��o a seguir verifica porqu� o la�o acabou.*/
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
