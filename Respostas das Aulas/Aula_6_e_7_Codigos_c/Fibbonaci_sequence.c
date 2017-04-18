#include<stdio.h>

int Fibbonaci_sequence(int a)
{
	/*Devolve o valor do n-ésimo termo da sequência de Fibbonaci*/
	if(a==0)
	{
		return 0;
	}
	else if(a==1 || a==2)
	{
		return 1;
	}
	else
	{
		int i, vetor[3]={1,1,0};
		for(i=3;i<=a;i++)
		{
			vetor[2] = vetor[1] + vetor[0]; /*vetor[n] = vetor[n-1] + vetor[n-2]*/
			vetor[0] = vetor[1]; 			/*vetor[n-2] = vetor [n-1]*/
			vetor[1] = vetor[2]; 			/*vetor[n-1] = vetor [n], para a próxima iteracao*/
			
		}
		return vetor[2];
		
	}
	
}

void main()
{
	int termo,valor;
	scanf("%d",&termo);
	valor = Fibbonaci_sequence(termo);
	printf("O termo %d da sequencia de Fibbonaci e' %d.\n",termo,valor);
}
