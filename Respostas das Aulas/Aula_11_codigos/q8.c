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
    P2OUT |= BIT0; //Começando com um bit 1 e mandando ele por 1 ms
    atraso(1);
    for(i=0;i<8;i++)
    {
        P2OUT |= (x&BIT0); //Mascarando x para nao aparecer valor espúrio na saída de P2OUT inteira
        Atraso(1);
        x = (x >> 1); //vai mandando do lsb para o msb de P1IN
    }
    P2OUT &= ~(BIT0); //Manda o bit 0 para terminar a comunicação
    Atraso(1);
}


int main(void) {
    WDTCTL = WDTPW | WDTHOLD;   // Stop watchdog timer
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
