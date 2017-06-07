#include "msp430g2553.h"

extern void toogle_leds();

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  P1DIR |= BIT0;
  while(1)
  {
    toogle_leds();
  }

  return 0;
}
