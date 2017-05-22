//Ligar LEDS enquanto o
//botão estiver pressionado
#include <msp430g2553.h>
#define BTN BIT3
#define LED1 BIT0
#define LED2 BIT6
int main(void){
    WDTCTL = WDTPW | WDTHOLD;
    P1OUT = 0;
    P1REN |= BTN;
    P1DIR |= LED1 + LED2;
    P1OUT |= BTN; 
    for(;;)
      {
      if((P1IN & BTN) == 0)
      {
        P1OUT |= LED1 + LED2;
      }
      else
      {
        P1OUT &= ~(LED1 + LED2);
      }
      }
}

