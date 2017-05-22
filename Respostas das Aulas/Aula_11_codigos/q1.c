#include <msp430g2553.h>
#include <intrinsics.h>

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

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
	return 0;
}
