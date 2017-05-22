#include <msp430.h> 

/*
 * main.c
 */

void Atraso(volatile unsigned int x)
{
    TACCR0 = 1000-1; //capture mode ativo para pegar o timer em 999
    TACTL |= TACLR; // limpar o timer A
    TACTL = TASSEL_2 + ID_0 + MC_1; //TASSEL_2 escolhe SMCLK como o clock do TAR
                                    //ID_0 significa que o clock sera dividido por 1
                                    //MC_1 significa que o timer segue o modo UP e vai contar até o valor setado em TACCR0
    while(x>0)
    {
      x--;
      while((TACTL&TAIFG)==0);
              TACTL &= ~TAIFG;
    }
    TACTL = MC_0; //timer no modo stop

}

void paralelo_para_serial(void)
{
    int i,x;
    x = P1IN;
    //A ideia é supor que P1IN vai ficar sem mudar sua saída por no mínimo 8 ms
    for(i=0;i<7;i++)
    {
        P2OUT = x;
        Atraso(1);
        x = (x >> 1);
    }

}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
	P1DIR = 0; //Definindo toda a porta P1 como entrada
	P2OUT = 0; //Inicializando toda a porta P2 em 0
	P2DIR |= BIT0; //Definindo somente P2.0 definida como saida
	for(;;)
	{
	    paralelo_para_serial();
	}
	return 0;
}

