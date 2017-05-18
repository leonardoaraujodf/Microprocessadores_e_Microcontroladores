#include <msp430.h> 
#define L0 BIT0
#define L1 BIT1
#define L2 BIT2
#define L3 BIT3
#define L4 BIT4
#define L5 BIT5

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	for(;;)
	{
	    //acender o led L0
	    P1DIR = 0;
	    P1DIR |= L0 + L1; //define p1.0 E p1.1 como saida
	    P1OUT = 0;
	    P1OUT |= L0;     // faz o led l0 acender;

	    //acender o led L1

	    P1OUT &= ~(L0);
	    P1OUT |= L1;

	    //acender o led L2

	    P1DIR &= ~(L0); //O BIT0 deve ser definido como entrada para se poder acender os leds L2 e L3
	    P1DIR |= L2; //O BIT1 e o BIT2 devem ser saidas
	    //P1OUT deve ser ter a porta P1.1 em Vcc. Ela j� esta ativada na linha 25.

	    //acender o led L3

	    P1OUT &= ~(L1);
	    P1OUT |= L2;

	    //acender o led L4

	    P1DIR &= ~(L1); //tornar p1.1 como entrada
	    P1DIR |= L0; //Definir o p1.0 e p1.2 como saidas
	    P1OUT &= ~(L2); //Tornar 1.2 como GND
	    P1OUT |= L0; //Tornar 1.0 como Vcc

	    //acender o led L5

	    P1OUT &= ~(L0); //Tornar 1.0 como GND
	    P1OUT |= L2; //Tornar 1.2 como Vcc

	}
	
	return 0;
}
