int ocorrencias_caracter(char s[],char caracter)
{
	int ocorrencias=0,i=0;
	while(s[i] != '\0')
	{
		if(s[i] == caracter)
		{
			ocorrencias++;
		}
		i++;	
	}
	return ocorrencias;
}

void main ()
{
	int ocorrencias;
	ocorrencias = ocorrencias_caracter("josiane de sousa alves",'a');
	printf("Foram %d ocorrencias da letra %c na palavra %s.\n",ocorrencias,'a',"josiane de sousa alves");
}
