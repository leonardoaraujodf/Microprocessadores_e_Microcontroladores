#include<stdio.h>

int Vetor_Ordenado_Decrescente(int *p,int n)
{
	/*Vetor_Ordenado_Decrescente é uma função que analisa se um vetor é decrescente ou não,
	de forma que retorna 1 se for decrescente e 0 se for decrescente.
	p* é um ponteiro que aponta para a primeira posição do vetor e n é um valor inteiro com o tamanho do vetor*/
	
	int i;
	for (i=0;i<n;i++)
	{
		
		if((i>0)&&(p[i] >= p[i-1]))
		{
			return 0;
		}
	}
	/*Se todas as posições do vetor foram visualizadas, o vetor é decrescente e a função deve retornar 1.*/
	return 1;
}

void main()
{
	int vetor[5],i,verificador;
	
	for(i=0;i<5;i++)
	{
		scanf("%d",&vetor[i]);	
	}
	
	verificador = Vetor_Ordenado_Decrescente(vetor,5);
	if(verificador == 1)
	{
		printf("O vetor ");
		for(i=0;i<5;i++)
		{	
			printf("%d ",vetor[i]);
		}	
		printf("e' decrescente.\n");
	}
	else
	{
		printf("O vetor ");
		for(i=0;i<5;i++)
		{	
			printf("%d ",vetor[i]);
		}	
		printf("nao e' decrescente.\n");
	}
	
}
