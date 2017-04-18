#include<stdio.h>

int Palindromo(int *p,int tamanho)
{
	int i;
	for(i=0;i<tamanho;i++)
	{
		if(p[i]!=p[(tamanho-1)-i])
		{
			return 0;
		}
	}
	return 1;
}

void main()
{
	int vetor[5],i;
	for(i=0;i<5;i++)
	{
		scanf("%d",&vetor[i]);
	}

	if(Palindromo(vetor,5))
	{
		printf("O vetor inserido e' palindromo.\n");
	}
	else
	{
		printf("O vetor inserido nao e' palindromo.\n");
	}
}
