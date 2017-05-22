#include <msp430g2553.h>
#include <intrinsics.h>

#define LED1 BIT0
#define LED2 BIT6

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    BCSCTL1 = CALBC1_1MHZ;      //MCLK e SMCLK @ 1MHz
    DCOCTL = CALDCO_1MHZ;       //MCLK e SMCLK @ 1MHz
    P1OUT &= ~(LED1+LED2);
    P1DIR |= LED1 + LED2;
    TA0CCR0 = 25000-1;
    TA0CTL = TASSEL_2 + ID_1 + MC_1 + TAIE;
    _BIS_SR(LPM0_bits+GIE);
    return 0;
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TIMER0_TA0_ISR(void)
{
    P1OUT ^= LED1 + LED2;
    TA0CTL &= ~TAIFG;
}

