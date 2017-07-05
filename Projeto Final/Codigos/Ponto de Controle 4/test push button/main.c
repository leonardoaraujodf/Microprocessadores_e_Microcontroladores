
#include <msp430g2553.h>
#define BTN BIT0
#define LED BIT6

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1OUT = 0;
  P1DIR &= ~BTN;
  P1REN |= BTN;
  P1OUT |= BTN;
  P1DIR |= LED;
  for(;;)
  {
    if((P1IN&BTN)==0)
    {
      P1OUT |= LED;
    }
    else
    {
      P1OUT &= ~LED;
    }
  }
  
  return 0;
}
