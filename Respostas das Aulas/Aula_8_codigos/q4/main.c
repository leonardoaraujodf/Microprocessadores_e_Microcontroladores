
#include <msp430g2553.h>
#define BTN BIT3
#define LED1 BIT0
#define LED2 BIT6

int main( void )
{
  volatile unsigned int i;
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT = 0;
  P1REN |= BTN;
  P1DIR |= LED1 + LED2;
  P1OUT = BTN;
    for(;;)
    {
      if((P1IN & BTN) == 0)
      {
        P1OUT ^= LED1 + LED2;
        
      }
      else
      {
        P1OUT &= ~(LED1 + LED2);
      }
      for(i=0; i<3; i++);
    }
  return 0;
}
