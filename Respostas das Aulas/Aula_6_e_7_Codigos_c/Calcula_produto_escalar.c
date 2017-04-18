#include<stdio.h>

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

int Produto_Escalar_int(int *a,int *b, int n)
{
/*O ponteiro *a aponta para o endereço do primeiro vetor na memória e o ponteiro *b aponta para o endereço do
do segundo vetor na memória. O número n indica o tamanho do vetor. Esta função retorna um valor inteiro.
*/	

	int i,soma=0;
	for(i=0;i<n;i++)
	{
		soma += MULT_signed(a[i],b[i]);
	}
	return soma;
}

void main()
{
	int a[3],b[3],i,prod_escalar;
	printf("Insira o valor do vetor a\n");
	for(i=0;i<3;i++)
	{
		scanf("%d",&a[i]);
	}
	printf("Insira o valor do vetor b\n");
	for(i=0;i<3;i++)
	{
		scanf("%d",&b[i]);
	}
	prod_escalar = Produto_Escalar_int(a,b,3);
	printf("O produto escalar do vetor a = <%d,%d,%d> e b = <%d,%d,%d> e' a.b = %d.\n",a[0],a[1],a[2],b[0],b[1],b[2],prod_escalar);
}
